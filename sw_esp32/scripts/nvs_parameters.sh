#!/bin/bash

# The purpose of this bash script:
#	calculate flash image crc
#	generate nvs partition with embedded CRC value and default parameters
#	flash nvs partition

# Constants
ESPIDF_PYTHON="/mnt/c/Users/Arvydas/.espressif/python_env/idf5.1_py3.11_env/Scripts/python.exe"
ESPIDF_NVS_PARTITION_GEN="C:/Users/Arvydas/esp/v5.1.2/esp-idf/components/nvs_flash/nvs_partition_generator/nvs_partition_gen.py"

LOCAL_PYTHON="python3"

HERE_WIN="C:/repo/plant_boss/sw_esp32/scripts"
HERE_WSL="/mnt/c/repo/plant_boss/sw_esp32/scripts"
NVS_PARTITION_DEF="$HERE_WIN/nvs_parameters.csv"
NVS_PARTITION_OUT="$HERE_WIN/nvs_parameters.bin"
NVS_PARTITION_SIZE_DEFAULT="0x6000"

NO_ERROR=0
ERROR=1

# Calculate flash image crc
$LOCAL_PYTHON $HERE_WSL/flash_image_crc.py
if [[ $? -ne $NO_ERROR ]]; then
	echo "err flash_image_crc.py"
	exit $ERROR
fi

# # write crc value to nvs partition .csv
# cat $nvs_partition_def
# if [[ $? -ne $no_error ]]; then
	# echo "err embed crc"
	# exit $error
# fi

# Generate nvs partition
$ESPIDF_PYTHON $ESPIDF_NVS_PARTITION_GEN generate $NVS_PARTITION_DEF $NVS_PARTITION_OUT $NVS_PARTITION_SIZE_DEFAULT
if [[ $? -ne $NO_ERROR ]]; then
	echo "err gen partition"
	exit $ERROR
fi

# Flash nvs partition

# if [[ $? -ne $NO_ERROR ]]; then
	# echo "err flash partition"
	# exit $ERROR
# fi

echo "nvs_parameters finish"
exit $NO_ERROR