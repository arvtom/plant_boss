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

#include "error.h"

/* Get wifi SSID and PASS */
#include "settings_wifi.h"

/*------------------------------Defines------------------------------*/

/*------------------------------Structures / enumerators------------------------------*/
typedef enum
{
    WIFI_ERROR_CONNECTION                   = 0x00000001U,
    WIFI_ERROR_HTTP_POST_DATA               = 0x00000002U,
    WIFI_ERROR_HTTP_RESPONSE_DATA           = 0x00000004U,
    WIFI_ERROR_SNPRINTF                     = 0x00000008U,
    WIFI_ERROR_HTTP_POST_SETTINGS_REQUEST   = 0x00000010U,
    WIFI_ERROR_HTTP_RESPONSE_SETTINGS       = 0x00000020U,
    WIFI_ERROR_GET_AP_INFO                  = 0x00000040U,
    WIFI_ERROR_SET_POST_FIELD               = 0x00000080U,
    WIFI_ERROR_CLIENT_PERFORM               = 0x00000100U,
    WIFI_ERROR_CLIENT_CLEANUP               = 0x00000200U,
    WIFI_ERROR_DISCONNECTED                 = 0x00000400U,
    WIFI_ERROR_UNKNOWN_EVENT_WIFI           = 0x00000800U,
    WIFI_ERROR_NETIF_INIT                   = 0x00001000U,
    WIFI_ERROR_LOOP_CREATE                  = 0x00002000U,
    WIFI_ERROR_INIT_DRV                     = 0x00004000U,
    WIFI_ERROR_REGISTER_EVENT_HANDLER_1     = 0x00008000U,
    WIFI_ERROR_REGISTER_EVENT_HANDLER_2     = 0x00010000U,
    WIFI_ERROR_SET_CONFIG                   = 0x00020000U,
    WIFI_ERROR_START                        = 0x00040000U,
    WIFI_ERROR_CONNECT                      = 0x00080000U,
    WIFI_ERROR_UNKNOWN_EVENT_POST           = 0x00100000U,
    WIFI_ERROR_SET_MODE                     = 0x00200000U,
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
} wifi_error_t;

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
