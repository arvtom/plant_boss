
/* ---------------------------- Includes ---------------------------- */
#include "thread_input.h"

/* ---------------------------- Typedefs ---------------------------- */

/* ---------------------------- Global variables ---------------------------- */
esp_err_t err_esp = 0;

thread_input_t s_thread_input;

uint32_t err_thread_input = 0u;

QueueHandle_t queue_input;
uint8_t buf_tx_queue_input[4];

bool b_ready_thread_input = false;

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

    if (true != bh1750fvi_init())
    {
        error_set_u32(&err_thread_input, THREAD_INPUT_ERROR_INIT_LIGHT_SENSOR);
        
        return false;
    }

    queue_input = xQueueCreate(1, sizeof(buf_tx_queue_input)); 
    if (queue_input == 0)
    {
     printf("Failed to create queue= %p\n", queue_input);
    }

    b_ready_thread_input = true;

    return true;
}

bool thread_input_handle(void)
{
    if (true != bh1750fvi_handle())
    {
        error_set_u32(&err_thread_input, THREAD_INPUT_ERROR_INIT_LIGHT_SENSOR);

        return false;
    }

    float sensor_light = bh1750fvi_get_light_value();

    if (true != adc_handle())
    {
        return false;
    }

    printf("\n");

    memcpy(&buf_tx_queue_input, &sensor_light, 4);
    xQueueSend(queue_input, (void*)buf_tx_queue_input, (TickType_t)0);
    
    vTaskDelay(100);

    return true;
}

/* ---------------------------- Private functions ---------------------------- */

/* ---------------------------- Interrupt callbacks ---------------------------- */

