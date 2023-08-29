/**
*  \file    hw390.h
*  \brief   This file contains functions for reading soil moisture sensor hw390 data.
*  \author  arvtom
*/

/*------------------------------Includes------------------------------*/
#include <stdbool.h>
#include <esp_log.h>

#include "adc_wrapper.h"

/*------------------------------Defines------------------------------*/
#define HW_390_HUMIDITY_OFFSET      (138.0)
#define HW_390_HUMIDITY_SCALE       -0.0667

/*------------------------------Structures / enumerators------------------------------*/
// typedef enum
// {
    // ERROR_BIT = 0x00000001U,
    // ERROR_BIT = 0x00000002U,
    // ERROR_BIT = 0x00000004U,
    // ERROR_BIT = 0x00000008U,
    // ERROR_BIT = 0x00000010U,
    // ERROR_BIT = 0x00000020U,
    // ERROR_BIT = 0x00000040U,
    // ERROR_BIT = 0x00000080U,
    // ERROR_BIT = 0x00000100U,
    // ERROR_BIT = 0x00000200U,
    // ERROR_BIT = 0x00000400U,
    // ERROR_BIT = 0x00000800U,
    // ERROR_BIT = 0x00001000U,
    // ERROR_BIT = 0x00002000U,
    // ERROR_BIT = 0x00004000U,
    // ERROR_BIT = 0x00008000U,
    // ERROR_BIT = 0x00010000U,
    // ERROR_BIT = 0x00020000U,
    // ERROR_BIT = 0x00040000U,
    // ERROR_BIT = 0x00080000U,
    // ERROR_BIT = 0x00100000U,
    // ERROR_BIT = 0x00200000U,
    // ERROR_BIT = 0x00400000U,
    // ERROR_BIT = 0x00800000U,
    // ERROR_BIT = 0x01000000U,
    // ERROR_BIT = 0x02000000U,
    // ERROR_BIT = 0x04000000U,
    // ERROR_BIT = 0x08000000U,
    // ERROR_BIT = 0x10000000U,
    // ERROR_BIT = 0x20000000U,
    // ERROR_BIT = 0x40000000U,
    // ERROR_BIT = 0x80000000U,
// }hw390_error_t;

/*------------------------------Public function prototypes------------------------------*/
bool hw390_init(void);
bool hw390_handle(void);

float hw390_get_humidity_value(void);

/*------------------------------Private function prototypes------------------------------*/