/**
*  \file    wifi_wrapper.c
*  \brief   This file wraps around esp32 wifi driver.
*  \author  arvtom
*/

/*------------------------------Includes------------------------------*/
#include "wifi_wrapper.h"

/*------------------------------Defines------------------------------*/

/*------------------------------Variables / Macro calls------------------------------*/
int err_wifi_drv = 0;
int err_tcp_drv = 0;
int err_http_drv = 0;

extern char buf_rx_queue_wifi[150];
extern uint16_t length_buf_tx_queue_wifi;

int8_t rssi_wifi = 0;

bool b_ready_wifi = false;

esp_http_client_config_t config_post;

/*------------------------------Public functions------------------------------*/
bool wifi_init(void)
{
    err_wifi_drv = wifi_connection();
    if (ESP_OK != err_wifi_drv)
    {
        printf("err wifi_connection\n");
    }

    config_post.url = "http://192.168.8.139:9999";
    config_post.method = HTTP_METHOD_POST;
    config_post.cert_pem = NULL;
    config_post.event_handler = client_event_post_handler;
    
    return true;
}

bool wifi_handle(void)
{
    if (true == b_ready_wifi)
    {
        if (true != wifi_handle_http_post())
        {
            return false;
        }

        wifi_ap_record_t ap_info;
        if (ESP_OK != esp_wifi_sta_get_ap_info(&ap_info))
        {
            printf("error checking wifi info\n");
            return false;
        }

        rssi_wifi = ap_info.rssi;
    }


    return true;
}

int8_t wifi_get_rssi_value(void)
{
    return rssi_wifi;
}

/*------------------------------Private functions------------------------------*/
bool wifi_handle_http_post(void)
{
    esp_http_client_handle_t client = esp_http_client_init(&config_post);

    err_http_drv = esp_http_client_set_post_field(client, (char *)buf_rx_queue_wifi, length_buf_tx_queue_wifi);
    if (ESP_OK != err_http_drv)
    {
        return false;
    }

    err_http_drv = esp_http_client_perform(client);
    if (ESP_OK != err_http_drv)
    {
        // return false;
    }

    err_http_drv = esp_http_client_cleanup(client);
    if (ESP_OK != err_http_drv)
    {
        return false;
    }

    return true;
}

void wifi_event_handler(void *event_handler_arg, esp_event_base_t event_base, int32_t event_id, void *event_data)
{
    switch (event_id)
    {
    case WIFI_EVENT_STA_START:
        printf("WiFi connecting ... \n");
        break;
    case WIFI_EVENT_STA_CONNECTED:
        printf("WiFi connected ... \n");
        break;
    case WIFI_EVENT_STA_DISCONNECTED:
        printf("WiFi lost connection ... \n");
        b_ready_wifi = false;
        break;
    case IP_EVENT_STA_GOT_IP:
        printf("WiFi got IP ... \n\n");
        b_ready_wifi = true;
        break;
    default:
        break;
    }
}

bool wifi_connection()
{
    // 1 - Wi-Fi/LwIP Init Phase
    err_tcp_drv = esp_netif_init();                    // TCP/IP initiation 					s1.1
    if (ESP_OK != err_tcp_drv)
    {
        printf("err erresp_netif_init\n");

        return false;
    }

    err_tcp_drv = esp_event_loop_create_default();     // event loop 			                s1.2
    if (ESP_OK != err_tcp_drv)
    {
        printf("err esp_event_loop_create_default\n");

        return false;
    }

    esp_netif_create_default_wifi_sta(); // WiFi station 	                    s1.3
    wifi_init_config_t wifi_initiation = WIFI_INIT_CONFIG_DEFAULT();

    err_wifi_drv = esp_wifi_init(&wifi_initiation); // 					                    s1.4
    if (ESP_OK != err_wifi_drv)
    {
        printf("err esp_wifi_init\n");

        return false;
    }

    // 2 - Wi-Fi Configuration Phase
    err_wifi_drv = esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, wifi_event_handler, NULL);
    if (ESP_OK != err_wifi_drv)
    {
        printf("err esp_event_handler_register\n");

        return false;
    }

    err_wifi_drv = esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, wifi_event_handler, NULL);
    if (ESP_OK != err_wifi_drv)
    {
        printf("err esp_event_handler_register\n");

        return false;
    }

    err_wifi_drv = esp_wifi_set_mode(WIFI_MODE_STA);
    if (ESP_OK != err_wifi_drv)
    {
        printf("err esp_wifi_set_mode\n");

        return false;
    }

    wifi_config_t wifi_configuration = {
        .sta = {
            .ssid = SSID,
            .password = PASS}};

    err_wifi_drv = esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_configuration);
    if (ESP_OK != err_wifi_drv)
    {
        printf("err esp_wifi_set_config %d\n", err_wifi_drv);

        return false;
    }

    // 3 - Wi-Fi Start Phase
    err_wifi_drv = esp_wifi_start();
    if (ESP_OK != err_wifi_drv)
    {
        printf("err esp_wifi_start\n");

        return false;
    }

    // 4- Wi-Fi Connect Phase
    err_wifi_drv = esp_wifi_connect();
    if (ESP_OK != err_wifi_drv)
    {
        printf("err esp_wifi_connect\n");

        return false;
    }

    return true;
}

esp_err_t client_event_post_handler(esp_http_client_event_handle_t evt)
{
    switch (evt->event_id)
    {
    case HTTP_EVENT_ON_DATA:
        printf("HTTP_EVENT_ON_DATA: %.*s\n", evt->data_len, (char *)evt->data);
        break;

    default:
        break;
    }
    return ESP_OK;
}