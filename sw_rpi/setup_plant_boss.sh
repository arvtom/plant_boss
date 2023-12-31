#According to: https://opensource.com/article/21/3/web-hosting-raspberry-pi

# Linux: 2023-05-03-raspios-bullseye-armhf.img.xz.

#Install packages
#sudo apt-get update
#sudo apt-get upgrade
#sudo apt-get install sqlite3 nginx

# This seems quicker to install matplotlib, since pip tries to build matplotlib from source on rpi zero, which is painfully slow.
#sudo apt install python3-matplotlib

#pip install uwsgi telebot APScheduler

#Create and open database
#sqlite3 /home/pi/plant_boss/plant_boss.db

#Create new data table in sqlite3
CREATE TABLE plant_boss_test_3 (
id INTEGER PRIMARY KEY AUTOINCREMENT,
timestamp TEXT NOT NULL, 
device INTEGER NOT NULL, 
humidity DECIMAL NOT NULL, 
light DECIMAL NOT NULL, 
temperature DECIMAL NOT NULL,
bat_voltage DECIMAL NOT NULL,
rssi_wifi INTEGER NOT NULL,
mode INTEGER NOT NULL,
bat_low_flag INTEGER NOT NULL,
error_app INTEGER NOT NULL,
error_input INTEGER NOT NULL,
error_output INTEGER NOT NULL,
error_network INTEGER NOT NULL,
error_memory INTEGER NOT NULL,
sw_version INTEGER NOT NULL,
timer_or_period INTEGER NOT NULL);

#Create new settings table in sqlite3
CREATE TABLE plant_boss_settings_test_4 (
id INTEGER PRIMARY KEY AUTOINCREMENT,
timestamp TEXT NOT NULL, 
device INTEGER NOT NULL, 
mode INTEGER NOT NULL,
threshold_bat_voltage DECIMAL NOT NULL,
period_measurement DECIMAL NOT NULL);

# To delete all rows in table:
DELETE FROM plant_boss_settings_test_3;

# To delete table:
DROP TABLE plant_boss_test_3

#Show database structure

#.tables
#.schema

#Allow 9999 port through firewall, to receive POST requests from other devices

#sudo ufw allow 9999

#Copy nginx configuration to add more locations (paths) in server
#cp nginx/default /etc/nginx/sites-available

# Set up autostart on boot
# cp /home/pi/github/plant_boss/sw_rpi/systemd/plant_boss.process /lib/systemd/system/plant_boss.process
# sudo systemctl daemon-reload
# sudo systemctl enable plant_boss.service

# Check systemd process result:
# sudo systemctl status plant_boss.service

# Start systemd process manually:
# sudo systemctl start plant_boss.service

# Display running processes
# ps aux

