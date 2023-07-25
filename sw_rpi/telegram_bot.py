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
    bot.send_message(CHAT_ID, "This is telegram bot printing message every 1 min.")
    

scheduler = BlockingScheduler(timezone="Europe/Berlin") # You need to add a timezone, otherwise it will give you a warning
scheduler.add_job(run_scheduled_task, trigger="cron", minute = "*") # Runs every minute

def schedule_checker():
    while True:
        scheduler.start()

@bot.message_handler(commands=['help'])
def print_help(message):
    string_response = """
        The purpose of this telegram bot:\r\n
        * Send periodic notifications about plant environment parameters (soil humidity, temperature, amount of light).\r\n
        * Send notifications when plant needs to be watered ASAP.\r\n
        * Edit settings for plant_boss devices.\r\n\r\n

        To change settings for plant_boss device, enter message in following format:\r\n
        * /plant_boss_settings\r\n
        * device_id; mode (0 for real time, 1 for normal with sleep functionality);\r\n
    """

    bot.send_message(message.chat.id, 'string_response')

Thread(target=schedule_checker).start() # Notice that you refer to schedule_checker function which starts the job

bot.polling() # Also notice that you need to include polling to allow your bot to get commands from you. But it should happen AFTER threading!
