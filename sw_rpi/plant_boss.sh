# The purpose of this script is to start all necessary processes on rpi needed for plant_boss system, including: webpage, telegram bot.
# Using &> to save standard output and standard error stream to log file. Using & to return executing next bash commands.

cd /home/pi/github/plant_boss/sw_rpi

# Nginx features are not used at the moment
# sudo cp nginx/default /etc/nginx/sites-available/default &> log/plant_boss.log
# sudo systemctl stop nginx &> log/plant_boss.log
# sudo systemctl start nginx &> log/plant_boss.log

# Stop existing uwsgi process
sudo systemctl stop plant_boss_uwsgi.service &> log/plant_boss.log
sudo systemctl stop plant_boss_telegram_bot.service &> log/plant_boss.log

# Wait 5s until previous uwsgi process releases port and python closes.
sleep 5 &> log/plant_boss.log

# Copy systemd service scripts
sudo cp systemd/plant_boss_uwsgi.service /lib/systemd/system/plant_boss_uwsgi.service &> log/plant_boss.log
sudo cp systemd/plant_boss_telegram_bot.service /lib/systemd/system/plant_boss_telegram_bot.service &> log/plant_boss.log

# Start systemd services
sudo systemctl daemon-reload &> log/plant_boss.log
sudo systemctl enable plant_boss_uwsgi.service &> log/plant_boss.log
sudo systemctl enable plant_boss_telegram_bot.service &> log/plant_boss.log
sudo systemctl start plant_boss_uwsgi.service &> log/plant_boss.log
sudo systemctl start plant_boss_telegram_bot.service &> log/plant_boss.log

echo "plant_boss.sh done" &> log/plant_boss.log
