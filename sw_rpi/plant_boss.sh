# The purpose of this script is to start all necessary processes on rpi needed for plant_boss system, including: webpage, telegram bot.
# Using &> to save standard output and standard error stream to log file.

# sudo cp nginx/default /etc/nginx/sites-available/default &> plant_boss.log

# sudo systemctl stop nginx &> plant_boss.log
# sudo systemctl start nginx &> plant_boss.log

# #Init server which writes/reads from database
# uwsgi --socket 127.0.0.1:8001 --wsgi-file /home/pi/github/plant_boss/sw_rpi/http_request_handler.py &> plant_boss.log
echo "plant_boss.sh done" &> plant_boss.log
