
/* ---------------------------- Includes ---------------------------- */
#include "thread_network.h"

/* ---------------------------- Typedefs ---------------------------- */

/* ---------------------------- Global variables ---------------------------- */
esp_err_t err_thread_network = ESP_OK;

char buf_rx_queue_wifi[150];

uint32_t notification_network = 0u;

char buf_tx_queue_app[20];

extern QueueHandle_t queue_app_to_wifi;
extern QueueHandle_t queue_wifi_to_app;

extern TaskHandle_t handle_app;
extern TaskHandle_t handle_network;

extern bool b_wifi_connected;

/* ---------------------------- Public functions ---------------------------- */
void thread_network(void *arg)
{
    if (true != thread_network_init())
    {
        error_handle();
    }

    while (1)
    {
        if (true != thread_network_handle())
        {

        }
    }
}

bool thread_network_init(void)
{
    printf("addr err_thread_network 0x%x\n", (unsigned int)&err_thread_network);

    xTaskNotifyWait(0u, 0u, &notification_network, portMAX_DELAY);
    if ((notification_network & NOTIFICATION_TO_NETWORK_REQ_INIT) == 0u)
    {
        return false;
    }

    ulTaskNotifyValueClear(handle_network, NOTIFICATION_TO_NETWORK_REQ_INIT);

    if (true != wifi_init())
    {
        while(false == b_wifi_connected)
        {
            vTaskDelay(200);
        }
        // return false;
    }

    /* Send response to thread_app */
    if (pdPASS != xTaskNotify(handle_app, NOTIFICATION_TO_APP_RES_INIT_NETWORK, eSetBits))
    {
        return false;
    }

    printf("thread_network init ok\n");

    /* Give some time to other tasks to prevent WDT reset */
    vTaskDelay(1);

    return true;
}

bool thread_network_handle(void)
{
    xTaskNotifyWait(0u, 0u, &notification_network, 1u);
    if ((notification_network & NOTIFICATION_TO_NETWORK_REQ_SETTINGS) == 0u)
    {
        return false;
    }

    ulTaskNotifyValueClear(handle_network, NOTIFICATION_TO_NETWORK_REQ_SETTINGS);

    if (true != wifi_handle_request_settings())
    {
        return false;
    }

    char settings[20];
    uint8_t length_settings;

    wifi_get_device_settings((char *)settings, &length_settings);

    if (length_settings <= 3)
    {
        return false;
    }

    length_settings -= 3;

    memcpy(&buf_tx_queue_app, &settings[3], length_settings);

    xQueueSend(queue_wifi_to_app, (void*)buf_tx_queue_app, (TickType_t)0);

    printf("thread_network handle ok\n");

    if (xQueueReceive(queue_app_to_wifi, &(buf_rx_queue_wifi), 1u))
    {
        // printf("data to wifi: %s\n\n", buf_rx_queue_wifi);
        printf("data to wifi\n");

        if (true != wifi_handle_send_data())
        {
            return false;
        }

        printf("thread_network handle ok\n");
    }

    /* TODO: Check if there was request to change mode from webpage. */
    
    vTaskDelay(DELAY_HANDLE_THREAD_NETWORK);

    return true;
}

/* ---------------------------- Private functions ---------------------------- */


/* ---------------------------- Interrupt callbacks ---------------------------- */

