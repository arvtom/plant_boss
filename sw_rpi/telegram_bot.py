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
    bot.send_message(CHAT_ID, "This is a message to send.")
    

scheduler = BlockingScheduler(timezone="Europe/Berlin") # You need to add a timezone, otherwise it will give you a warning
scheduler.add_job(run_scheduled_task, trigger="cron", minute = "*") # Runs every minute

def schedule_checker():
    while True:
        scheduler.start()

@bot.message_handler(commands=['start', 'help'])
def print_hi(message):
    # bot.send_message(message.chat.id, 'Hi!, chat id is: ' + str(message.chat.id))
    bot.send_message(message.chat.id, 'Hi!')

Thread(target=schedule_checker).start() # Notice that you refer to schedule_checker function which starts the job

bot.polling() # Also notice that you need to include polling to allow your bot to get commands from you. But it should happen AFTER threading!
