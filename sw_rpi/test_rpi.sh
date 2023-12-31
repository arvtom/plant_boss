# The purpose of this script is to transfer plant_boss/sw_rpi folder from development machine to rpi and start plant_boss software automatically.

# Get pw_rpi, path_scp and path_ssh
source settings_test_rpi.sh

# Call scp to copy test scripts to rpi. Use sshpass to provide pass.
# Copy all contents of sw_rpi except .db file.
cd /home/arvydas/github/plant_boss/sw_rpi
shopt -s extglob
# sshpass -p $pw_rpi scp /home/arvydas/github/plant_boss/sw_rpi/!(plant_boss.db) -r $path_scp
sshpass -p $pw_rpi scp -r !(plant_boss.db) $path_scp

# Call plant_boss script to start all needed processes on rpi
echo "bash /home/pi/github/plant_boss/sw_rpi/plant_boss.sh" | sshpass -p $pw_rpi ssh pi@192.168.1.101

echo "test_rpi.sh done"
