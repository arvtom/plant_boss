/**
*  \file    gpio_wrapper.h
*  \brief   This file wraps around esp32 gpio driver.
*  \author  arvtom
*/

/*------------------------------Includes------------------------------*/
#include <stdbool.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/gpio.h>
#include <esp_log.h>


/*------------------------------Defines------------------------------*/

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
// }gpio_error_t;

/*------------------------------Public function prototypes------------------------------*/
// bool gpio_init(void);
// bool gpio_handle(void);

bool gpio_init_pin(uint8_t pin, gpio_mode_t mode, gpio_pullup_t pull_up, gpio_pulldown_t pull_down, gpio_int_type_t intr);
bool gpio_handle_pin_output(uint8_t pin, bool level);

/*------------------------------Private function prototypes------------------------------*/