
#ifndef THREAD_NETWORK_H
#define THREAD_NETWORK_H

/* ---------------------------- Includes ---------------------------- */
#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>
// #include <freertos/semphr.h>
#include "settings_wifi.h"
#include <esp_wifi.h>
#include <esp_netif.h>
#include <esp_http_client.h>

/* ---------------------------- Typedefs ---------------------------- */

/* ---------------------------- Public functions ---------------------------- */
void thread_network(void *arg);
bool thread_network_init(void);
void thread_network_handle(void);

/* ---------------------------- Private functions ---------------------------- */
static void wifi_event_handler(void *event_handler_arg, esp_event_base_t event_base, int32_t event_id, void *event_data);
bool wifi_connection();
static void post_rest_function();

/* ---------------------------- Interrupt callbacks ---------------------------- */

#endif
