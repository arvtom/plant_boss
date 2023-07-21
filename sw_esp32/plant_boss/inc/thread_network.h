
#ifndef THREAD_NETWORK_H
#define THREAD_NETWORK_H

/* ---------------------------- Includes ---------------------------- */
#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>
// #include <freertos/semphr.h>
// #include "settings_wifi.h"
// #include <esp_wifi.h>
// #include <esp_netif.h>
// #include <esp_http_client.h>

#include "wifi_wrapper.h"
#include "uart_wrapper.h"
#include "common_thread_objects.h"

/* ---------------------------- Typedefs ---------------------------- */

/* ---------------------------- Public functions ---------------------------- */
void thread_network(void *arg);
bool thread_network_init(void);
bool thread_network_handle(void);

/* ---------------------------- Private functions ---------------------------- */


/* ---------------------------- Interrupt callbacks ---------------------------- */

#endif
