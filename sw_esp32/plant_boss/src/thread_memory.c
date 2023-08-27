
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
    // nvs_handle_savings();

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
        nvs_handle_savings();
    }
    
    vTaskDelay(DELAY_HANDLE_THREAD_MEMORY);

    return true;
}

/* ---------------------------- Private functions ---------------------------- */
void nvs_handle_savings(void)
{
    // Initialize NVS
    // esp_err_t err_nvs = nvs_flash_init();
    // if (err_nvs == ESP_ERR_NVS_NO_FREE_PAGES || err_nvs == ESP_ERR_NVS_NEW_VERSION_FOUND) {
    //     // NVS partition was truncated and needs to be erased
    //     // Retry nvs_flash_init
    //     ESP_ERROR_CHECK(nvs_flash_erase());
    //     err_nvs = nvs_flash_init();
    // }
    // ESP_ERROR_CHECK( err_nvs );

    // Open
    printf("1");
    // printf("Opening Non-Volatile Storage (NVS) handle... ");
    // nvs_handle_t my_handle;
    // err_nvs = nvs_open("storage", NVS_READWRITE, &my_handle);
    // if (err_nvs != ESP_OK) {
    //     printf("Error (%s) opening NVS handle!\n", esp_err_to_name(err_nvs));
    // } 
    // else 
    // {
    //     printf("Done\n");

    //     // Read
    //     printf("Reading restart counter from NVS ... ");
    //     int32_t restart_counter = 0; // value will default to 0, if not set yet in NVS
    //     err_nvs = nvs_get_i32(my_handle, "restart_counter", &restart_counter);
    //     switch (err_nvs) 
    //     {
    //         case ESP_OK:
    //             printf("Done\n");
    //             printf("Restart counter = %ld\n", restart_counter);
    //             break;
    //         case ESP_ERR_NVS_NOT_FOUND:
    //             printf("The value is not initialized yet!\n");
    //             break;
    //         default :
    //             printf("Error (%s) reading!\n", esp_err_to_name(err_nvs));
    //     }

    //     //TODO: read filter structure

    //     // Write
    //     printf("Updating restart counter in NVS ... ");
    //     restart_counter++;
    //     err_nvs = nvs_set_i32(my_handle, "restart_counter", restart_counter);
    //     printf((err_nvs != ESP_OK) ? "Failed!\n" : "Done\n");

    //     //TODO: save filter structure

    //     // Commit written value.
    //     // After setting any values, nvs_commit() must be called to ensure changes are written
    //     // to flash storage. Implementations may write to storage at other times,
    //     // but this is not guaranteed.
    //     printf("Committing updates in NVS ... ");
    //     err_nvs = nvs_commit(my_handle);
    //     printf((err_nvs != ESP_OK) ? "Failed!\n" : "Done\n");

    //     // Close
    //     nvs_close(my_handle);
    // }
}

/* ---------------------------- Interrupt callbacks ---------------------------- */

