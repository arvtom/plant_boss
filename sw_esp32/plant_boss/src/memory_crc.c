/**
*  \file    memory_crc.c
*  \brief   This file contains functions for checking memory crc.
*  \author  arvtom
*/

/*------------------------------Includes------------------------------*/
#include "memory_crc.h"

/*------------------------------Defines------------------------------*/
static const char* tag_crc = "crc";

/*------------------------------Variables / Macro calls------------------------------*/


/*------------------------------Public functions------------------------------*/
bool memory_crc_check_image(void)
{
    uint32_t flash_size = 0u;
    uint8_t flash_byte = 0u;
    uint32_t flash_crc_value = 0u;

    if (ESP_OK != esp_flash_get_physical_size(esp_flash_default_chip, &flash_size))
    {
        printf("err flash_size r\n");
    }

    printf("flash_size=0x%lX\n", flash_size);

    /* Calculate first CRC iteration using CRC init value */
    if (ESP_OK != esp_flash_read(esp_flash_default_chip , &flash_byte, FLASH_OFFSET_FACTORY_APP, 1))
    {
        printf("err flash r\n");
    }

    /* Apply reflection of input */
    flash_crc_value = crc32_le(~CRC32_INIT_VALUE, &flash_byte, 1u);

    printf("start calc flash crc\n");

    /* Calculate remaining CRC iterations byte by byte */
    for (uint32_t i = FLASH_OFFSET_FACTORY_APP + 1u; i < FLASH_OFFSET_FACTORY_APP + FLASH_SIZE_TEST; i++)
    {
        if (ESP_OK != esp_flash_read(esp_flash_default_chip , &flash_byte, i, 1))
        {
            printf("err flash r idx %lu\n", i);
        }

        flash_crc_value = crc32_le(flash_crc_value, &flash_byte, 1u);
        printf("%lu\n", i);
    }

    /* Apply reflection of output and final xor */
    flash_crc_value = (~flash_crc_value) ^ CRC32_XOR_VALUE;

    printf("flash_crc_value=%lX\n", flash_crc_value);

    return true;
}

/*------------------------------Private functions------------------------------*/
