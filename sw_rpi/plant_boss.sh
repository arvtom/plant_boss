# The purpose of this script is to start all necessary processes on rpi needed for plant_boss system, including: webpage, telegram bot.
# Using &> to save standard output and standard error stream to log file.

sudo cp nginx/default /etc/nginx/sites-available/default &> plant_boss.log

sudo systemctl stop nginx &> plant_boss.log
sudo systemctl start nginx &> plant_boss.log

#Init server which writes/reads from database
uwsgi --socket 127.0.0.1:8001 --wsgi-file /home/pi/github/plant_boss/sw_rpi/http_request_handler.py &> plant_boss.log
# nohup uwsgi --socket 127.0.0.1:8001 --wsgi-file /home/pi/github/plant_boss/sw_rpi/http_request_handler.py > uwsgi_plant_boss.log

#Check if server accepts data from other devices

#curl -X POST -d "timestamp=1.39&device=1&humidity=1.49&light=1.59&temperature=1.69&bat_voltage=1.79&rssi_wifi=1.89" 192.168.8.139:9999/

#Check if data was put into database from other devices

#curl 192.168.8.139:9999/
