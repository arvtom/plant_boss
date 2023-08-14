# The purpose of this script is to transfer plant_boss/sw_rpi folder from development machine to rpi and start plant_boss software automatically.

# Get pw_rpi, path_scp and path_ssh
source settings_test_rpi.sh

# Call scp to copy test scripts to rpi. Use sshpass to provide pass.
sshpass -p $pw_rpi scp -r /home/arvydas/github/plant_boss/sw_rpi $path_scp

# Call plant_boss script to start all needed processes on rpi
echo "bash plant_boss.sh" | sshpass -p $pw_rpi ssh pi@192.168.8.139

echo "test_rpi.sh done"
