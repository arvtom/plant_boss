
/* ---------------------------- Includes ---------------------------- */
#include "thread_input.h"

/* ---------------------------- Typedefs ---------------------------- */

/* ---------------------------- Global variables ---------------------------- */
esp_err_t err_esp = 0;

thread_input_t s_thread_input;

/* ---------------------------- Public functions ---------------------------- */
void thread_input(void *arg)
{
    // thread_app();
    if (true != thread_input_init())
    {
        error_handle();
    }

    while (1)
    {
        if (true != thread_input_handle())
        {
            error_handle();
        }
    }
}

bool thread_input_init(void)
{
    if (true != adc_init())
    {
        printf("error\n");
        return false;
    }

    if (true != gpio_init())
    {
        printf("error\n");
        return false;
    }

    if (true != i2c_init())
    {
        printf("error\n");
        return false;
    }

    return true;
}

bool thread_input_handle(void)
{
    if (true != i2c_handle())
    {
        return false;
    }

    if (true != adc_handle())
    {
        return false;
    }

    printf("\n");
    
    vTaskDelay(100);

    return true;
}

/* ---------------------------- Private functions ---------------------------- */

/* ---------------------------- Interrupt callbacks ---------------------------- */

