
// #include <stdint.h>
// #include <math.h>
// #include <driver/gpio.h>
// #include <esp_adc/adc_oneshot.h>
// #include <esp_adc/adc_cali.h>
// #include <esp_adc/adc_cali_scheme.h>
// #include <driver/i2c.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "main.h"
#include "thread_app.h"
#include "thread_input.h"
#include "thread_output.h"
#include "thread_network.h"
#include "thread_memory.h"

TaskHandle_t addr_thread_app = NULL;
TaskHandle_t addr_thread_input = NULL;
TaskHandle_t addr_thread_output = NULL;
TaskHandle_t addr_thread_network = NULL;
TaskHandle_t addr_thread_memory = NULL;

void app_main(void)
{   
    xTaskCreate(thread_app, "thread_app", 
        STACK_THREAD_APP, NULL, PRIORITY_THREAD_APP, &addr_thread_app);
    xTaskCreate(thread_input, "thread_input", 
        STACK_THREAD_INPUT, NULL, PRIORITY_THREAD_INPUT, &addr_thread_input);
    xTaskCreate(thread_output, "thread_output", 
        STACK_THREAD_OUTPUT, NULL, PRIORITY_THREAD_OUTPUT, &addr_thread_output);
    xTaskCreate(thread_network, "thread_network", 
        STACK_THREAD_NETWORK, NULL, PRIORITY_THREAD_NETWORK, &addr_thread_network);
    xTaskCreate(thread_memory, "thread_memory", 
        STACK_THREAD_MEMORY, NULL, PRIORITY_THREAD_MEMORY, &addr_thread_memory);
}
