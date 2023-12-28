sudo apt update
sudo apt-get -y install cppcheck sshpass python3-pip python3-venv libusb-1.0-0-dev minicom
pip install flawfinder lizard

# esp-idf also asks for:
# sudo cp -n /root/.espressif/tools/openocd-esp32/v0.12.0-esp32-20230921/openocd-esp32/share/openocd/contrib/60-openocd.rules /etc/udev/rules.d