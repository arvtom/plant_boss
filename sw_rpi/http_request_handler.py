import sqlite3
import cgi
from datetime import datetime

PATH_DATABASE = '/home/pi/github/plant_boss/sw_rpi/plant_boss.db'
TABLE_NAME = 'plant_boss_test_3'
ROWS = 100

# Dispatches HTTP requests to the appropriate handler.
def application(env, start_line):
    if env['REQUEST_METHOD'] == 'POST':
        # take new database entry
        return handle_post(env, start_line)

    elif env['REQUEST_METHOD'] == 'GET':
        requested_path = env['PATH_INFO']

        if ("/plant_boss/data" == requested_path):
            response = handle_get_data(start_line)
        
        elif ("/plant_boss/settings" == requested_path):
            response = handle_get_settings(start_line)

        elif ("/plant_boss/plot" == requested_path):
            response = handle_get_plot(start_line) 
        
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

def handle_get_settings(start_line):
    response_body = """
        <!DOCTYPE html>
        <html>
            <body>
                <h2>get settings</h2>
            </body>
        </html>"""
    
    start_line('200 OK', [('Content-Type', 'text/html')])
    return [response_body.encode()]

def handle_get_plot(start_line):
    conn = sqlite3.connect(PATH_DATABASE)        # connect to database
    cursor = conn.cursor()                   # get a cursor
    cursor.execute("select * from " + TABLE_NAME)
    rows = cursor.fetchall()

    humidity = rows[3][:]
    light = rows[4][:]
    temperature = rows[5][:]

    print(rows[0][3])
    print(rows[0:-1][3])
    print(rows[3][0:-1])
    print(type(rows))
    print(humidity)
    print(light)
    print(temperature)

    response_body = """
        <!DOCTYPE html>
        <html>
            <body>
                <h2>get plot</h2>
            </body>
        </html>"""
    
    start_line('200 OK', [('Content-Type', 'text/html')])
    return [response_body.encode()]

def handle_get_data(start_line):
    conn = sqlite3.connect(PATH_DATABASE)        # connect to database
    cursor = conn.cursor()                   # get a cursor
    cursor.execute("select * from " + TABLE_NAME)
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
                <h2>plant_boss database report</h2>

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

    print("Count of Rows")
    cursor.execute("select * from " + TABLE_NAME)
    number_rows = len(cursor.fetchall())
    print(number_rows)

    sql = "INSERT INTO " + TABLE_NAME + """
        (timestamp,device,humidity,light,temperature,bat_voltage,rssi_wifi,mode,bat_low_flag,
        error_app,error_input,error_output,error_network,error_memory,sw_version,timer_or_period) 
        values (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)"""
    cursor.execute(sql, (timestamp, device, humidity, light, temperature, bat_voltage, rssi_wifi, mode, bat_low_flag, \
        error_app, error_input, error_output, error_network, error_memory, sw_version, timer_or_period)) # execute INSERT 

    sql = "DELETE FROM " + TABLE_NAME +  " WHERE ROWID IN (SELECT ROWID FROM " + TABLE_NAME + " ORDER BY ROWID DESC LIMIT -1 OFFSET "+ str(ROWS) +")"
    cursor.execute(sql)

    conn.commit()
    conn.close()
