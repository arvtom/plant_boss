
/* ---------------------------- Includes ---------------------------- */
#include "thread_network.h"

/* ---------------------------- Typedefs ---------------------------- */

/* ---------------------------- Global variables ---------------------------- */
esp_err_t err_thread_network = ESP_OK;

char buf_rx_queue_wifi[150];

uint32_t notification_network = 0u;

extern QueueHandle_t queue_app_to_wifi;
extern QueueHandle_t queue_wifi_to_app;

extern TaskHandle_t handle_app;

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

    xTaskNotifyWait(NOTIFICATION_TO_NETWORK_REQ_INIT, 0u, &notification_network, portMAX_DELAY);
    if ((notification_network & NOTIFICATION_TO_NETWORK_REQ_INIT) == 0u)
    {
        return false;
    }

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
    if (xQueueReceive(queue_app_to_wifi, &(buf_rx_queue_wifi), 0u))
    {
        printf("data to wifi: %s\n\n", buf_rx_queue_wifi);
    }

    if (true != wifi_handle())
    {
        return false;
    }

    /* TODO: Check if there was request to change mode from webpage. */

    printf("thread_network handle ok\n");
    
    vTaskDelay(100);

    return true;
}

/* ---------------------------- Private functions ---------------------------- */


/* ---------------------------- Interrupt callbacks ---------------------------- */

