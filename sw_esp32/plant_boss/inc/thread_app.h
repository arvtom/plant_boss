
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

#define TIMEOUT_WRITE_ERROR_TO_MEMORY   200U    /* x10 ms*/
#define TIMEOUT_SEND_ERROR_TO_NETWORK   1000U   /* x10 ms*/

typedef enum
{
    THREAD_APP_ERROR_INIT_COMMON_OBJECTS            = 0x0000000000000001U,
    THREAD_APP_ERROR_INIT_MEMORY                    = 0x0000000000000002U,
    THREAD_APP_ERROR_INIT_MEMORY_RES                = 0x0000000000000004U,
    THREAD_APP_ERROR_INIT_NETWORK                   = 0x0000000000000008U,
    THREAD_APP_ERROR_INIT_NETWORK_RES               = 0x0000000000000010U,
    THREAD_APP_ERROR_INIT_OUTPUT                    = 0x0000000000000020U,
    THREAD_APP_ERROR_INIT_OUTPUT_RES                = 0x0000000000000040U,
    THREAD_APP_ERROR_INIT_INPUT                     = 0x0000000000000080U,
    THREAD_APP_ERROR_INIT_INPUT_RES                 = 0x0000000000000100U,
    THREAD_APP_ERROR_HANDLE_REQ_SETTINGS            = 0x0000000000000200U,
    THREAD_APP_ERROR_HANDLE_REQ_SETTINGS_RES        = 0x0000000000000400U,
    THREAD_APP_ERROR_HANDLE_SENSORS                 = 0x0000000000000800U,
    THREAD_APP_ERROR_HANDLE_SENSORS_RES             = 0x0000000000001000U,
    THREAD_APP_ERROR_HANDLE_EXT_LED                 = 0x0000000000002000U,
    THREAD_APP_ERROR_HANDLE_EXT_LED_RES             = 0x0000000000004000U,
    THREAD_APP_ERROR_HANDLE_SLEEP_SETTINGS          = 0x0000000000008000U,
    THREAD_APP_ERROR_HANDLE_SETTINGS_LENGTH         = 0x0000000000010000U,
    THREAD_APP_ERROR_HANDLE_SETTINGS_TOKEN_1        = 0x0000000000020000U,
    THREAD_APP_ERROR_HANDLE_SETTINGS_TOKEN_2        = 0x0000000000040000U,
    THREAD_APP_ERROR_HANDLE_SETTINGS_BAT_THRESHOLD  = 0x0000000000080000U,
    THREAD_APP_ERROR_HANDLE_SETTINGS_DELAY          = 0x0000000000100000U,
    THREAD_APP_ERROR_HANDLE_SETTINGS_UNKNOWN        = 0x0000000000200000U,
    THREAD_APP_ERROR_REQ_NVM_CONTENTS               = 0x0000000000400000U,
    THREAD_APP_ERROR_RES_NVM_CONTENTS               = 0x0000000000800000U,
    THREAD_APP_ERROR_HANDLE_SETTINGS_MODE           = 0x0000000001000000U,
    // ERROR_BIT = 0x0000000002000000U,
    // ERROR_BIT = 0x0000000004000000U,
    // ERROR_BIT = 0x0000000008000000U,
    // ERROR_BIT = 0x0000000010000000U,
    // ERROR_BIT = 0x0000000020000000U,
    // ERROR_BIT = 0x0000000040000000U,
    // ERROR_BIT = 0x0000000080000000U,

    // ERROR_BIT = 0x0000000100000000U,
    // ERROR_BIT = 0x0000000200000000U,
    // ERROR_BIT = 0x0000000400000000U,
    // ERROR_BIT = 0x0000000800000000U,
    // ERROR_BIT = 0x0000001000000000U,
    // ERROR_BIT = 0x0000002000000000U,
    // ERROR_BIT = 0x0000004000000000U,
    // ERROR_BIT = 0x0000008000000000U,
    // ERROR_BIT = 0x0000010000000000U,
    // ERROR_BIT = 0x0000020000000000U,
    // ERROR_BIT = 0x0000040000000000U,
    // ERROR_BIT = 0x0000080000000000U,
    // ERROR_BIT = 0x0000100000000000U,
    // ERROR_BIT = 0x0000200000000000U,
    // ERROR_BIT = 0x0000400000000000U,
    // ERROR_BIT = 0x0000800000000000U,
    // ERROR_BIT = 0x0001000000000000U,
    // ERROR_BIT = 0x0002000000000000U,
    // ERROR_BIT = 0x0004000000000000U,
    // ERROR_BIT = 0x0008000000000000U,
    // ERROR_BIT = 0x0010000000000000U,
    // ERROR_BIT = 0x0020000000000000U,
    // ERROR_BIT = 0x0040000000000000U,
    // ERROR_BIT = 0x0080000000000000U,
    // ERROR_BIT = 0x0100000000000000U,
    // ERROR_BIT = 0x0200000000000000U,
    // ERROR_BIT = 0x0400000000000000U,
    // ERROR_BIT = 0x0800000000000000U,
    // ERROR_BIT = 0x1000000000000000U,
    // ERROR_BIT = 0x2000000000000000U,
    // ERROR_BIT = 0x4000000000000000U,
    // ERROR_BIT = 0x8000000000000000U,
} thread_app_error_t;

/* ---------------------------- Public functions ---------------------------- */
void thread_app(void *arg);
bool thread_app_init(void);
bool thread_app_handle(void);

void thread_app_handle_error(void);

/* ---------------------------- Private functions ---------------------------- */
bool thread_app_init_threads(void);

bool thread_app_handle_settings(void);
bool thread_app_handle_data_packet(void);

void thread_app_handle_error_write_memory(void);
void thread_app_handle_error_send_network(void);

/* ---------------------------- Interrupt callbacks ---------------------------- */

#endif
