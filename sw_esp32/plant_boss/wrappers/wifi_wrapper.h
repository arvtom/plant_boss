/**
*  \file    wifi_wrapper.h
*  \brief   This file wraps around esp32 wifi driver.
*  \author  arvtom
*/

#ifndef WIFI_WRAPPER_H
#define WIFI_WRAPPER_H

/*------------------------------Includes------------------------------*/
#include <stdbool.h>

#include <esp_wifi.h>
#include <esp_netif.h>
#include <esp_http_client.h>
#include <esp_log.h>

#include "settings_wifi.h"

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
// }wifi_error_t;

/*------------------------------Public function prototypes------------------------------*/
bool wifi_init(void);
bool wifi_handle_send_data(void);
bool wifi_handle_request_settings(void);

int8_t wifi_get_rssi_value(void);
void wifi_get_device_settings(char *settings, uint8_t *length_settings);
/*------------------------------Private function prototypes------------------------------*/
bool wifi_handle_http_post(char *buffer, uint16_t length);
void wifi_event_handler(void *event_handler_arg, esp_event_base_t event_base, int32_t event_id, void *event_data);
bool wifi_connection();
esp_err_t client_event_post_handler(esp_http_client_event_handle_t evt);

#endif /* WIFI_WRAPPER_H */