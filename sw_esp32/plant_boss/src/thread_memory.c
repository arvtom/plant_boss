
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

nvs_handle_t handle_nvs;

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
    if (true != nvs_handle_read())
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
        if (true != nvs_handle_write())
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
bool nvs_handle_read(void)
{
    uint8_t temporary_id = 0xFF;
    uint8_t temporary_mode = 0xFF;
    uint16_t temporary_threshold = 0xFFFF;
    uint32_t temporary_period = 100u;

    if (ESP_OK != nvs_open("plant_boss", NVS_READONLY, &handle_nvs)) 
    {
        ESP_LOGI(tag_t_m, "of");

        return false;
    }

    if (ESP_OK != nvs_get_u8(handle_nvs, "0", &temporary_id))
    {
        ESP_LOGI(tag_t_m, "0f");

        nvs_close(handle_nvs);

        return false;
    }

    if (ESP_OK != nvs_get_u8(handle_nvs, "1", &temporary_mode))
    {
        ESP_LOGI(tag_t_m, "1f");

        nvs_close(handle_nvs);

        return false;
    }

    if (ESP_OK != nvs_get_u16(handle_nvs, "2", &temporary_threshold))
    {
        ESP_LOGI(tag_t_m, "2f");

        nvs_close(handle_nvs);

        return false;
    }

    if (ESP_OK != nvs_get_u32(handle_nvs, "3", &temporary_period))
    {
        ESP_LOGI(tag_t_m, "3f");

        nvs_close(handle_nvs);

        return false;
    }

    nvs_close(handle_nvs);

    ESP_LOGI(tag_t_m, "nvs%x,%x,%x,%lx",
        temporary_id, temporary_mode,
        temporary_threshold, temporary_period);

    return true;
}

bool nvs_handle_write(void)
{
    if (ESP_OK != nvs_open("plant_boss", NVS_READWRITE, &handle_nvs)) 
    {
        return false;
    } 

    if (ESP_OK != nvs_set_u8(handle_nvs, "0", device_id))
    {
        nvs_close(handle_nvs);

        return false;
    }

    if (ESP_OK != nvs_set_u8(handle_nvs, "1", device_mode))
    {
        nvs_close(handle_nvs);

        return false;
    }

    if (ESP_OK != nvs_set_u16(handle_nvs, "2", threshold_voltage_battery))
    {
        nvs_close(handle_nvs);

        return false;
    }

    if (ESP_OK != nvs_set_u32(handle_nvs, "3", delay_handle_thread_app))
    {
        nvs_close(handle_nvs);

        return false;
    }

    if (ESP_OK != nvs_commit(handle_nvs))
    {
        nvs_close(handle_nvs);

        return false;
    }

    nvs_close(handle_nvs);

    return true;
}

/* ---------------------------- Interrupt callbacks ---------------------------- */

