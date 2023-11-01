/**
*  \file    nvm_wrapper.h
*  \brief   This file wraps around esp32 nvs driver.
*  \author  arvtom
*/

#ifndef NVM_WRAPPER_H
#define NVM_WRAPPER_H

/*------------------------------Includes------------------------------*/
#include <stdbool.h>

#include <esp_log.h>
#include <nvs_flash.h>

#include "error.h"

/*------------------------------Defines------------------------------*/
#define KEY_NVS_DEVICE_ID                     "0"
#define KEY_NVS_DEVICE_MODE                   "1"
#define KEY_NVS_THRESHOLD_BAT_VOLTAGE         "2"
#define KEY_NVS_PERIOD_MEASUREMENT            "3"
#define KEY_NVS_CALIBRATION_SCALE             "4"
#define KEY_NVS_CALIBRATION_OFFSET            "5"
#define KEY_NVS_ERROR_APP                     "6"
#define KEY_NVS_ERROR_INPUT                   "7"
#define KEY_NVS_ERROR_OUTPUT                  "8"
#define KEY_NVS_ERROR_NETWORK                 "9"
#define KEY_NVS_ERROR_MEMORY                  "10"

/*------------------------------Structures / enumerators------------------------------*/
typedef enum
{
    NVM_ERROR_INIT = 0x00000001U,
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
} nvm_error_t;

typedef struct
{
    uint8_t id;
    uint8_t mode;
    uint16_t bat_threshold;
    uint32_t measurement_period;
    float calibration_scale;
    float calibration_offset;
    uint64_t err_app;
    uint32_t err_input;
    uint32_t err_output;
    uint32_t err_network;
    uint32_t err_memory;
} nvm_contents_t;

/*------------------------------Public function prototypes------------------------------*/
bool nvm_init(void);

bool nvm_handle_read(void);
bool nvm_handle_write(void);

/*------------------------------Private function prototypes------------------------------*/

#endif /* NVM_WRAPPER_H */