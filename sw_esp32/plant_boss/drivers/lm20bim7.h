/**
*  \file    lm20bim7.h
*  \brief   This file contains functions for reading temperature sensor lm20bim7 data.
*  \author  arvtom
*/

#ifndef LM20BIM7_H
#define LM20BIM7_H

/*------------------------------Includes------------------------------*/
#include <stdbool.h>

#include <esp_log.h>

#include "error.h"
#include "adc_wrapper.h"

/*------------------------------Defines------------------------------*/

/*------------------------------Structures / enumerators------------------------------*/
typedef enum
{
    LM20BIM7_ERROR_INIT_ADC                 = 0x00000001U,
    LM20BIM7_ERROR_HANDLE_ADC               = 0x00000002U,
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
} lm20bim7_error_t;

/*------------------------------Public function prototypes------------------------------*/
bool lm20bim7_init(void);
bool lm20bim7_handle(void);

float lm20bim7_get_temperature_value(void);

/*------------------------------Private function prototypes------------------------------*/

#endif /* LM20BIM7_H */