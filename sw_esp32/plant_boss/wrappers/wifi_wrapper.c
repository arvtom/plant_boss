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

bool b_wifi_connected = false;

extern char buf_rx_queue_wifi[150];
extern uint16_t length_buf_tx_queue_wifi;

int8_t rssi_wifi = 0;

bool b_ready_wifi = false;
bool b_err_database = false;

char response[30];
bool b_http_response = false;
int length_response = 0u;

esp_http_client_config_t config_post;

static const char* tag_wifi = "wifi";

/*------------------------------Public functions------------------------------*/
bool wifi_init(void)
{
    err_wifi_drv = wifi_connection();
    if (ESP_OK != err_wifi_drv)
    {
        ESP_LOGI(tag_wifi, "con");
    }

    config_post.cert_pem = NULL;
    config_post.event_handler = client_event_post_handler;
    config_post.method = HTTP_METHOD_POST;
    
    return true;
}

bool wifi_handle_send_data(void)
{
    if (true == b_ready_wifi && false == b_err_database)
    {
        config_post.url = "http://192.168.8.139/plant_boss/data";

        if (true != wifi_handle_http_post((char *)buf_rx_queue_wifi, length_buf_tx_queue_wifi))
        {
            return false;
        }

        /* Wait until webpage responds */
        while(false == b_http_response)
        {

        }

        b_http_response = false;

        /* Check if reponse is string OK */
        if (0x4F != response[0] && 0x4B != response[1])
        {
            b_err_database = true;

            ESP_LOGI(tag_wifi, "r%.*s", length_response, (char *)response);
        }
    }


    return true;
}

bool wifi_handle_request_settings(void)
{
    if (true == b_ready_wifi && false == b_err_database)
    {
        char temporary_buffer[6];

        /* post data packet to request device 0 settings */
        int ret = snprintf(temporary_buffer, 6, "a1=%d", 0u);

        if (ret < 0 || ret > 6)
        {
            return false;
        }

        config_post.url = "http://192.168.8.139/plant_boss/settings_request";

        if (true != wifi_handle_http_post((char *)temporary_buffer, ret))
        {
            return false;
        }

        /* Wait until webpage responds */
        while(false == b_http_response)
        {

        }

        b_http_response = false;

        /* Check if reponse is string OK */
        if (0x4F != response[0] && 0x4B != response[1])
        {
            b_err_database = true;

            ESP_LOGI(tag_wifi, "r%.*s", length_response, (char *)response);
        }

        wifi_ap_record_t ap_info;
        if (ESP_OK != esp_wifi_sta_get_ap_info(&ap_info))
        {
            ESP_LOGI(tag_wifi, "ch");

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

void wifi_get_device_settings(char *settings, uint8_t *length_settings)
{
    if (length_response > 0)
    {
        memcpy(settings, response, length_response);
        *length_settings = (uint8_t)length_response;
    }
}

/*------------------------------Private functions------------------------------*/
bool wifi_handle_http_post(char *buffer, uint16_t length)
{
    esp_http_client_handle_t client = esp_http_client_init(&config_post);

    err_http_drv = esp_http_client_set_post_field(client, buffer, length);
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
        ESP_LOGI(tag_wifi, "wing");

        break;
    case WIFI_EVENT_STA_CONNECTED:
        ESP_LOGI(tag_wifi, "wed");

        b_wifi_connected = true;
        break;
    case WIFI_EVENT_STA_DISCONNECTED:
        ESP_LOGI(tag_wifi, "wost");

        b_ready_wifi = false;
        break;
    case IP_EVENT_STA_GOT_IP:
        ESP_LOGI(tag_wifi, "wot");

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
        ESP_LOGI(tag_wifi, "n");

        return false;
    }

    err_tcp_drv = esp_event_loop_create_default();     // event loop 			                s1.2
    if (ESP_OK != err_tcp_drv)
    {
        ESP_LOGI(tag_wifi, "l");

        return false;
    }

    esp_netif_create_default_wifi_sta(); // WiFi station 	                    s1.3
    wifi_init_config_t wifi_initiation = WIFI_INIT_CONFIG_DEFAULT();

    err_wifi_drv = esp_wifi_init(&wifi_initiation); // 					                    s1.4
    if (ESP_OK != err_wifi_drv)
    {
        ESP_LOGI(tag_wifi, "d i");

        return false;
    }

    // 2 - Wi-Fi Configuration Phase
    err_wifi_drv = esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, wifi_event_handler, NULL);
    if (ESP_OK != err_wifi_drv)
    {
        ESP_LOGI(tag_wifi, "er");

        return false;
    }

    err_wifi_drv = esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, wifi_event_handler, NULL);
    if (ESP_OK != err_wifi_drv)
    {
        ESP_LOGI(tag_wifi, "hr");

        return false;
    }

    err_wifi_drv = esp_wifi_set_mode(WIFI_MODE_STA);
    if (ESP_OK != err_wifi_drv)
    {
        ESP_LOGI(tag_wifi, "ms");

        return false;
    }

    wifi_config_t wifi_configuration = {
        .sta = {
            .ssid = SSID,
            .password = PASS}};

    err_wifi_drv = esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_configuration);
    if (ESP_OK != err_wifi_drv)
    {
        ESP_LOGI(tag_wifi, "cs");

        return false;
    }

    // 3 - Wi-Fi Start Phase
    err_wifi_drv = esp_wifi_start();
    if (ESP_OK != err_wifi_drv)
    {
        ESP_LOGI(tag_wifi, "ds");

        return false;
    }

    // 4- Wi-Fi Connect Phase
    err_wifi_drv = esp_wifi_connect();
    if (ESP_OK != err_wifi_drv)
    {
        ESP_LOGI(tag_wifi, "dc");

        return false;
    }

    return true;
}

esp_err_t client_event_post_handler(esp_http_client_event_handle_t evt)
{
    switch (evt->event_id)
    {
    case HTTP_EVENT_ON_DATA:
        memcpy(&response, evt->data, evt->data_len);
        length_response = evt->data_len;

        b_http_response = true;

        break;

    default:
        break;
    }
    return ESP_OK;
}