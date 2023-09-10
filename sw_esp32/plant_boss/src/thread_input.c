
/* ---------------------------- Includes ---------------------------- */
#include "thread_input.h"

/* ---------------------------- Typedefs ---------------------------- */

/* ---------------------------- Global variables ---------------------------- */
uint32_t err_thread_input = 0u;

esp_err_t err_esp = 0;

thread_input_t s_thread_input;

uint8_t buf_tx_queue_input[16];

uint32_t notification_input = 0u;

extern QueueHandle_t queue_input_to_app;

extern TaskHandle_t handle_app;
extern TaskHandle_t handle_input;

static const char* tag_t_i = "t_i";

/* ---------------------------- Public functions ---------------------------- */
void thread_input(void *arg)
{
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
    // printf("addr err_thread_input 0x%x\n", (unsigned int)&err_thread_input);

    xTaskNotifyWait(0u, 0u, &notification_input, portMAX_DELAY);
    if ((notification_input & NOTIFICATION_TO_INPUT_REQ_INIT) == 0u)
    {
        return false;
    }

    ulTaskNotifyValueClear(handle_input, NOTIFICATION_TO_INPUT_REQ_INIT);

    if (true != adc_init())
    {
        return false;
    }

    if (true != gpio_init())
    {
        return false;
    }

    if (true != bh1750fvi_init())
    {
        error_set_u32(&err_thread_input, THREAD_INPUT_ERROR_INIT_LIGHT);
        
        return false;
    }

    if (true != lm20bim7_init())
    {
        error_set_u32(&err_thread_input, THREAD_INPUT_ERROR_INIT_TEMPERATURE);
        
        return false;
    }

    if (true != hw390_init())
    {
        error_set_u32(&err_thread_input, THREAD_INPUT_ERROR_INIT_HUMIDITY);
        
        return false;
    }

    if (true != battery_init())
    {
        error_set_u32(&err_thread_input, THREAD_INPUT_ERROR_INIT_BATTERY);
        
        return false;
    }

    if (pdPASS != xTaskNotify(handle_app, NOTIFICATION_TO_APP_RES_INIT_INPUT, eSetBits))
    {
        return false;
    }

    ESP_LOGI(tag_t_i, "i");

    /* Give some time to other tasks to prevent WDT reset */
    vTaskDelay(1);

    return true;
}

bool thread_input_handle(void)
{
    xTaskNotifyWait(0u, 0u, &notification_input, portMAX_DELAY);
    if ((notification_input & NOTIFICATION_TO_INPUT_REQ_HANDLE_SENSORS) == 0u)
    {
        return false;
    }

    ulTaskNotifyValueClear(handle_input, NOTIFICATION_TO_INPUT_REQ_HANDLE_SENSORS);
    
    float light_bh1750fvi;
    float temperature_lm20bim7;
    float humidity_hw390;
    float voltage_battery;
    
    if (true != bh1750fvi_handle())
    {
        error_set_u32(&err_thread_input, THREAD_INPUT_ERROR_HANDLE_LIGHT);

        return false;
    }

    light_bh1750fvi = bh1750fvi_get_light_value();

    if (true != lm20bim7_handle())
    {
        error_set_u32(&err_thread_input, THREAD_INPUT_ERROR_HANDLE_TEMPERATURE);
        
        return false;
    }

    temperature_lm20bim7 = lm20bim7_get_temperature_value();

    if (true != hw390_handle())
    {
        error_set_u32(&err_thread_input, THREAD_INPUT_ERROR_HANDLE_HUMIDITY);
        
        return false;
    }

    humidity_hw390 = hw390_get_humidity_value();

    if (true != battery_handle())
    {
        error_set_u32(&err_thread_input, THREAD_INPUT_ERROR_HANDLE_BATTERY);
        
        return false;
    }

    voltage_battery = battery_get_voltage_value();

    memcpy(&buf_tx_queue_input, &light_bh1750fvi, 4);
    memcpy(&buf_tx_queue_input[4], &temperature_lm20bim7, 4);
    memcpy(&buf_tx_queue_input[8], &humidity_hw390, 4);
    memcpy(&buf_tx_queue_input[12], &voltage_battery, 4);

    xQueueSend(queue_input_to_app, (void*)buf_tx_queue_input, (TickType_t)0);

    ESP_LOGI(tag_t_i, "h");
    
    vTaskDelay(DELAY_HANDLE_THREAD_INPUT);

    return true;
}

/* ---------------------------- Private functions ---------------------------- */

/* ---------------------------- Interrupt callbacks ---------------------------- */

