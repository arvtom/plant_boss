# The purpose of this script is to start all necessary processes on rpi needed for plant_boss system, including: webpage, telegram bot.
# Using &> to save standard output and standard error stream to log file.

sudo cp nginx/default /etc/nginx/sites-available/default

sudo systemctl stop nginx
sudo systemctl start nginx

# Stop existing uwsgi process
killall -v uwsgi

# Stop existing process of telegram_bot.py
killall -v python

# Wait 5s until previous uwsgi process releases port and python closes.
sleep 5

# Start uwsgi as a background process
nohup bash -c "uwsgi --socket 127.0.0.1:8001 --wsgi-file http_request_handler.py" &> uwsgi.log &

# Start telegram_bot.py as a background process
nohup bash -c "python telegram_bot.py" &> telegram_bot.log &

echo "plant_boss.sh done"
