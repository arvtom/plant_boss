#Init server which writes/reads from database

uwsgi --http 0.0.0.0:9999 --wsgi-file /home/pi/github/plant_boss/sw_rpi/request_handler.py

#Check if server accepts data from other devices

#curl -X POST -d "timestamp=1.39&device=1&humidity=1.49&light=1.59&temperature=1.69&bat_voltage=1.79&rssi_wifi=1.89" 192.168.8.139:9999/

#Check if data was put into database from other devices

#curl 192.168.8.139:9999/