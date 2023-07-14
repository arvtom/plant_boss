
/* ---------------------------- Includes ---------------------------- */
#include "thread_network.h"

/* ---------------------------- Typedefs ---------------------------- */

/* ---------------------------- Global variables ---------------------------- */
char buffer_rx_queue_message_wifi[50];
QueueHandle_t queue_message_wifi;
esp_err_t err_thread_network = ESP_OK;
bool b_err_thread_network = false;
bool b_ready_wifi = false;

/* temporary global variables for testing */
extern float light;
extern float temperature;
extern int adc_raw_humidity;
extern int adc_raw_battery;

/* ---------------------------- Public functions ---------------------------- */
void thread_network(void *arg)
{
    b_err_thread_network = thread_network_init();
    if (true != b_err_thread_network)
    {
        return;
    }

    while (1)
    {
        thread_network_handle();
    }
}

bool thread_network_init(void)
{
    queue_message_wifi = xQueueCreate(5, sizeof(buffer_rx_queue_message_wifi)); 
    if (queue_message_wifi == 0)
    {
     printf("Failed to create queue= %p\n", queue_message_wifi);
    }

    /* Enable nvs, which is also used for wifi*/
    err_thread_network = nvs_flash_init();
    if (ESP_OK != err_thread_network)
    {
        printf("err nvs_flash_init\n");
    }

    err_thread_network = wifi_connection();
    if (ESP_OK != err_thread_network)
    {
        printf("err wifi_connection\n");
    }

    return true;
}

void thread_network_handle(void)
{
    if (xQueueReceive(queue_message_wifi, &(buffer_rx_queue_message_wifi), (TickType_t)5))
    {
        printf("thread_network sending data to wifi: %s\n", buffer_rx_queue_message_wifi);
        vTaskDelay(10);
    }


    if (true == b_ready_wifi)
    {
        post_rest_function();
    }
    
    vTaskDelay(100);
}

/* ---------------------------- Private functions ---------------------------- */
static void wifi_event_handler(void *event_handler_arg, esp_event_base_t event_base, int32_t event_id, void *event_data)
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
    err_thread_network = esp_netif_init();                    // TCP/IP initiation 					s1.1
    if (ESP_OK != err_thread_network)
    {
        printf("err erresp_netif_init\n");

        return false;
    }

    err_thread_network = esp_event_loop_create_default();     // event loop 			                s1.2
    if (ESP_OK != err_thread_network)
    {
        printf("err esp_event_loop_create_default\n");

        return false;
    }

    esp_netif_create_default_wifi_sta(); // WiFi station 	                    s1.3
    wifi_init_config_t wifi_initiation = WIFI_INIT_CONFIG_DEFAULT();

    err_thread_network = esp_wifi_init(&wifi_initiation); // 					                    s1.4
    if (ESP_OK != err_thread_network)
    {
        printf("err esp_wifi_init\n");

        return false;
    }

    // 2 - Wi-Fi Configuration Phase
    err_thread_network = esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, wifi_event_handler, NULL);
    if (ESP_OK != err_thread_network)
    {
        printf("err esp_event_handler_register\n");

        return false;
    }

    err_thread_network = esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, wifi_event_handler, NULL);
    if (ESP_OK != err_thread_network)
    {
        printf("err esp_event_handler_register\n");

        return false;
    }

    err_thread_network = esp_wifi_set_mode(WIFI_MODE_STA);
    if (ESP_OK != err_thread_network)
    {
        printf("err esp_wifi_set_mode\n");

        return false;
    }

    wifi_config_t wifi_configuration = {
        .sta = {
            .ssid = SSID,
            .password = PASS}};

    err_thread_network = esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_configuration);
    if (ESP_OK != err_thread_network)
    {
        printf("err esp_wifi_set_config %d\n", err_thread_network);

        return false;
    }

    // 3 - Wi-Fi Start Phase
    err_thread_network = esp_wifi_start();
    if (ESP_OK != err_thread_network)
    {
        printf("err esp_wifi_start\n");

        return false;
    }

    // 4- Wi-Fi Connect Phase
    err_thread_network = esp_wifi_connect();
    if (ESP_OK != err_thread_network)
    {
        printf("err esp_wifi_connect\n");

        return false;
    }

    b_ready_wifi = true;

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

static void post_rest_function()
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

    char buffer [100];
    int ret = snprintf(buffer, 100, "a1=%2.2f&a2=%d&a3=%d&a4=%5.1f&a5=%2.1f&a6=%d&a7=%d", 
        1.0,
        1,
        adc_raw_humidity,
        light,
        temperature,
        adc_raw_battery,
        120);

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

/* ---------------------------- Interrupt callbacks ---------------------------- */

