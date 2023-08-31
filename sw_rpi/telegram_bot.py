import telebot
from apscheduler.schedulers.blocking import BlockingScheduler
from threading import Thread
import sqlite3
from datetime import datetime
import matplotlib.pyplot as plt

# Import BOT_TOKEN and CHAT_ID
import settings_telegram_bot

BOT_TOKEN = settings_telegram_bot.BOT_TOKEN
CHAT_ID = settings_telegram_bot.CHAT_ID

PATH_DATABASE = '/home/pi/github/plant_boss/sw_rpi/plant_boss.db'
TABLE_NAME_SETTINGS = 'plant_boss_settings_test_4'
TABLE_NAME_DATA = 'plant_boss_test_3'

device_id = 0
device_mode = 0
threshold_bat_voltage = 0.0
period_measurement = 0.0
b_settings_valid = False

bot = telebot.TeleBot(BOT_TOKEN)

def check_plant_boss():
    conn = sqlite3.connect(PATH_DATABASE)      # connect to database
    cursor = conn.cursor()                 # get a cursor

    cursor.execute("SELECT * FROM " + TABLE_NAME_DATA + " order by ROWID DESC limit 1")
    entries = cursor.fetchall()

    conn.commit()
    conn.close()

    if 0 == len(entries):
        # bot.send_message(CHAT_ID, "Database is empty")
        nothing=0
    else:
        entries = entries[0]

        if entries[3] < 40.0:
            bot.send_message(CHAT_ID, "Plant needs water, humidity is " + str(entries[3]) + " %")
        else:
            bot.send_message(CHAT_ID, "Plant is ok, humidity is " + str(entries[3]) + " %")

def run_scheduled_task():
    check_plant_boss()

scheduler = BlockingScheduler(timezone="Europe/Berlin") # You need to add a timezone, otherwise it will give you a warning
scheduler.add_job(run_scheduled_task, trigger="cron", minute = "*") # Runs every minute
# scheduler.add_job(run_scheduled_task, trigger="cron", minute = "*/1") # Runs every 60min

def schedule_checker():
    bot.send_message(CHAT_ID, "Telegram bot started")

    check_plant_boss()

    while True:
        scheduler.start()

# Handle message /help
@bot.message_handler(commands=['help'])
def print_help(message):
    string_response = """
        The purpose of this telegram bot:
        * Send periodic notifications about plant environment parameters (soil humidity, temperature, amount of light).
        * Send notifications when plant needs to be watered ASAP.
        * Edit settings for plant_boss devices.
        * Print settings for all plant_boss devices.

        To change settings for plant_boss device, enter message in following format:
        * settings:<device_id>;<device_mode>;<threshold_bat_voltage>;<period_measurement>

        To print settings for all plant_boss devices:
        * /settings

        For information:
        * device_id can be integer: from 0 to 255.
        * device_mode is integer: 0 (real time) or 1 (normal with sleep function).
        * threshold_bat_voltage is float in mV: from 0 to 4.2.
        * period_measurement is float in s: from 1 to 86400.
    """

    bot.send_message(message.chat.id, string_response)

@bot.message_handler(commands=['settings'])
def print_settings(message):
    string_response = "Number of entries "

    conn = sqlite3.connect(PATH_DATABASE)      # connect to database
    cursor = conn.cursor()                 # get a cursor

    cursor.execute("SELECT * FROM " + TABLE_NAME_SETTINGS)
    entries = cursor.fetchall()

    conn.commit()
    conn.close()

    if 0 == len(entries):
        bot.send_message(CHAT_ID, "Database is empty")
    else:
        number_rows = len(entries)
        string_response += str(number_rows) + "\r\n\r\n"

        string_response += "(entry_id, timestamp, device_id, device_mode, threshold_bat_voltage, period_measurement)\r\n"

        for i in range(0, number_rows):
            string_response += str(entries[i]) + "\r\n"

        bot.send_message(message.chat.id, string_response)

# When using this function, received error from telegram that message is too long.
@bot.message_handler(commands=['data'])
def print_data(message):
    conn = sqlite3.connect(PATH_DATABASE)      # connect to database
    cursor = conn.cursor()                 # get a cursor

    cursor.execute("SELECT * FROM " + TABLE_NAME_DATA + " order by ROWID DESC limit 1")
    entries = cursor.fetchall()

    conn.commit()
    conn.close()

    if 0 == len(entries):
        bot.send_message(CHAT_ID, "Database is empty")
    else:
        entries = entries[0]

        string_response = "entry_id=" + str(entries[0])\
            + "; time=" + str(entries[1])\
            + "; device_id=" + str(entries[2])\
            + "; humidity=" + str(entries[3]) + " %"\
            + "; light=" + str(entries[4]) + " lx"\
            + "; temperature=" + str(entries[5]) + " C"
        bot.send_message(CHAT_ID, string_response)

