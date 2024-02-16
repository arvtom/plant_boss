/**
*  \file    memory_crc.h
*  \brief   This file contains functions for checking memory crc.
*  \author  arvtom
*/

#ifndef MEMORY_CRC_H
#define MEMORY_CRC_H

/*------------------------------Includes------------------------------*/
#include <stdbool.h>
#include <esp_log.h>
#include <esp_flash_spi_init.h>
#include <rom/crc.h>

/*------------------------------Defines------------------------------*/
#define CRC32_INIT_VALUE            (0x00000000)
#define CRC32_XOR_VALUE             (0xffffffff)
#define CRC32_POLYNOME              (0x04c11db7)        /* already used by crc32_le function from esp lib. */
#define CRC32_REFLECT_IN_TRUE                           /* already used in source code */
#define CRC32_REFLECT_OUT_TRUE                          /* already used in source code */

/*------------------------------Structures / enumerators------------------------------*/
// typedef enum
// {
//     BATTERY_ERROR_INIT_ADC                  = 0x00000001U,
//     BATTERY_ERROR_HANDLE_ADC                = 0x00000002U,
//     // ERROR_BIT = 0x00000004U,
//     // ERROR_BIT = 0x00000008U,
//     // ERROR_BIT = 0x00000010U,
//     // ERROR_BIT = 0x00000020U,
//     // ERROR_BIT = 0x00000040U,
//     // ERROR_BIT = 0x00000080U,
//     // ERROR_BIT = 0x00000100U,
//     // ERROR_BIT = 0x00000200U,
//     // ERROR_BIT = 0x00000400U,
//     // ERROR_BIT = 0x00000800U,
//     // ERROR_BIT = 0x00001000U,
//     // ERROR_BIT = 0x00002000U,
//     // ERROR_BIT = 0x00004000U,
//     // ERROR_BIT = 0x00008000U,
//     // ERROR_BIT = 0x00010000U,
//     // ERROR_BIT = 0x00020000U,
//     // ERROR_BIT = 0x00040000U,
//     // ERROR_BIT = 0x00080000U,
//     // ERROR_BIT = 0x00100000U,
//     // ERROR_BIT = 0x00200000U,
//     // ERROR_BIT = 0x00400000U,
//     // ERROR_BIT = 0x00800000U,
//     // ERROR_BIT = 0x01000000U,
//     // ERROR_BIT = 0x02000000U,
//     // ERROR_BIT = 0x04000000U,
//     // ERROR_BIT = 0x08000000U,
//     // ERROR_BIT = 0x10000000U,
//     // ERROR_BIT = 0x20000000U,
//     // ERROR_BIT = 0x40000000U,
//     // ERROR_BIT = 0x80000000U,
// } battery_error_t;

/*------------------------------Public function prototypes------------------------------*/
bool memory_crc_check_image(void);

/*------------------------------Private function prototypes------------------------------*/

#endif /* MEMORY_CRC_H */
