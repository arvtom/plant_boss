# The purpose of this script is to transfer plant_boss/sw_rpi folder from development machine to rpi and start plant_boss software automatically.

# Get pw_rpi
source settings_test_rpi.sh

echo $pw_rpi

#scp -r /home/arvydas/github/plant_boss/sw_rpi pi@192.168.8.139:/home/pi/github/plant_boss/sw_rpi

#ssh pi@192.168.8.139 "bash -s" /home/pi/github/plant_boss/sw_rpi/plant_boss.sh

#echo "done"
