
/* ---------------------------- Includes ---------------------------- */
#include "thread_output.h"

/* ---------------------------- Typedefs ---------------------------- */

/* ---------------------------- Global variables ---------------------------- */
#warning issue_with_esp_err_t_where_not_allowed_variables_with_same_name_in_different_src
#warning reading_sensors_also_contains_power_outputs

uint32_t err_thread_output = 0u;

esp_err_t err_esp_output = ESP_OK;
uint8_t counter = 0u;

thread_output_t s_thread_output;

uint32_t notification_output = 0u;

extern TaskHandle_t handle_app;

/* ---------------------------- Public functions ---------------------------- */
void thread_output(void *arg)
{
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
    printf("addr err_thread_output 0x%x\n", (unsigned int)&err_thread_output);

    xTaskNotifyWait(NOTIFICATION_TO_OUTPUT_REQ_INIT, 0u, &notification_output, portMAX_DELAY);
    if (notification_output != NOTIFICATION_TO_OUTPUT_REQ_INIT)
    {
        return false;
    }

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

    if (pdPASS != xTaskNotify(handle_app, NOTIFICATION_TO_APP_RES_INIT_OUTPUT, eSetBits))
    {
        return false;
    }

    printf("thread_output init ok\n");

    /* Give some time to other tasks to prevent WDT reset */
    vTaskDelay(1);

    return true;
}

bool thread_output_handle(void)
{
    /* TODO: check if it is time to turn on/off power for sensors */

    xTaskNotifyWait(NOTIFICATION_TO_OUTPUT_REQ_HANDLE_EXT_LED, 0u, &notification_output, portMAX_DELAY);
    if (notification_output != NOTIFICATION_TO_OUTPUT_REQ_HANDLE_EXT_LED)
    {
        return false;
    }

    counter++;

    if (true != gpio_handle_pin_output(27u, counter % 2))
    {
        error_set_u32(&s_thread_output.err, THREAD_OUTPUT_ERROR_HANDLE_EXT_LED_PIN);

        return false;
    }

    printf("thread_output handle ok\n");
    
    vTaskDelay(100);

    return true;
}

/* ---------------------------- Interrupt callbacks ---------------------------- */

