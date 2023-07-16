
/* ---------------------------- Includes ---------------------------- */
#include "thread_output.h"

/* ---------------------------- Typedefs ---------------------------- */

/* ---------------------------- Global variables ---------------------------- */
#warning issue_with_esp_err_t_where_not_allowed_variables_with_same_name_in_different_src
#warning reading_sensors_also_contains_power_outputs

esp_err_t err_esp_output = ESP_OK;
uint8_t counter = 0;

thread_output_t s_thread_output;

bool b_ready_sensor_power;

uint32_t err_thread_output = 0u;

/* ---------------------------- Public functions ---------------------------- */
void thread_output(void *arg)
{
    // thread_app();
    if (true != thread_output_init())
    {
        error_handle();
    }

    while (1)
    {
        if (true != thread_output_handle())
        {
            error_handle();
        }
    }
}

/* ---------------------------- Private functions ---------------------------- */
bool thread_output_init(void)
{
    if (true != gpio_init_pin(27u, GPIO_MODE_OUTPUT, 
        GPIO_PULLUP_DISABLE, GPIO_PULLDOWN_DISABLE, GPIO_INTR_DISABLE))
    {
        printf("error\n");
        return false;
    }

    b_ready_sensor_power = true;

    return true;
}

bool thread_output_handle(void)
{
    counter++;

    if (true != gpio_handle_pin_output(27u, counter % 2))
    {
        printf("error\n");
        return false;
    }
    
    vTaskDelay(100);

    return true;
}

/* ---------------------------- Interrupt callbacks ---------------------------- */

