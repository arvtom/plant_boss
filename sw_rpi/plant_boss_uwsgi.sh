cd /home/pi/github/plant_boss/sw_rpi

# Create new log file
touch log/uwsgi.log

# Start uwsgi as a background process
/home/pi/.local/bin/uwsgi --socket 127.0.0.1:8001 --wsgi-file http_request_handler.py &> log/uwsgi.log &