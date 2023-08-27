
/* ---------------------------- Includes ---------------------------- */
#include "thread_memory.h"

/* ---------------------------- Typedefs ---------------------------- */

/* ---------------------------- Global variables ---------------------------- */
uint32_t err_thread_memory = 0u;

uint32_t notification_memory = 0u;

extern QueueHandle_t queue_app_to_memory;
extern QueueHandle_t queue_memory_to_app;

extern TaskHandle_t handle_app;
extern TaskHandle_t handle_memory;

uint8_t buf_rx_queue_app_to_memory[10];

/* ---------------------------- Public functions ---------------------------- */
void thread_memory(void *arg)
{
    if (true != thread_memory_init())
    {
        error_handle();
    }

    while (1)
    {
        if (true != thread_memory_handle())
        {
            error_handle();
        }
    }
}

bool thread_memory_init(void)
{
    printf("addr err_thread_memory 0x%x\n", (unsigned int)&err_thread_memory);

    xTaskNotifyWait(0u, 0u, &notification_memory, portMAX_DELAY);
    if ((notification_memory & NOTIFICATION_TO_MEMORY_REQ_INIT) == 0u)
    {
        return false;
    }

    ulTaskNotifyValueClear(handle_memory, NOTIFICATION_TO_MEMORY_REQ_INIT);

    if (true != nvm_init())
    {
        return false;
    }

    if (pdPASS != xTaskNotify(handle_app, NOTIFICATION_TO_APP_RES_INIT_MEMORY, eSetBits))
    {
        return false;
    }

    /* TODO: read mode from nvm */

    printf("thread_memory init ok\n");

    /* Give some time to other tasks to prevent WDT reset */
    vTaskDelay(1);

    return true;
}

bool thread_memory_handle(void)
{
    if (xQueueReceive(queue_app_to_memory, &buf_rx_queue_app_to_memory, 1u))
    {
        // printf("thread_memory: %x,%x,%x%x%x%x,%x%x%x%x\n",
        //     buf_rx_queue_app_to_memory[0], buf_rx_queue_app_to_memory[1],
        //     buf_rx_queue_app_to_memory[2], buf_rx_queue_app_to_memory[3],
        //     buf_rx_queue_app_to_memory[4], buf_rx_queue_app_to_memory[5],
        //     buf_rx_queue_app_to_memory[6], buf_rx_queue_app_to_memory[7],
        //     buf_rx_queue_app_to_memory[8], buf_rx_queue_app_to_memory[9]);
        printf("thread_memory id %x\n", buf_rx_queue_app_to_memory[0]);
        printf("thread_memory mode %x\n", buf_rx_queue_app_to_memory[1]);
        // printf("thread_memory threshold %x %x %x %x\n", 
        //     buf_rx_queue_app_to_memory[2], buf_rx_queue_app_to_memory[3],
        //     buf_rx_queue_app_to_memory[4], buf_rx_queue_app_to_memory[5]);
        // printf("thread_memory period %x\n", buf_rx_queue_app_to_memory[1]);
    }
    
    vTaskDelay(DELAY_HANDLE_THREAD_MEMORY);

    return true;
}

/* ---------------------------- Private functions ---------------------------- */

/* ---------------------------- Interrupt callbacks ---------------------------- */

