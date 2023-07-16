#According to: https://opensource.com/article/21/3/web-hosting-raspberry-pi

#Install packages

#sudo apt-get install sqlite3 build-essential python3
#pip install uwsgi

#Create and open database

#sqlite3 /home/pi/plant_boss/plant_boss.db

#Create new table in database

# CREATE TABLE plant_boss_test_3 (
# id INTEGER PRIMARY KEY AUTOINCREMENT,
# timestamp TEXT NOT NULL, 
# device INTEGER NOT NULL, 
# humidity DECIMAL NOT NULL, 
# light DECIMAL NOT NULL, 
# temperature DECIMAL NOT NULL,
# bat_voltage DECIMAL NOT NULL,
# rssi_wifi INTEGER NOT NULL,
# mode INTEGER NOT NULL,
# bat_low_flag INTEGER NOT NULL,
# error_app INTEGER NOT NULL,
# error_input INTEGER NOT NULL,
# error_output INTEGER NOT NULL,
# error_network INTEGER NOT NULL,
# error_memory INTEGER NOT NULL,
# sw_version INTEGER NOT NULL,
# timer_or_period INTEGER NOT NULL);

#Show database structure

#.tables
#.schema

#Allow 9999 port through firewall, to receive POST requests from other devices

#sudo ufw allow 9999
