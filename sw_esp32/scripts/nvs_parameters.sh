#!/bin/bash

# The purpose of this bash script:
#	calculate flash image crc
#	generate nvs partition with embedded CRC value and default parameters
#	flash nvs partition

# Constants
ESPIDF_PYTHON="/mnt/c/Users/Arvydas/.espressif/python_env/idf5.1_py3.11_env/Scripts/python.exe"
ESPIDF_NVS_PARTITION_GEN="C:/Users/Arvydas/esp/v5.1.2/esp-idf/components/nvs_flash/nvs_partition_generator/nvs_partition_gen.py"
ESPTOOL="C:/Users/Arvydas/.espressif/python_env/idf5.1_py3.11_env/Scripts/esptool.py"

LOCAL_PYTHON="python3"

HERE_WIN="C:/repo/plant_boss/sw_esp32/scripts"
HERE_WSL="/mnt/c/repo/plant_boss/sw_esp32/scripts"
NVS_PARTITION_DEF="$HERE_WIN/nvs_parameters.csv"
NVS_PARTITION_OUT="$HERE_WIN/nvs_parameters.bin"
NVS_PARTITION_SIZE_DEFAULT="0x6000"
NVS_PARTITION_OFFSET_DEFAULT="0x9000"

NO_ERROR=0
ERROR=1

CSV_ROW_CRC=13
CSV_COLUMN_CRC=4

crc="255"

# generated with chat gpt
update_csv() {
    local csv_file=$1
    local row=$2
    local column=$3
    local value=$4

    # Create a temporary file
    temp_file=$(mktemp)

    # Read the CSV file line by line
    line_num=0
    while IFS=, read -r line; do
        ((line_num++))
        if [ $((line_num-1)) -eq $row ]; then
            # Split the line into an array
            IFS=',' read -ra row_data <<< "$line"
            # Update the value in the specified column
            row_data[$((column-1))]=$value
            # Reconstruct the line with updated values
            modified_line=$(IFS=,; echo "${row_data[*]}")
            echo -n "$modified_line" >> "$temp_file"
        else
            # Write the line unchanged to the temporary file
            echo -n "$line" >> "$temp_file"
        fi
        # Ensure LF line endings
        echo -n $'\n' >> "$temp_file"
    done < "$csv_file"

    # Replace the original file with the updated one
    mv "$temp_file" "$csv_file"
	
	return $NO_ERROR
}

# Calculate flash image crc
crc=$($LOCAL_PYTHON $HERE_WSL/flash_image_crc.py)
if [[ $? -ne $NO_ERROR ]]; then
	echo "err flash_image_crc.py"
	exit $ERROR
fi

echo "crc=$crc"

# # write crc value to nvs partition .csv
# cat $nvs_partition_def
update_csv "$HERE_WSL/nvs_parameters.csv" $CSV_ROW_CRC $CSV_COLUMN_CRC $crc
if [[ $? -ne $NO_ERROR ]]; then
	echo "err embed crc"
	exit $ERROR
fi

# Generate nvs partition
$ESPIDF_PYTHON $ESPIDF_NVS_PARTITION_GEN generate $NVS_PARTITION_DEF $NVS_PARTITION_OUT $NVS_PARTITION_SIZE_DEFAULT
if [[ $? -ne $NO_ERROR ]]; then
	echo "err gen partition"
	exit $ERROR
fi

# Flash nvs partition
$ESPIDF_PYTHON $ESPTOOL write_flash $NVS_PARTITION_OFFSET_DEFAULT $NVS_PARTITION_OUT
if [[ $? -ne $NO_ERROR ]]; then
	echo "err flash partition"
	exit $ERROR
fi

echo "nvs_parameters finish"
exit $NO_ERROR