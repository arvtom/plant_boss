import telebot
from apscheduler.schedulers.blocking import BlockingScheduler
from threading import Thread

# Import BOT_TOKEN and CHAT_ID
import settings_telegram_bot

BOT_TOKEN = settings_telegram_bot.BOT_TOKEN
CHAT_ID = settings_telegram_bot.CHAT_ID

bot = telebot.TeleBot(BOT_TOKEN)

def run_scheduled_task():
    print("I am running")
    bot.send_message(CHAT_ID, "This is telegram bot printing periodic message.")
    

scheduler = BlockingScheduler(timezone="Europe/Berlin") # You need to add a timezone, otherwise it will give you a warning
# scheduler.add_job(run_scheduled_task, trigger="cron", minute = "*") # Runs every minute
scheduler.add_job(run_scheduled_task, trigger="cron", minute = "*/5") # Runs every 5min

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

# def handle_settings(string_input):


# Handle any other text message
@bot.message_handler(func=lambda message: True)
def handle_message(message):
    string_input = message.text
    length_input = len(string_input)

    print(length_input)
    print(string_input)
    print(string_input[9:])
    print(string_input[0:9])

    string_response = ""

    if ("settings:" != string_input[0:9]):
        string_response = "I don't understand."
    else:
        settings = string_input[9:].split(";")
        length_settings = len(settings)

        if (2 != length_settings):
            string_response = "Missing settings parameters."
        else:
            print(length_settings)
            print(settings)

            is_numeric = []
            is_numeric.append(settings[0].isnumeric())
            is_numeric.append(settings[1].isnumeric())

            print(is_numeric)

            if (False == is_numeric[0] or 
                False == is_numeric[1]):
                string_response = "One of settings parameters is not numeric."
            else:
                device_id = int(settings[0])
                device_mode = int(settings[1])

                if (device_id < 0 or device_id > 255):
                    string_response = "device_id is invalid."


                string_response = "Settings received. device_id=" + str(device_id) + "; device_mode=" + str(device_mode)


    bot.send_message(message.chat.id, string_response)


    # bot.reply_to(message, message.text)

Thread(target=schedule_checker).start() # Notice that you refer to schedule_checker function which starts the job

bot.polling() # Also notice that you need to include polling to allow your bot to get commands from you. But it should happen AFTER threading!
