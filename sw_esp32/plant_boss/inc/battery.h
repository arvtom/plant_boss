/**
*  \file    battery.h
*  \brief   This file contains functions for battery management.
*  \author  arvtom
*/

#ifndef BATTERY_H
#define BATTERY_H

/*------------------------------Includes------------------------------*/
#include <stdbool.h>

#include <esp_log.h>

#include "error.h"
#include "adc_wrapper.h"

/*------------------------------Defines------------------------------*/
#define THRESHOLD_VOLTAGE_BATTERY 3400

/*------------------------------Structures / enumerators------------------------------*/
typedef enum
{
    BATTERY_ERROR_INIT_ADC                  = 0x00000001U,
    BATTERY_ERROR_HANDLE_ADC                = 0x00000002U,
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
} battery_error_t;

/*------------------------------Public function prototypes------------------------------*/
bool battery_init(void);
bool battery_handle(void);

float battery_get_voltage_value(void);

/*------------------------------Private function prototypes------------------------------*/

#endif /* BATTERY_H */
