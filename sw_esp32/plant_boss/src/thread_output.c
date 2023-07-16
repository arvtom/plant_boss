
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
        error_set_u32(&s_thread_output.err, THREAD_OUTPUT_ERROR_INIT_EXT_LED_PIN);

        return false;
    }

    /* light sensor power supply pin */
    if (true != gpio_init_pin(4u, GPIO_MODE_OUTPUT, 
        GPIO_PULLUP_DISABLE, GPIO_PULLDOWN_DISABLE, GPIO_INTR_DISABLE))
    {
        printf("error\n");

        return false;
    }

    if (true != gpio_handle_pin_output(4u, true))
    {
        printf("error\n");

        return false;
    }

    /* light sensor reset pin */
    if (true != gpio_init_pin(17u, GPIO_MODE_OUTPUT, 
        GPIO_PULLUP_DISABLE, GPIO_PULLDOWN_DISABLE, GPIO_INTR_DISABLE))
    {
        printf("error\n");

        return false;
    }

    if (true != gpio_handle_pin_output(17u, false))
    {
        printf("error\n");

        return false;
    }

    vTaskDelay(2);

    if (true != gpio_handle_pin_output(17u, true))
    {
        printf("error\n");

        return false;
    }

    vTaskDelay(2);

    /* temperature sensor power supply pin */
    if (true != gpio_init_pin(32u, GPIO_MODE_OUTPUT, 
        GPIO_PULLUP_DISABLE, GPIO_PULLDOWN_DISABLE, GPIO_INTR_DISABLE))
    {
        printf("error\n");

        return false;
    }

    if (true != gpio_handle_pin_output(32u, true))
    {
        printf("error\n");

        return false;
    }

    /* humidity sensor power supply pin */
    if (true != gpio_init_pin(33u, GPIO_MODE_OUTPUT, 
        GPIO_PULLUP_DISABLE, GPIO_PULLDOWN_DISABLE, GPIO_INTR_DISABLE))
    {
        printf("error\n");

        return false;
    }

    if (true != gpio_handle_pin_output(33u, true))
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
        error_set_u32(&s_thread_output.err, THREAD_OUTPUT_ERROR_HANDLE_EXT_LED_PIN);

        return false;
    }
    
    vTaskDelay(100);

    return true;
}

/* ---------------------------- Interrupt callbacks ---------------------------- */

