
/* ---------------------------- Includes ---------------------------- */
#include "thread_network.h"

/* ---------------------------- Typedefs ---------------------------- */

/* ---------------------------- Global variables ---------------------------- */
extern QueueHandle_t queue_wifi;
char buf_rx_queue_wifi[150];

esp_err_t err_thread_network = ESP_OK;
bool b_err_thread_network = false;
bool b_ready_network = false;

// extern bool b_ready_thread_memory;

/* temporary global variables for testing */

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
    printf("addr err_thread_network 0x%x\n", (unsigned int)&err_thread_network);
    
    queue_wifi = xQueueCreate(5, sizeof(buf_rx_queue_wifi)); 
    if (queue_wifi == 0)
    {
        printf("Failed to create queue= %p\n", queue_wifi);
    }

    // while (false == b_ready_thread_memory)
    // {
    //     vTaskDelay(1);
    // }

    uint32_t value_notification = 0;

    xTaskNotifyWait(0x00, 0x00, &value_notification, portMAX_DELAY);

    if (true != wifi_init())
    {
        return false;
    }

    b_ready_network = true;

    vTaskDelay(1);

    return true;
}

bool thread_network_handle(void)
{
    if (xQueueReceive(queue_wifi, &(buf_rx_queue_wifi), (TickType_t)5))
    {
        printf("data to wifi: %s\n\n", buf_rx_queue_wifi);
        vTaskDelay(10);
    }

    if (true == b_ready_network)
    {
        if (true != wifi_handle())
        {
            return false;
        }
        // uart_handle();
    }
    
    vTaskDelay(100);

    return true;
}

/* ---------------------------- Private functions ---------------------------- */


/* ---------------------------- Interrupt callbacks ---------------------------- */

