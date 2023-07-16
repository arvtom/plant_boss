
/* ---------------------------- Includes ---------------------------- */
#include "thread_memory.h"

/* ---------------------------- Typedefs ---------------------------- */

/* ---------------------------- Global variables ---------------------------- */

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

    return true;
}

void thread_memory_handle(void)
{
    
    
    vTaskDelay(100);
}

/* ---------------------------- Private functions ---------------------------- */

/* ---------------------------- Interrupt callbacks ---------------------------- */

