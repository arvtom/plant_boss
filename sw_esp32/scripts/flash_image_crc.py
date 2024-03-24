# The purpose of this python script is to calculate esp32 flash image CRC.

from crc import Calculator, Configuration

PATH_TO_IMAGE="../plant_boss/build/plant_boss.bin"

config = Configuration(
    width=32,
    polynomial=0x04c11db7,
    init_value=0x00000000,
    final_xor_value=0xffffffff,
    reverse_input=True,
    reverse_output=True,
)

test_bytes = bytes(
    [0x8c, 0xad, 0x08, 0xa5, 0x96, 0xff, 0x48, 0x61, 0x98, 0x61, 0x68])

file = open(PATH_TO_IMAGE, 'rb')

image = file.read()
image_size = len(image)
padding_size = 1048576 - image_size
padding = bytes([])

for i in range(0, padding_size):
    padding += bytes([0xFF])

image += padding

calculator = Calculator(config, optimized=True)
crc32_value = calculator.checksum(image)
crc32_value_hex = hex(crc32_value)
print(crc32_value)