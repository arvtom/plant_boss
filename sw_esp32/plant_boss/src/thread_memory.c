
/* ---------------------------- Includes ---------------------------- */
#include "thread_memory.h"

/* ---------------------------- Typedefs ---------------------------- */

/* ---------------------------- Global variables ---------------------------- */
uint32_t err_thread_memory = 0u;

// bool b_ready_thread_memory = false;
extern TaskHandle_t handle_network;
extern TaskHandle_t handle_app;

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

    if (true != nvm_init())
    {
        return false;
    }

    // b_ready_thread_memory = true;

    if (pdPASS != xTaskNotify(handle_network, 0, eNoAction))
    {
        return false;
    }

    if (pdPASS != xTaskNotify(handle_app, THREAD_MEMORY_TO_APP_RESULT_INIT, eSetBits))
    {
        return false;
    }

    vTaskDelay(1);

    return true;
}

void thread_memory_handle(void)
{
    
    
    vTaskDelay(100);
}

/* ---------------------------- Private functions ---------------------------- */

/* ---------------------------- Interrupt callbacks ---------------------------- */

