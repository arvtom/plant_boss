/**
*  \file    i2c_wrapper.h
*  \brief   This file wraps around esp32 i2c driver.
*  \author  arvtom
*/

#ifndef I2C_WRAPPER_H
#define I2C_WRAPPER_H

/*------------------------------Includes------------------------------*/
#include <stdbool.h>

#include <driver/i2c.h>
#include <esp_log.h>

#include "error.h"

/*------------------------------Defines------------------------------*/

/*------------------------------Structures / enumerators------------------------------*/
typedef enum
{
    I2C_ERROR_INIT_PARAM                = 0x00000001U,
    I2C_ERROR_INIT_DRIVER               = 0x00000002U,
    I2C_ERROR_HANDLE_WRITE              = 0x00000004U,
    I2C_ERROR_HANDLE_READ               = 0x00000008U,
    // I2C_ERROR_INIT_DRIVER               = 0x00000010U,
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
}i2c_error_t;

/*------------------------------Public function prototypes------------------------------*/
bool i2c_init(void);
// bool i2c_handle(void);

bool i2c_handle_write(uint8_t addr, uint8_t* p_buf, uint8_t count, uint8_t timeout);
bool i2c_handle_read(uint8_t addr, uint8_t* p_buf, uint8_t count, uint8_t timeout);

/*------------------------------Private function prototypes------------------------------*/

#endif /* I2C_WRAPPER_H */