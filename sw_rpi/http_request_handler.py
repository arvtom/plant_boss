import sqlite3
import cgi
from datetime import datetime
import matplotlib.pyplot as plt
import base64

PATH_DATABASE = '/home/pi/github/plant_boss/sw_rpi/plant_boss.db'
TABLE_NAME_DATA = 'plant_boss_test_3'
TABLE_NAME_SETTINGS = 'plant_boss_settings_test_4'
ROWS = 100

device_id_request_settings = 0

# Dispatches HTTP requests to the appropriate handler.
def application(env, start_line):
    requested_path = env['PATH_INFO']

    if env['REQUEST_METHOD'] == 'POST':
        # esp32 sending measured data
        if ("/plant_boss/data" == requested_path):
            response = handle_post(env, start_line)

        # esp32 request settings for specific device number
        elif ("/plant_boss/settings_request" == requested_path):
            response = handle_post_settings_request(env, start_line)
        
        return response
        
    elif env['REQUEST_METHOD'] == 'GET':
        # webpage requesting measured data
        if ("/plant_boss/data" == requested_path):
            response = handle_get_data(start_line)
        
        # webpage requesting esp32 settings
        elif ("/plant_boss/settings" == requested_path):
            response = handle_get_settings(start_line)

        # webpage requesting plot from measured data
        elif ("/plant_boss/plot" == requested_path):
            response = handle_get_plot(start_line) 

        # esp32 get settings for specific device number
        elif ("/plant_boss/settings_request" == requested_path):
            response = handle_get_settings_request(start_line)  
        
        else:
            response = handle_get_error(start_line)

        return response

    else:
        # for other type html requests, return error
        start_line('405 METHOD NOT ALLOWED', [('Content-Type', 'text/plain')])
        response_body = 'Only POST and GET verbs supported.'
        return [response_body.encode()]                            

def handle_get_error(start_line):
    response_body = """
        <!DOCTYPE html>
        <html>
            <body>
                <h2>error unknown path</h2>
            </body>
        </html>"""
    
    start_line('200 OK', [('Content-Type', 'text/html')])
    return [response_body.encode()]

def handle_get_settings_request(start_line):
    global device_id_request_settings

    conn = sqlite3.connect(PATH_DATABASE)        # connect to database
    cursor = conn.cursor()                   # get a cursor
    sql = "SELECT * FROM " + TABLE_NAME_SETTINGS + " WHERE device=" + str(device_id_request_settings) + ";"
    cursor.execute(sql)

    rows = cursor.fetchall()
    amount_rows = len(rows)

    if (0 == amount_rows):
        response_body = "not found"
        start_line('405 METHOD NOT ALLOWED', [('Content-Type', 'text/plain')])

    if (amount_rows > 1):
        response_body = "found more than one"
        start_line('405 METHOD NOT ALLOWED', [('Content-Type', 'text/plain')])

    response_body = str(rows[0][2]) + ";" + str(rows[0][3]) + ";" +\
        str(rows[0][4]) + ";" + str(rows[0][5])
    start_line('200 OK', [('Content-Type', 'text/plain')])

def handle_get_settings(start_line):
    conn = sqlite3.connect(PATH_DATABASE)        # connect to database
    cursor = conn.cursor()                   # get a cursor
    cursor.execute("select * from " + TABLE_NAME_SETTINGS)
    rows = cursor.fetchall()

    response_body = """
        <!DOCTYPE html>
        <html>
            <style>
                table, th, td {
                border:1px solid black;
                }
            </style>

            <body>
                <h2>plant_boss settings</h2>

                <table style="width:100%">
                <tr>
                    <th>entry_id</th>
                    <th>timestamp</th>
                    <th>device_id</th>
                    <th>device_mode</th>
                    <th>threshold_bat_voltage</th>
                    <th>period_measurement</th>
                </tr>
                """

    for i in range(0, len(rows)):
        row = rows[i]
        response_body += "<tr>"
        response_body += "<td>" + str(row[0]) + "</td>"         # entry_id
        response_body += "<td>" + str(row[1]) + "</td>"         # timestamp
        response_body += "<td>" + str(row[2]) + "</td>"         # device_id
        response_body += "<td>" + str(row[3]) + "</td>"         # device_mode
        response_body += "<td>" + str(row[4]) + "</td>"         # threshold_bat_voltage
        response_body += "<td>" + str(row[5]) + "</td>"         # period_measurement
        response_body += "</tr>"

    response_body += """
                </table>
            </body>
        </html>
        """

    conn.commit()
    conn.close()
    
    start_line('200 OK', [('Content-Type', 'text/html')])
    return [response_body.encode()]

