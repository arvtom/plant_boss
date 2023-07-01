
// #include <stdint.h>
// #include <math.h>
// #include <driver/gpio.h>
// #include <esp_adc/adc_oneshot.h>
// #include <esp_adc/adc_cali.h>
// #include <esp_adc/adc_cali_scheme.h>
// #include <driver/i2c.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#define STACK_THREAD_INPUT          4096u
#define PRIORITY_THREAD_INPUT       10u

TaskHandle_t addr_thread_input = NULL;

void thread_input(void *arg)
{
    while(1){
        printf("thread input\n");
        vTaskDelay(100);
    }
}

void app_main(void)
{
    xTaskCreate(thread_input, "thread_input", 
        STACK_THREAD_INPUT, NULL, PRIORITY_THREAD_INPUT, &addr_thread_input);

    // while(1)
    // {
        


    // }
}