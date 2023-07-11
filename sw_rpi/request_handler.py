import sqlite3
import cgi

PATH_2_DB = '/home/pi/plant_boss/plant_boss.db'

## Dispatches HTTP requests to the appropriate handler.
def application(env, start_line):
    if env['REQUEST_METHOD'] == 'POST':   ## add new DB record
        return handle_post(env, start_line)
    elif env['REQUEST_METHOD'] == 'GET':  ## create HTML-fragment report 
        return handle_get(start_line)
    else:                                 ## no other option for now
        start_line('405 METHOD NOT ALLOWED', [('Content-Type', 'text/plain')])
        response_body = 'Only POST and GET verbs supported.'
        return [response_body.encode()]                            

def handle_post(env, start_line):    
    form = get_field_storage(env)  ## body of an HTTP POST request
    
    ## Extract fields from POST form.
    timestamp = form.getvalue('timestamp')
    device = form.getvalue('device')
    humidity = form.getvalue('humidity')
    light = form.getvalue('light')
    temperature = form.getvalue('temperature')
    bat_voltage = form.getvalue('bat_voltage')
    rssi_wifi = form.getvalue('rssi_wifi')

    ## Missing info?
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
        response_body = "Missing info in POST request.\n"
        start_line('400 Bad Request', [('Content-Type', 'text/plain')])
 
    return [response_body.encode()]

def handle_get(start_line):
    conn = sqlite3.connect(PATH_2_DB)        ## connect to DB
    cursor = conn.cursor()                   ## get a cursor
    cursor.execute("select * from plant_boss_test_2")

    response_body = "<h3>plant_boss report</h3><ul>"
    rows = cursor.fetchall()
    for row in rows:
        response_body += "<li>" + str(row[0]) + '|'  ## id
        response_body += str(row[1]) + '|'                ## timestamp
        response_body += str(row[2]) + '|'                ## device
        response_body += str(row[3]) + '|'           ## humidity
        response_body += str(row[4]) + '|' #light
        response_body += str(row[5]) + '|' #temperature
        response_body += str(row[6]) + '|' #bat_voltage
        response_body += str(row[7]) + "</li>"       ## rssi_wifi
        response_body += "</ul>"

    conn.commit()  ## commit
    conn.close()   ## cleanup
    
    start_line('200 OK', [('Content-Type', 'text/html')])
    return [response_body.encode()]

## Add a record from a device to the DB.
def add_record(timestamp, device, humidity, light, temperature, bat_voltage, rssi_wifi):
    conn = sqlite3.connect(PATH_2_DB)      ## connect to DB
    cursor = conn.cursor()                 ## get a cursor

    sql = "INSERT INTO plant_boss_test_2(timestamp,device,humidity,light,temperature,bat_voltage,rssi_wifi) values (?,?,?,?,?,?,?)"
    cursor.execute(sql, (timestamp, device, humidity, light, temperature, bat_voltage, rssi_wifi)) ## execute INSERT 

    conn.commit()  ## commit
    conn.close()   ## cleanup

def get_field_storage(env):
    input = env['wsgi.input']
    form = env.get('wsgi.post_form')
    if (form is not None and form[0] is input):
        return form[2]

    fs = cgi.FieldStorage(fp = input,
                          environ = env,
                          keep_blank_values = 1)
    return fs
