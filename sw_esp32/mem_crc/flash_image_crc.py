# The purpose of this python script is to calculate esp32 flash image CRC and embed it's value in image.

PATH_TO_IMAGE="../plant_boss/build/plant_boss.bin"

print("python start")

# with open(PATH_TO_IMAGE, 'r') as fp:
#     hex_list = ["{:02x}".format(ord(c)) for c in fp.read()]

# print("hexlist=" + hex_list[:10])

file = open(PATH_TO_IMAGE, 'rb')

image = file.read()
image_size = len(image)

print("size of image: " + str(image_size))
print("first 10 bytes of image: " + str(image[:10]))
print("last 10 bytes of image: " + str(image[image_size-10:]))

from crc import Calculator, Configuration

config = Configuration(
    width=8,
    polynomial=0x07,
    init_value=0x00,
    final_xor_value=0x00,
    reverse_input=False,
    reverse_output=False,
)

calculator = Calculator(config, optimized=True)

crc32_value = calculator.checksum(image)

print("python finish")