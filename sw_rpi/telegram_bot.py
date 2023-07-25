import telebot
from apscheduler.schedulers.blocking import BlockingScheduler
from threading import Thread
import sqlite3
from datetime import datetime

# Import BOT_TOKEN and CHAT_ID
import settings_telegram_bot

BOT_TOKEN = settings_telegram_bot.BOT_TOKEN
CHAT_ID = settings_telegram_bot.CHAT_ID

PATH_DATABASE = '/home/pi/github/plant_boss/sw_rpi/plant_boss.db'
TABLE_NAME_SETTINGS = 'plant_boss_settings_test_3'
TABLE_NAME_DATA = 'plant_boss_test_3'

device_id = 0
device_mode = 0
b_settings_valid = False

bot = telebot.TeleBot(BOT_TOKEN)

def run_scheduled_task():
    print("I am running")
    bot.send_message(CHAT_ID, "This is telegram bot printing periodic message.")
    

scheduler = BlockingScheduler(timezone="Europe/Berlin") # You need to add a timezone, otherwise it will give you a warning
# scheduler.add_job(run_scheduled_task, trigger="cron", minute = "*") # Runs every minute
scheduler.add_job(run_scheduled_task, trigger="cron", minute = "*/59") # Runs every 60min

def schedule_checker():
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

        To change settings for plant_boss device, enter message in following format:
        * settings:<device_id>;<device_mode>

        For information:
        * device_id can be from 0 to 255.
        * device_mode can be 0 (real time) or 1 (normal with sleep function).
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

    number_rows = len(entries)
    string_response += str(number_rows) + "\r\n"

    for i in range(0, number_rows):
        string_response += str(entries[i]) + "\r\n"

    bot.send_message(message.chat.id, string_response)

# When using this function, received error from telegram that message is too long.
# @bot.message_handler(commands=['data'])
# def print_settings(message):
#     string_response = "Number of entries "

#     conn = sqlite3.connect(PATH_DATABASE)      # connect to database
#     cursor = conn.cursor()                 # get a cursor

#     cursor.execute("SELECT * FROM " + TABLE_NAME_DATA)
#     entries = cursor.fetchall()

#     conn.commit()
#     conn.close()

#     number_rows = len(entries)
#     string_response += str(number_rows) + "\r\n" + str(entries)

    bot.send_message(message.chat.id, string_response)

def parse_message(string_input):
    global device_id
    global device_mode
    global b_settings_valid

    string_response = ""

    if ("settings:" != string_input[0:9]):
        string_response = "I don't understand."
        return string_response

    settings = string_input[9:].split(";")
    length_settings = len(settings)

    if (2 != length_settings):
        string_response = "Missing settings parameters."
        return string_response

    is_numeric = []
    is_numeric.append(settings[0].isnumeric())
    is_numeric.append(settings[1].isnumeric())

    if (False == is_numeric[0] or 
        False == is_numeric[1]):
        string_response = "One of settings parameters is not numeric."
        return string_response

    device_id = int(settings[0])
    device_mode = int(settings[1])

    if (device_id < 0 or device_id > 255):
        string_response = "device_id is invalid."
        return string_response

    if (device_mode < 0 or device_mode > 1):
        string_response = "device_mode is invalid."
        return string_response

    b_settings_valid = True

    string_response = "Settings received. device_id=" + str(device_id) + "; device_mode=" + str(device_mode)
    return string_response

def handle_database():
    global device_id
    global device_mode

    conn = sqlite3.connect(PATH_DATABASE)      # connect to database
    cursor = conn.cursor()                 # get a cursor

    timestamp = datetime.now()

    # Delete settings entry with the same device_id, if it exists
    sql = "DELETE FROM " + TABLE_NAME + " WHERE device=" + str(device_id) + ";"
    cursor.execute(sql)

    # Add new settings entry for device_id
    sql = "INSERT INTO " + TABLE_NAME + """
        (timestamp,device,mode) 
        values (?,?,?)"""
    cursor.execute(sql, (timestamp, device_id, device_mode))

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
