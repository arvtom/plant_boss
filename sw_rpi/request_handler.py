import sqlite3
import cgi

PATH_DATABASE = '/home/pi/github/plant_boss/sw_rpi/plant_boss.db'
TABLE_NAME = 'plant_boss_test_2'
ROWS = 100

# Dispatches HTTP requests to the appropriate handler.
def application(env, start_line):
    if env['REQUEST_METHOD'] == 'POST':
        # take new database entry
        return handle_post(env, start_line)

    elif env['REQUEST_METHOD'] == 'GET':
        # return database contents in html
        return handle_get(start_line)

    else:
        # for other type html requests, return error
        start_line('405 METHOD NOT ALLOWED', [('Content-Type', 'text/plain')])
        response_body = 'Only POST and GET verbs supported.'
        return [response_body.encode()]                            

def handle_post(env, start_line):    
    form = get_field_storage(env)  # body of an HTTP POST request
    
    # Extract fields from POST form.
    timestamp = form.getvalue('timestamp')
    device = form.getvalue('device')
    humidity = form.getvalue('humidity')
    light = form.getvalue('light')
    temperature = form.getvalue('temperature')
    bat_voltage = form.getvalue('bat_voltage')
    rssi_wifi = form.getvalue('rssi_wifi')

    # Check if there is missing data
    if (timestamp is not None and
            device is not None and
            humidity is not None and
            light is not None and
            temperature is not None and
            bat_voltage is not None and
            rssi_wifi is not None):
        add_record(timestamp, device, humidity, light, temperature, bat_voltage, rssi_wifi)
        response_body = "POST request handled.\n"
        start_line('201 OK', [('Content-Type', 'text/plain')])

    else:
        # Return error
        response_body = "Missing info in POST request.\n"
        start_line('400 Bad Request', [('Content-Type', 'text/plain')])
 
    return [response_body.encode()]

def handle_get(start_line):
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
                    <th>humidity</th>
                    <th>light</th>
                    <th>temperature</th>
                    <th>bat_voltage</th>
                    <th>rssi_wifi</th>
                </tr>
                """

    for i in range(ROWS-1, 0, -1):
        row = rows[i]
        response_body += "<tr>"
        response_body += "<td>" + str(row[0]) + "</td>"     # id
        response_body += "<td>" + str(row[1]) + "</td>"     # timestamp
        response_body += "<td>" + str(row[2]) + "</td>"     # device
        response_body += "<td>" + str(row[3]) + "</td>"     # humidity
        response_body += "<td>" + str(row[4]) + "</td>"     #light
        response_body += "<td>" + str(row[5]) + "</td>"     #temperature
        response_body += "<td>" + str(row[6]) + "</td>"     #bat_voltage
        response_body += "<td>" + str(row[7]) + "</td>"     # rssi_wifi
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

def add_record(timestamp, device, humidity, light, temperature, bat_voltage, rssi_wifi):
    conn = sqlite3.connect(PATH_DATABASE)      # connect to database
    cursor = conn.cursor()                 # get a cursor

    print("Count of Rows")
    cursor.execute("select * from " + TABLE_NAME)
    number_rows = len(cursor.fetchall())
    print(number_rows)

    sql = "INSERT INTO " + TABLE_NAME + "(timestamp,device,humidity,light,temperature,bat_voltage,rssi_wifi) values (?,?,?,?,?,?,?)"
    cursor.execute(sql, (timestamp, device, humidity, light, temperature, bat_voltage, rssi_wifi)) # execute INSERT 

    sql = "DELETE FROM " + TABLE_NAME +  " WHERE ROWID IN (SELECT ROWID FROM " + TABLE_NAME + " ORDER BY ROWID DESC LIMIT -1 OFFSET "+ str(ROWS) +")"
    cursor.execute(sql)

    conn.commit()
    conn.close()

def get_field_storage(env):
    input = env['wsgi.input']
    form = env.get('wsgi.post_form')
    if (form is not None and form[0] is input):
        return form[2]

    fs = cgi.FieldStorage(fp = input, environ = env, keep_blank_values = 1)

    return fs
