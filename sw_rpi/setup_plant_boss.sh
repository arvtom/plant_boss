#According to: https://opensource.com/article/21/3/web-hosting-raspberry-pi

#Install packages

#sudo apt-get install sqlite3 build-essential python3
#pip install uwsgi

#Create and open database

#sqlite3 /home/pi/plant_boss/plant_boss.db

#Create new table in database

#CREATE TABLE plant_boss_table_x (
#id INTEGER PRIMARY KEY AUTOINCREMENT,
#timestamp DECIMAL NOT NULL, 
#device DECIMAL NOT NULL, 
#humidity DECIMAL NOT NULL, 
#light DECIMAL NOT NULL, 
#temperature DECIMAL NOT NULL,
#bat_voltage DECIMAL NOT NULL,
#rssi_wifi DECIMAL NOT NULL);

#Show database structure

#.tables
#.schema

#Allow 9999 port through firewall, to receive POST requests from other devices

#sudo ufw allow 9999