def update_plot():
    conn = sqlite3.connect(PATH_DATABASE)        # connect to database
    cursor = conn.cursor()                   # get a cursor
    cursor.execute("select * from " + TABLE_NAME_DATA)
    rows = cursor.fetchall()

    conn.commit()
    conn.close()

    if 0 == len(rows):
        return False

    humidity = []
    light = []
    temperature = []
    time = []
    timestamp = []

    length_rows = len(rows) - 1

    for i in range(length_rows, 0, -1):
        row = rows[i]

        humidity.append(row[3])
        light.append(row[4])
        temperature.append(row[5])

    time = range(0, length_rows, 1)

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

    return True

@bot.message_handler(commands=['plot'])
def print_plot(message):
    if False == update_plot():
        bot.send_message(CHAT_ID, "plot error")
    else:
        bot.send_photo(CHAT_ID, open("humidity.png", "rb"))

def parse_message(string_input):
    global device_id
    global device_mode
    global threshold_bat_voltage
    global period_measurement
    global b_settings_valid

    string_response = ""

    if ("settings:" != string_input[0:9]):
        string_response = "I don't understand."
        return string_response

    settings = string_input[9:].split(";")
    length_settings = len(settings)

    if (4 != length_settings):
        string_response = "Missing settings parameters."
        return string_response

    is_numeric = []
    is_numeric.append(settings[0].isnumeric())
    is_numeric.append(settings[1].isnumeric())
    is_numeric.append(settings[2].replace(".", "").isnumeric())
    is_numeric.append(settings[3].replace(".", "").isnumeric())

    if (False == is_numeric[0] or 
        False == is_numeric[1] or
        False == is_numeric[2] or
        False == is_numeric[3]):
        string_response = "One of settings parameters is not numeric. " + str(is_numeric[:])
        return string_response

    device_id = int(settings[0])
    device_mode = int(settings[1])
    threshold_bat_voltage = float(settings[2])
    period_measurement = float(settings[3])

    if (device_id < 0 or device_id > 255):
        string_response = "device_id is invalid."
        return string_response

    if (device_mode < 0 or device_mode > 1):
        string_response = "device_mode is invalid."
        return string_response

    if (threshold_bat_voltage < 0.0 or threshold_bat_voltage > 4.2):
        string_response = "threshold_bat_voltage is invalid."
        return string_response

    if (period_measurement < 1.0 or period_measurement > 86400.0):
        string_response = "period_measurement is invalid."
        return string_response

    b_settings_valid = True

    string_response = "Settings received. device_id=" + str(device_id)\
        + "; device_mode=" + str(device_mode)\
        + "; threshold_bat_voltage=" + str(threshold_bat_voltage)\
        + "; period_measurement=" + str(period_measurement)

    return string_response

def handle_database():
    global device_id
    global device_mode
    global threshold_bat_voltage
    global period_measurement

    conn = sqlite3.connect(PATH_DATABASE)      # connect to database
    cursor = conn.cursor()                 # get a cursor

    timestamp = datetime.now()

    # Delete settings entry with the same device_id, if it exists
    sql = "DELETE FROM " + TABLE_NAME_SETTINGS + " WHERE device=" + str(device_id) + ";"
    cursor.execute(sql)

    # Add new settings entry for device_id
    sql = "INSERT INTO " + TABLE_NAME_SETTINGS + """
        (timestamp,device,mode,threshold_bat_voltage,period_measurement) 
        values (?,?,?,?,?)"""
    cursor.execute(sql, (timestamp, device_id, device_mode, threshold_bat_voltage, period_measurement))

    conn.commit()
    conn.close()

    return True

# Handle any other text message
@bot.message_handler(func=lambda message: True)
def handle_message(message):
    global b_settings_valid

    # Reset flag
    b_settings_valid = False

    bot.send_message(message.chat.id, parse_message(message.text))

    if (True == b_settings_valid):
        if (False == handle_database()):
            bot.send_message(message.chat.id, "Database error.")

        bot.send_message(message.chat.id, "Database updated.")

Thread(target=schedule_checker).start() # Notice that you refer to schedule_checker function which starts the job

bot.polling() # Also notice that you need to include polling to allow your bot to get commands from you. But it should happen AFTER threading!
