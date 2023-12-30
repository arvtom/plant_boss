apt-get update
apt-get -y install sshpass python3-pip python3-venv libusb-1.0-0-dev minicom wget cmake
pip install flawfinder lizard

# Get newest version of cppcheck
cd /home
wget https://github.com/danmar/cppcheck/archive/refs/tags/2.13.0.tar.gz
tar -xf 2.13.0.tar.gz
cd cppcheck-2.13.0
mkdir build &&
cd build &&
cmake .. &&
cmake --build .

# esp-idf also asks for:
# sudo cp -n /root/.espressif/tools/openocd-esp32/v0.12.0-esp32-20230921/openocd-esp32/share/openocd/contrib/60-openocd.rules /etc/udev/rules.dcd ..