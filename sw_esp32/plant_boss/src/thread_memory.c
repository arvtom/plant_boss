
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

extern uint32_t delay_handle_thread_app;
extern uint16_t threshold_voltage_battery;
extern uint8_t device_mode;
extern uint8_t device_id;

static const char* tag_t_m = "t_m";

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
    // printf("addr err_thread_memory 0x%x\n", (unsigned int)&err_thread_memory);

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
    if (true != nvm_handle_read())
    {
        ESP_LOGI(tag_t_m, "nrf");
    }

    ESP_LOGI(tag_t_m, "i");

    /* Give some time to other tasks to prevent WDT reset */
    vTaskDelay(1);

    return true;
}

bool thread_memory_handle(void)
{
    if (xQueueReceive(queue_app_to_memory, &buf_rx_queue_app_to_memory, 1u))
    {
        if (true != nvm_handle_write())
        {
            ESP_LOGI(tag_t_m, "nwf");
        }
        else
        {
            ESP_LOGI(tag_t_m, "nwo");
        }

        ESP_LOGI(tag_t_m, "h");
    }

    // if (pdTRUE == xTaskNotifyWait(0u, 0u, &notification_memory, 1u))
    // {
    //     if (1u == notification_memory & NOTIFICATION_TO_MEMORY_REQ_DEVICE_ID)
    //     {

    //     }
    //     else
    //     {
    //         return false;
    //     }
    // }

    vTaskDelay(DELAY_HANDLE_THREAD_MEMORY);

    return true;
}

/* ---------------------------- Private functions ---------------------------- */


/* ---------------------------- Interrupt callbacks ---------------------------- */

