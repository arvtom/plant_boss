sudo cp nginx/default /etc/nginx/sites-available/default

sudo systemctl stop nginx
sudo systemctl start nginx

#Init server which writes/reads from database
nohup uwsgi --socket 127.0.0.1:8001 --wsgi-file /home/pi/github/plant_boss/sw_rpi/uwsgi_plant_boss.py > uwsgi_plant_boss.log
#nohup uwsgi --socket 127.0.0.1:8002 --wsgi-file /home/pi/github/plant_boss/sw_rpi/uwsgi_plant_boss_settings.py > uwsgi_plant_boss_settings.log
#nohup uwsgi --socket 127.0.0.1:8003 --wsgi-file /home/pi/github/plant_boss/sw_rpi/uwsgi_plant_boss_plot.py > uwsgi_plant_boss_plot.log

#Check if server accepts data from other devices

#curl -X POST -d "timestamp=1.39&device=1&humidity=1.49&light=1.59&temperature=1.69&bat_voltage=1.79&rssi_wifi=1.89" 192.168.8.139:9999/

#Check if data was put into database from other devices

#curl 192.168.8.139:9999/
