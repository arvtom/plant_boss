#!/bin/bash

# The purpose of this bash script is to call python script generates nvs partition with embedded CRC value and default parameters

/mnt/c/Users/Arvydas/.espressif/python_env/idf5.1_py3.11_env/Scripts/python.exe C:/Users/Arvydas/esp/v5.1.2/esp-idf/components/nvs_flash/nvs_partition_generator/nvs_partition_gen.py generate C:/repo/plant_boss/sw_esp32/nvs_parameters.csv C:/repo/plant_boss/sw_esp32/nvs_parameters.bin 0x6000
echo "nvs_parameters finish"