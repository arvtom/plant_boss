
#ifndef THREAD_APP_H
#define THREAD_APP_H

/* ---------------------------- Includes ---------------------------- */
#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>
#include <freertos/queue.h>
#include <esp_log.h>
#include <esp_sleep.h>

#include <string.h>

#include "wifi_wrapper.h"
#include "common_thread_objects.h"
#include "error.h"

/* ---------------------------- Typedefs ---------------------------- */
#define TIME_SLEEP (5U * 1000000) //5 seconds

// typedef struct
// {

// }thread_app_t;

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
