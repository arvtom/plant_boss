
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
    nvs_handle_read();

    // printf("thread_memory 111111111111init ok\n");
    printf("thread_memory init ok\n");

    /* Give some time to other tasks to prevent WDT reset */
    vTaskDelay(1);

    return true;
}

bool thread_memory_handle(void)
{
    if (xQueueReceive(queue_app_to_memory, &buf_rx_queue_app_to_memory, 1u))
    {
        printf("%x\n", buf_rx_queue_app_to_memory[0]);
        printf("%x\n", buf_rx_queue_app_to_memory[1]);
        printf("%x%x%x%x\n", 
            buf_rx_queue_app_to_memory[2], buf_rx_queue_app_to_memory[3],
            buf_rx_queue_app_to_memory[4], buf_rx_queue_app_to_memory[5]);
        printf("%x%x%x%x\n", 
            buf_rx_queue_app_to_memory[6], buf_rx_queue_app_to_memory[7],
            buf_rx_queue_app_to_memory[8], buf_rx_queue_app_to_memory[9]);
        // printf("thread_memory period 0x%x%x%x%x\n", 
        //     buf_rx_queue_app_to_memory[6], buf_rx_queue_app_to_memory[7],
        //     buf_rx_queue_app_to_memory[8], buf_rx_queue_app_to_memory[9]);
        // printf("nvs%s\n", buf_rx_queue_app_to_memory);
        nvs_handle_write();
    }
    
    vTaskDelay(DELAY_HANDLE_THREAD_MEMORY);

    return true;
}

/* ---------------------------- Private functions ---------------------------- */
bool nvs_handle_read(void)
{
    uint8_t temporary_id = 0xFF;
    uint8_t temporary_mode = 0xFF;
    uint32_t temporary_threshold = 0xFFFFFFFF;
    uint32_t temporary_period = 100u;

    if (ESP_OK != nvs_open("plant_boss", NVS_READONLY, &handle_nvs)) 
    {
        return false;
    } 

    if (ESP_OK != nvs_get_u8(handle_nvs, "0", &temporary_id))
    {
        nvs_close(handle_nvs);

        return false;
    }

    if (ESP_OK != nvs_get_u8(handle_nvs, "1", &temporary_mode))
    {
        nvs_close(handle_nvs);

        return false;
    }

    if (ESP_OK != nvs_get_u32(handle_nvs, "2", &temporary_threshold))
    {
        nvs_close(handle_nvs);

        return false;
    }

    if (ESP_OK != nvs_get_u32(handle_nvs, "3", &temporary_period))
    {
        nvs_close(handle_nvs);

        return false;
    }

    if (ESP_OK != nvs_close(handle_nvs))
    {
        return false;
    }

    printf("nvs%x,%x,%lx,%lx\n",
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

    err_nvs = nvs_set_i32(my_handle, "restart_counter", restart_counter);
    printf((err_nvs != ESP_OK) ? "Failed!\n" : "Done\n");

    //TODO: save filter structure

    // Commit written value.
    // After setting any values, nvs_commit() must be called to ensure changes are written
    // to flash storage. Implementations may write to storage at other times,
    // but this is not guaranteed.
    printf("Committing updates in NVS ... ");
    err_nvs = nvs_commit(my_handle);
    printf((err_nvs != ESP_OK) ? "Failed!\n" : "Done\n");

    // Close
    nvs_close(my_handle);
}

/* ---------------------------- Interrupt callbacks ---------------------------- */

