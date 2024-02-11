
/* ---------------------------- Includes ---------------------------- */
#include "thread_memory.h"

/* ---------------------------- Typedefs ---------------------------- */

/* ---------------------------- Global variables ---------------------------- */
uint32_t err_thread_memory = 0u;

uint32_t notification_memory = 0u;

// extern QueueHandle_t queue_app_to_memory;
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
    uint32_t out_size = 0u;
    uint32_t flash_size = 0u;
    
    if (ESP_OK != esp_flash_get_size(esp_flash_default_chip, &out_size))
    {
        printf("err out_size r\n");
    }

    printf("out_size=0x%lX\n", out_size);

    if (ESP_OK != esp_flash_get_physical_size(esp_flash_default_chip, &flash_size))
    {
        printf("err flash_size r\n");
    }

    printf("flash_size=0x%lX\n", flash_size);

    uint32_t buf_flash = 0u;

    printf("flash content: addr;value\n");

    for (uint32_t i = 0u; i < out_size; i++)
    {
        if (ESP_OK != esp_flash_read(esp_flash_default_chip , &buf_flash, i, 1))
        {
            printf("err flash r\n");
        }

        printf("%lx;%lX\n", i, buf_flash);
    }


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
    if (pdTRUE == xTaskNotifyWait(0u, 0u, &notification_memory, 1u))
    {
        if (0u != (notification_memory & NOTIFICATION_TO_MEMORY_REQ_WRITE_ERROR) ||
                0u != (notification_memory & NOTIFICATION_TO_MEMORY_REQ_WRITE_PARAMETERS))
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
    }

    vTaskDelay(DELAY_HANDLE_THREAD_MEMORY);

    return true;
}

/* ---------------------------- Private functions ---------------------------- */


/* ---------------------------- Interrupt callbacks ---------------------------- */

