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

/*------------------------------Public functions------------------------------*/
bool wifi_init(void)
{
    err_wifi_drv = wifi_connection();
    if (ESP_OK != err_wifi_drv)
    {
        printf("err wifi_connection\n");
    }
    
    return true;
}

bool wifi_handle(void)
{
    post_rest_function();
    wifi_ap_record_t ap_info;
    if (ESP_OK != esp_wifi_sta_get_ap_info(&ap_info))
    {
        printf("error checking wifi info\n");
    }
    else
    {
        printf("rssi=%d\n", ap_info.rssi);
    }

    return true;
}

/*------------------------------Private functions------------------------------*/
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
        break;
    case IP_EVENT_STA_GOT_IP:
        printf("WiFi got IP ... \n\n");
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

void post_rest_function(void)
{
    esp_http_client_config_t config_post = {
        .url = "http://192.168.8.139:9999",
        .method = HTTP_METHOD_POST,
        .cert_pem = NULL,
        .event_handler = client_event_post_handler};
        
    esp_http_client_handle_t client = esp_http_client_init(&config_post);

    /* a1 timestamp */
    /* a2 device */
    /* a3 humidity */
    /* a4 light */
    /* a5 temperature */
    /* a6 bat_voltage */
    /* a7 rssi_wifi */

    // extern float light;
    // extern float temperature;
    // extern int adc_raw_humidity;
    // extern int adc_raw_battery;

    esp_err_t err_wifi[3];

    // char  *post_data = "a1=1.39&a2=1&a3=1.49&a4=1.59&a5=1.69&a6=1.79&a7=1.89";
    // err_wifi[0] = esp_http_client_set_post_field(client, post_data, strlen(post_data));

    // device = form.getvalue('a1')
    // humidity = form.getvalue('a2')
    // light = form.getvalue('a3')
    // temperature = form.getvalue('a4')
    // bat_voltage = form.getvalue('a5')
    // rssi_wifi = form.getvalue('a6')
    // mode = form.getvalue('a7')
    // bat_low_flag = form.getvalue('a8')
    // error_app = form.getvalue('a9')
    // error_input = form.getvalue('a10')
    // error_output = form.getvalue('a11')
    // error_network = form.getvalue('a12')
    // error_memory = form.getvalue('a13')
    // sw_version = form.getvalue('a14')
    // timer_or_period = form.getvalue('a15')


    char buffer [100];
    int ret = snprintf(buffer, 100, 
        "a1=%d&a2=%1.1f&a3=%1.1f&a4=%1.1f&a5=%1.1f&a6=%d&a7=%d&a8=%d&a9=%d&a10=%d&a11=%d&a12=%d&a13=%d&a14=%d&a15=%d",
        1u, 9.1, 8.1, 7.1, 6.1,
        2u, 3u, 4u, 5u, 6u,
        7u, 8u, 9u, 10u, 11u);

    if (ret <= 0)
    {
        printf("snprintf_error");
    }
    else
    {
        err_wifi[0] = esp_http_client_set_post_field(client, (char *)buffer, ret);
        err_wifi[1] = esp_http_client_perform(client);
        err_wifi[2] = esp_http_client_cleanup(client);
    }

    printf("err_wifi=%d,%d,%d\n", err_wifi[0], err_wifi[1], err_wifi[2]);
}