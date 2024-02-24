#!/bin/bash

# The purpose of this bash script is to call python script which calculates flash image crc and embed it to NVM.

# Activate python venv
# ./.venv/Scripts/activate
# Using global packages instead

# Calculate CRC
python3 flash_image_crc.py

# Write CRC to target NVM


echo "flash_image_crc.sh finished"