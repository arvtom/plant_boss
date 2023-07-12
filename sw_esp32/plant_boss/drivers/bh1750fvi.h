/**
*  \file    bh1750fvi.h
*  \brief   This file contains functions for reading light sensor bh1750fvi data.
*  \author  arvtom
*/

/*------------------------------Includes------------------------------*/
#include <stdbool.h>
#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "i2c_wrapper.h"

/*------------------------------Defines------------------------------*/
#define BH1750FVI_I2C_ADDR_MEASURE          0x23
#define BH1750FVI_I2C_ADDR_RESULT           0x23

#define BH1750FVI_I2C_COMMAND_MEASURE       0x23

#define BH1750FVI_I2C_TIMEOUT               100u

/*------------------------------Structures / enumerators------------------------------*/
typedef enum
{
    BH1750FVI_ERROR_INIT        = 0x00000001U,
    BH1750FVI_ERROR_HANDLE      = 0x00000002U,
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
}bh1750fvi_error_t;

/*------------------------------Public function prototypes------------------------------*/
bool bh1750fvi_init(void);
bool bh1750fvi_handle(void);

/*------------------------------Private function prototypes------------------------------*/