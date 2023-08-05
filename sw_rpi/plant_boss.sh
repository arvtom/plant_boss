# The purpose of this script is to start all necessary processes on rpi needed for plant_boss system, including: webpage, telegram bot.
# Using &> to save standard output and standard error stream to log file.

sudo cp nginx/default /etc/nginx/sites-available/default

sudo systemctl stop nginx
sudo systemctl start nginx

# Stop existing uwsgi process
killall -v uwsgi

# Wait 2s until previous uwsgi process releases port
sleep 2

# Start uwsgi as a background process
nohup bash -c "uwsgi --socket 127.0.0.1:8001 --wsgi-file /home/pi/github/plant_boss/sw_rpi/http_request_handler.py" &> uwsgi.log &

echo "plant_boss.sh done"
