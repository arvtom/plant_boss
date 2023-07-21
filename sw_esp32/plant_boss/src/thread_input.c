
/* ---------------------------- Includes ---------------------------- */
#include "thread_input.h"

/* ---------------------------- Typedefs ---------------------------- */

/* ---------------------------- Global variables ---------------------------- */
uint32_t err_thread_input = 0u;

esp_err_t err_esp = 0;

thread_input_t s_thread_input;

extern QueueHandle_t queue_input;
uint8_t buf_tx_queue_input[16];

bool b_ready_thread_input = false;

extern bool b_ready_sensor_power;

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
    printf("addr err_thread_input 0x%x\n", (unsigned int)&err_thread_input);

    if (true != adc_init())
    {
        printf("error\n");
        return false;
    }

    while (false == b_ready_sensor_power)
    {
        vTaskDelay(1);
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

    queue_input = xQueueCreate(1, sizeof(buf_tx_queue_input)); 
    if (queue_input == 0)
    {
     printf("Failed to create queue= %p\n", queue_input);
    }

    b_ready_thread_input = true;

    vTaskDelay(1);

    return true;
}

bool thread_input_handle(void)
{
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

    xQueueSend(queue_input, (void*)buf_tx_queue_input, (TickType_t)0);
    
    vTaskDelay(100);

    return true;
}

/* ---------------------------- Private functions ---------------------------- */

/* ---------------------------- Interrupt callbacks ---------------------------- */

