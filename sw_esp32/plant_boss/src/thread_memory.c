
/* ---------------------------- Includes ---------------------------- */
#include "thread_memory.h"

/* ---------------------------- Typedefs ---------------------------- */

/* ---------------------------- Global variables ---------------------------- */
uint32_t err_thread_memory = 0u;
int err_nvs_drv = 0;

bool b_ready_thread_memory = false;

/* ---------------------------- Public functions ---------------------------- */
void thread_memory(void *arg)
{
    // thread_app();
    thread_memory_init();

    while (1)
    {
        thread_memory_handle();
    }
}

bool thread_memory_init(void)
{
    printf("addr err_thread_memory 0x%x\n", (unsigned int)&err_thread_memory);

    err_nvs_drv = nvs_flash_init();
    if (ESP_OK != err_nvs_drv)
    {
        printf("err nvs_flash_init\n");
    }

    b_ready_thread_memory = true;

    vTaskDelay(1);

    return true;
}

void thread_memory_handle(void)
{
    
    
    vTaskDelay(100);
}

/* ---------------------------- Private functions ---------------------------- */

/* ---------------------------- Interrupt callbacks ---------------------------- */

