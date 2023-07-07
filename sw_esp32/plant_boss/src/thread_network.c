
/* ---------------------------- Includes ---------------------------- */
#include "thread_network.h"

/* ---------------------------- Typedefs ---------------------------- */

/* ---------------------------- Global variables ---------------------------- */
char buffer_rx_queue_message_wifi[50];
QueueHandle_t queue_message_wifi;

/* ---------------------------- Public functions ---------------------------- */
void thread_network(void *arg)
{
    thread_network_init();

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

    return true;
}

void thread_network_handle(void)
{
    if (xQueueReceive(queue_message_wifi, &(buffer_rx_queue_message_wifi), (TickType_t)5))
    {
        printf("thread_network sending data to wifi: %s\n", buffer_rx_queue_message_wifi);
        vTaskDelay(10);
    }
    
    vTaskDelay(100);
}

/* ---------------------------- Private functions ---------------------------- */

/* ---------------------------- Interrupt callbacks ---------------------------- */