def handle_get_plot(start_line):
    conn = sqlite3.connect(PATH_DATABASE)        # connect to database
    cursor = conn.cursor()                   # get a cursor
    cursor.execute("select * from " + TABLE_NAME_DATA)
    rows = cursor.fetchall()

    humidity = []
    light = []
    temperature = []
    time = []
    timestamp = []

    length_rows = len(rows) - 1

    for i in range(length_rows, 0, -1):
        row = rows[i]

        # time.append(row[1])
        humidity.append(row[3])
        light.append(row[4])
        temperature.append(row[5])

    time = range(0, length_rows, 1)

    # time = time[0:10]
    # humidity = humidity[0:10]
    # light = light[0:10]
    # temperature = temperature[0:10]

    figure, axis = plt.subplots(3, 1)

    i = 0
    axis[i].plot(time, humidity)
    axis[i].set_xlabel("time")
    axis[i].set_ylabel("humidity, %")
    axis[i].set_xlim([0, length_rows])
    axis[i].grid(visible = True, which = "both", axis = "both")

    i = 1
    axis[i].plot(time, light)
    axis[i].set_xlabel("time")
    axis[i].set_ylabel("light, lx")
    axis[i].set_xlim([0, length_rows])
    axis[i].grid(visible = True, which = "both", axis = "both")

    i = 2
    axis[i].plot(time, temperature)
    axis[i].set_xlabel("time")
    axis[i].set_ylabel("temperature, C")
    axis[i].set_xlim([0, length_rows])
    axis[i].grid(visible = True, which = "both", axis = "both")

    plt.savefig("humidity.png")

    data_uri = base64.b64encode(open('humidity.png', 'rb').read()).decode('utf-8')
    response_body = '<img src="data:image/png;base64,{0}">'.format(data_uri)

    # response_body = """
    #     <picture>
    #         <source media="(min-width:200px)" srcset="humidity.png">
    #         <img src="/home/pi/github/plant_boss/sw_rpi/humidity.png" alt="Humidity" style="width:auto;">
    #     </picture>
    # """
    
    start_line('200 OK', [('Content-Type', 'text/html')])
    return [response_body.encode()]

def handle_get_data(start_line):
    conn = sqlite3.connect(PATH_DATABASE)        # connect to database
    cursor = conn.cursor()                   # get a cursor
    cursor.execute("select * from " + TABLE_NAME_DATA)
    rows = cursor.fetchall()

    response_body = """
        <!DOCTYPE html>
        <html>
            <style>
                table, th, td {
                border:1px solid black;
                }
            </style>

            <body>
                <h2>plant_boss data</h2>

                <table style="width:100%">
                <tr>
                    <th>id</th>
                    <th>timestamp</th>
                    <th>device</th>
                    <th>humidity, %</th>
                    <th>light, lx</th>
                    <th>temperature, C</th>
                    <th>bat_voltage, V</th>
                    <th>rssi_wifi, dBm</th>
                    <th>mode</th>
                    <th>bat_low_flag</th>
                    <th>error_app</th>
                    <th>error_input</th>
                    <th>error_output</th>
                    <th>error_network</th>
                    <th>error_memory</th>
                    <th>sw_version</th>
                    <th>timer_or_period</th>
                </tr>
                """

    for i in range(len(rows)-1, 0, -1):
        row = rows[i]
        response_body += "<tr>"
        response_body += "<td>" + str(row[0]) + "</td>"         # id
        response_body += "<td>" + str(row[1]) + "</td>"         # timestamp
        response_body += "<td>" + str(row[2]) + "</td>"         # device
        response_body += "<td>" + str(row[3]) + "</td>"         # humidity
        response_body += "<td>" + str(row[4]) + "</td>"         #light
        response_body += "<td>" + str(row[5]) + "</td>"         #temperature
        response_body += "<td>" + str(row[6]) + "</td>"         #bat_voltage
        response_body += "<td>" + str(row[7]) + "</td>"         # rssi_wifi
        response_body += "<td>" + str(row[8]) + "</td>"         # mode
        response_body += "<td>" + str(row[9]) + "</td>"         # bat_low_flag
        response_body += "<td>" + str(row[10]) + "</td>"        # error_app
        response_body += "<td>" + str(row[11]) + "</td>"        # error_input
        response_body += "<td>" + str(row[12]) + "</td>"        # error_output
        response_body += "<td>" + str(row[13]) + "</td>"        # error_network
        response_body += "<td>" + str(row[14]) + "</td>"        # error_memory
        response_body += "<td>" + str(row[15]) + "</td>"        # sw_version
        response_body += "<td>" + str(row[16]) + "</td>"        # timer_or_period
        response_body += "</tr>"

    response_body += """
                </table>
            </body>
        </html>
        """

    conn.commit()
    conn.close()
    
    start_line('200 OK', [('Content-Type', 'text/html')])
    return [response_body.encode()]

