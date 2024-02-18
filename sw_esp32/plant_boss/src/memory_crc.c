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
bool memory_crc_check_image_8bit(void)
{
    uint32_t flash_size = 0u;
    uint8_t flash_byte[FLASH_SEQUENTIAL_CRC_CHECK_LENGTH];
    memset(&flash_byte, 0u, FLASH_SEQUENTIAL_CRC_CHECK_LENGTH);
    uint8_t flash_crc_value = 0u;
    TickType_t tick_start = 0u;
    TickType_t tick_finish = 0u;
    TickType_t tick_diff = 0u;
    float crc_speed = 0.0f;
    uint32_t bytes_to_read = 0u;
    uint32_t remaining_bytes = 0u;

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
    flash_crc_value = crc8_le(~CRC32_INIT_VALUE, &flash_byte[0], 1u);

    tick_start = xTaskGetTickCount();

    /* Calculate remaining CRC iterations byte by byte */
    for (uint32_t i = FLASH_OFFSET_FACTORY_APP + 1u; i < FLASH_OFFSET_FACTORY_APP + FLASH_SIZE_FACTORY_APP; i += FLASH_SEQUENTIAL_CRC_CHECK_LENGTH)
    {
        remaining_bytes = FLASH_OFFSET_FACTORY_APP + FLASH_SIZE_FACTORY_APP - i - 1u;

        if (remaining_bytes > FLASH_SEQUENTIAL_CRC_CHECK_LENGTH)
        {
            bytes_to_read = FLASH_SEQUENTIAL_CRC_CHECK_LENGTH;
        }
        else
        {
            bytes_to_read = remaining_bytes;
        }
        
        if (ESP_OK != esp_flash_read(esp_flash_default_chip , &flash_byte[0], i, bytes_to_read))
        {
            printf("err flash r idx %lu\n", i);
        }

        flash_crc_value = crc8_le(flash_crc_value, &flash_byte[0], bytes_to_read);
    }

    /* Apply reflection of output and final xor */
    flash_crc_value = (~flash_crc_value) ^ CRC32_XOR_VALUE;

    tick_finish = xTaskGetTickCount();
    tick_diff = tick_finish - tick_start;

    crc_speed = (float)FLASH_SIZE_FACTORY_APP / ((float)tick_diff / 100.0f);

    printf("flash_crc_value 8bit=%X, calc took %lu ticks at %.1fB/s\n", flash_crc_value, tick_diff, crc_speed);

    return true;
}

bool memory_crc_check_image_32bit(void)
{
    uint32_t flash_size = 0u;
    uint8_t flash_byte[FLASH_SEQUENTIAL_CRC_CHECK_LENGTH];
    memset(&flash_byte, 0u, FLASH_SEQUENTIAL_CRC_CHECK_LENGTH);
    uint32_t flash_crc_value = 0u;
    TickType_t tick_start = 0u;
    TickType_t tick_finish = 0u;
    TickType_t tick_diff = 0u;
    float crc_speed = 0.0f;
    uint32_t bytes_to_read = 0u;
    uint32_t remaining_bytes = 0u;

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
    flash_crc_value = crc32_le(~CRC32_INIT_VALUE, &flash_byte[0], 1u);

    tick_start = xTaskGetTickCount();

    /* Calculate remaining CRC iterations byte by byte */
    for (uint32_t i = FLASH_OFFSET_FACTORY_APP + 1u; i < FLASH_OFFSET_FACTORY_APP + FLASH_SIZE_FACTORY_APP; i += FLASH_SEQUENTIAL_CRC_CHECK_LENGTH)
    {
        remaining_bytes = FLASH_OFFSET_FACTORY_APP + FLASH_SIZE_FACTORY_APP - i - 1u;

        if (remaining_bytes > FLASH_SEQUENTIAL_CRC_CHECK_LENGTH)
        {
            bytes_to_read = FLASH_SEQUENTIAL_CRC_CHECK_LENGTH;
        }
        else
        {
            bytes_to_read = remaining_bytes;
        }
        
        if (ESP_OK != esp_flash_read(esp_flash_default_chip , &flash_byte[0], i, bytes_to_read))
        {
            printf("err flash r idx %lu\n", i);
        }

        flash_crc_value = crc32_le(flash_crc_value, &flash_byte[0], bytes_to_read);
    }

    /* Apply reflection of output and final xor */
    flash_crc_value = (~flash_crc_value) ^ CRC32_XOR_VALUE;

    tick_finish = xTaskGetTickCount();
    tick_diff = tick_finish - tick_start;

    crc_speed = (float)FLASH_SIZE_FACTORY_APP / ((float)tick_diff / 100.0f);

    printf("flash_crc_value 32bit=%lX, calc took %lu ticks at %.1fB/s\n", flash_crc_value, tick_diff, crc_speed);

    return true;
}

/*------------------------------Private functions------------------------------*/
