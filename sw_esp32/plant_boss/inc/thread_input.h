
#ifndef THREAD_INPUT_H
#define THREAD_INPUT_H

/* ---------------------------- Includes ---------------------------- */
#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "error.h"
#include "adc_wrapper.h"
#include "gpio_wrapper.h"
#include "bh1750fvi.h"

/* ---------------------------- Typedefs ---------------------------- */
typedef enum
{
    // THREAD_INPUT_ERROR_INIT_ADC_1                           = 0x00000001U,
    // THREAD_INPUT_ERROR_INIT_ADC_CHANNEL_TEMPERATURE         = 0x00000002U,
    // THREAD_INPUT_ERROR_INIT_ADC_CHANNEL_HUMIDITY            = 0x00000004U,
    // THREAD_INPUT_ERROR_INIT_ADC_CHANNEL_BATTERY             = 0x00000008U,
    // THREAD_INPUT_ERROR_INIT_ADC_CALIBRATION_TEMPERATURE     = 0x00000010U,
    // THREAD_INPUT_ERROR_INIT_ADC_CALIBRATION_HUMIDITY        = 0x00000020U,
    // THREAD_INPUT_ERROR_INIT_ADC_CALIBRATION_BATTERY         = 0x00000040U,
    THREAD_INPUT_ERROR_INIT_GPIO_LIGHT_POWER                = 0x00000080U,
    THREAD_INPUT_ERROR_INIT_GPIO_LIGHT_RESET                = 0x00000100U,
    THREAD_INPUT_ERROR_INIT_GPIO_TEMPERATURE_POWER          = 0x00000200U,
    THREAD_INPUT_ERROR_INIT_GPIO_HUMIDITY_POWER             = 0x00000400U,
    THREAD_INPUT_ERROR_HANDLE_GPIO_LIGHT_POWER              = 0x00000800U,
    THREAD_INPUT_ERROR_HANDLE_GPIO_LIGHT_RESET              = 0x00001000U,
    THREAD_INPUT_ERROR_HANDLE_GPIO_TEMPERATURE_POWER        = 0x00002000U,
    THREAD_INPUT_ERROR_HANDLE_GPIO_HUMIDITY_POWER           = 0x00004000U,
    THREAD_INPUT_ERROR_INIT_I2C                             = 0x00008000U,
    THREAD_INPUT_ERROR_HANDLE_I2C                           = 0x00010000U,
    THREAD_INPUT_ERROR_HANDLE_ADC                           = 0x00020000U,
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
    // ERROR_BIT = 0x80000000U
}thread_input_error_t;

typedef struct
{
    uint32_t err;

}thread_input_t;

/* ---------------------------- Public functions ---------------------------- */
void thread_input(void *arg);
bool thread_input_init(void);
bool thread_input_handle(void);

/* ---------------------------- Private functions ---------------------------- */

/* ---------------------------- Interrupt callbacks ---------------------------- */

#endif
