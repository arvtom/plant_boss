
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
    // /* external led pin */
    // gpio_config_t io_conf_27 = {};
    // io_conf_27.intr_type = GPIO_INTR_DISABLE;
    // io_conf_27.mode = GPIO_MODE_OUTPUT;
    // io_conf_27.pin_bit_mask = (1ULL<<27u);
    // io_conf_27.pull_down_en = 0;
    // io_conf_27.pull_up_en = 0;

    // err_esp_output = gpio_config(&io_conf_27);
    // if (ESP_OK != err_esp_output)
    // {
    //     error_set_u32(&s_thread_output.err, THREAD_OUTPUT_ERROR_INIT_EXT_LED_PIN);

    //     return false;
    // }

    if (true != gpio_init_pin(27u, GPIO_MODE_OUTPUT, 
        GPIO_PULLUP_DISABLE, GPIO_PULLDOWN_DISABLE, GPIO_INTR_DISABLE))
    {
        error_set_u32(&s_thread_output.err, THREAD_OUTPUT_ERROR_INIT_EXT_LED_PIN);

        return false;
    }

    if (true != gpio_init())
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

