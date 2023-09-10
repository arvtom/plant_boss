
#ifndef THREAD_APP_H
#define THREAD_APP_H

/* ---------------------------- Includes ---------------------------- */
#include <stdio.h>
#include <string.h>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>
#include <freertos/queue.h>
#include <esp_log.h>
#include <esp_sleep.h>

#include "wifi_wrapper.h"
#include "common_thread_objects.h"
#include "error.h"

/* ---------------------------- Typedefs ---------------------------- */
#define TIME_SLEEP (5U * 1000000U) //5 seconds

typedef enum
{
    THREAD_APP_ERROR_INIT_COMMON_OBJECTS            = 0x00000001U,
    THREAD_APP_ERROR_INIT_MEMORY                    = 0x00000002U,
    THREAD_APP_ERROR_INIT_MEMORY_RES                = 0x00000004U,
    THREAD_APP_ERROR_INIT_NETWORK                   = 0x00000008U,
    THREAD_APP_ERROR_INIT_NETWORK_RES               = 0x00000010U,
    THREAD_APP_ERROR_INIT_OUTPUT                    = 0x00000020U,
    THREAD_APP_ERROR_INIT_OUTPUT_RES                = 0x00000040U,
    THREAD_APP_ERROR_INIT_INPUT                     = 0x00000080U,
    THREAD_APP_ERROR_INIT_INPUT_RES                 = 0x00000100U,
    THREAD_APP_ERROR_HANDLE_REQ_SETTINGS            = 0x00000200U,
    THREAD_APP_ERROR_HANDLE_REQ_SETTINGS_RES        = 0x00000400U,
    THREAD_APP_ERROR_HANDLE_SENSORS                 = 0x00000800U,
    THREAD_APP_ERROR_HANDLE_SENSORS_RES             = 0x00001000U,
    THREAD_APP_ERROR_HANDLE_EXT_LED                 = 0x00002000U,
    THREAD_APP_ERROR_HANDLE_EXT_LED_RES             = 0x00004000U,
    THREAD_APP_ERROR_HANDLE_SLEEP_SETTINGS          = 0x00008000U,
    THREAD_APP_ERROR_HANDLE_SETTINGS_LENGTH         = 0x00010000U,
    THREAD_APP_ERROR_HANDLE_SETTINGS_TOKEN_1        = 0x00020000U,
    THREAD_APP_ERROR_HANDLE_SETTINGS_TOKEN_2        = 0x00040000U,
    THREAD_APP_ERROR_HANDLE_SETTINGS_BAT_THRESHOLD  = 0x00080000U,
    THREAD_APP_ERROR_HANDLE_SETTINGS_DELAY          = 0x00100000U,
    THREAD_APP_ERROR_HANDLE_SETTINGS_UNKNOWN        = 0x00200000U,
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
} thread_app_error_t;

/* ---------------------------- Public functions ---------------------------- */
void thread_app(void *arg);
bool thread_app_init(void);
bool thread_app_handle(void);
uint8_t app_function(void);

/* ---------------------------- Private functions ---------------------------- */
bool thread_app_handle_settings(void);
bool thread_app_handle_data_packet(void);

/* ---------------------------- Interrupt callbacks ---------------------------- */

#endif
