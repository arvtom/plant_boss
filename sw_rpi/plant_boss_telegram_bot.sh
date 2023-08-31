cd /home/pi/github/plant_boss/sw_rpi

# Create new log file
touch log/telegram_bot.log

# Start telegram_bot.py as a background process
python telegram_bot.py &> log/telegram_bot.log &