def handle_post_settings_request(env, start_line): 
    global device_id_request_settings

    form = get_field_storage(env)

    temporary = form.getvalue('a1')

    if (temporary is not None):
        device_id_request_settings = temporary

        response_body = "OK\n"
        start_line('201 OK', [('Content-Type', 'text/plain')])

    else:
        response_body = "Missing info in POST request.\n"
        start_line('400 Bad Request', [('Content-Type', 'text/plain')])
 
    return [response_body.encode()]

def handle_post(env, start_line):    
    form = get_field_storage(env)  # body of an HTTP POST request

    timestamp = datetime.now()
    
    # Extract fields from POST form.
    device = form.getvalue('a1')
    humidity = form.getvalue('a2')
    light = form.getvalue('a3')
    temperature = form.getvalue('a4')
    bat_voltage = form.getvalue('a5')
    rssi_wifi = form.getvalue('a6')
    mode = form.getvalue('a7')
    bat_low_flag = form.getvalue('a8')
    error_app = form.getvalue('a9')
    error_input = form.getvalue('a10')
    error_output = form.getvalue('a11')
    error_network = form.getvalue('a12')
    error_memory = form.getvalue('a13')
    sw_version = form.getvalue('a14')
    timer_or_period = form.getvalue('a15')

    # Check if there is missing data
    if (device is not None and
        humidity is not None and
        light is not None and
        temperature is not None and
        bat_voltage is not None and
        rssi_wifi is not None and 
        mode is not None and 
        bat_low_flag is not None and 
        error_app is not None and 
        error_input is not None and 
        error_output is not None and 
        error_network is not None and 
        error_memory is not None and 
        sw_version is not None and 
        timer_or_period is not None):

        add_record(timestamp, device, humidity, light, temperature, bat_voltage, rssi_wifi, mode, bat_low_flag, \
            error_app, error_input, error_output, error_network, error_memory, sw_version, timer_or_period)
        response_body = "OK\n"
        start_line('201 OK', [('Content-Type', 'text/plain')])

    else:
        # Return error
        response_body = "Missing info in POST request.\n"
        start_line('400 Bad Request', [('Content-Type', 'text/plain')])
 
    return [response_body.encode()]

def get_field_storage(env):
    input = env['wsgi.input']
    form = env.get('wsgi.post_form')
    if (form is not None and form[0] is input):
        return form[2]

    fs = cgi.FieldStorage(fp = input, environ = env, keep_blank_values = 1)

    return fs

def add_record(timestamp, device, humidity, light, temperature, bat_voltage, rssi_wifi, mode, bat_low_flag, \
        error_app, error_input, error_output, error_network, error_memory, sw_version, timer_or_period):
    conn = sqlite3.connect(PATH_DATABASE)      # connect to database
    cursor = conn.cursor()                 # get a cursor

    cursor.execute("select * from " + TABLE_NAME_DATA)
    number_rows = len(cursor.fetchall())

    sql = "INSERT INTO " + TABLE_NAME_DATA + """
        (timestamp,device,humidity,light,temperature,bat_voltage,rssi_wifi,mode,bat_low_flag,
        error_app,error_input,error_output,error_network,error_memory,sw_version,timer_or_period) 
        values (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)"""
    cursor.execute(sql, (timestamp, device, humidity, light, temperature, bat_voltage, rssi_wifi, mode, bat_low_flag, \
        error_app, error_input, error_output, error_network, error_memory, sw_version, timer_or_period)) # execute INSERT 

    sql = "DELETE FROM " + TABLE_NAME_DATA +  " WHERE ROWID IN (SELECT ROWID FROM " + TABLE_NAME_DATA + " ORDER BY ROWID DESC LIMIT -1 OFFSET "+ str(ROWS) +")"
    cursor.execute(sql)

    conn.commit()
    conn.close()
