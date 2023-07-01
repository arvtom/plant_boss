
// #include <stdint.h>
// #include <math.h>
// #include <driver/gpio.h>
// #include <esp_adc/adc_oneshot.h>
// #include <esp_adc/adc_cali.h>
// #include <esp_adc/adc_cali_scheme.h>
// #include <driver/i2c.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>
#include <freertos/semphr.h>

#include "thread_app.h"
#include "thread_input.h"
#include "thread_output.h"
#include "thread_network.h"
#include "thread_memory.h"

#define STACK_THREAD_APP            4096u
#define STACK_THREAD_INPUT          4096u
#define STACK_THREAD_OUTPUT         4096u
#define STACK_THREAD_NETWORK        4096u
#define STACK_THREAD_MEMORY         4096u

#define PRIORITY_THREAD_APP         10u
#define PRIORITY_THREAD_INPUT       10u
#define PRIORITY_THREAD_OUTPUT      10u
#define PRIORITY_THREAD_NETWORK     10u
#define PRIORITY_THREAD_MEMORY      10u

TaskHandle_t addr_thread_app = NULL;
TaskHandle_t addr_thread_input = NULL;
TaskHandle_t addr_thread_output = NULL;
TaskHandle_t addr_thread_network = NULL;
TaskHandle_t addr_thread_memory = NULL;

QueueHandle_t queue;
char txBuffer[50];

SemaphoreHandle_t SimpleMutex;

// void thread_app(void *arg);
// void thread_input(void *arg);
// void thread_output(void *arg);
// void thread_network(void *arg);
// void thread_memory(void *arg);

void thread_app_handle(void)
{
    char txBuffer[50];
    queue = xQueueCreate(5, sizeof(txBuffer)); 
    if (queue == 0)
    {
     printf("Failed to create queue= %p\n", queue);
    }
    
    while (1)
    {
        // printf("app\n");

        xSemaphoreTake(SimpleMutex, portMAX_DELAY);

        /* Critical section, which cannot be interrupted by other threads */
        printf("measuring\n");
        
        xSemaphoreGive(SimpleMutex);

        sprintf(txBuffer, "Hello from Demo_Task 1\n");
        xQueueSend(queue, (void*)txBuffer, (TickType_t)0);

        sprintf(txBuffer, "Hello from Demo_Task 2\n");
        xQueueSend(queue, (void*)txBuffer, (TickType_t)0); 

        vTaskDelay(100);
    }
}

void thread_input_handle(void)
{
    // printf("input\n");
    // vTaskDelay(100);

    while (1)
    {
        vTaskDelay(100);
        // taskYIELD();
    }
}

void thread_output_handle(void)
{
    // printf("output\n");
    // vTaskDelay(100);

    while (1)
    {
        vTaskDelay(100);
        // taskYIELD();
    }
}

void thread_network_handle(void)
{
    // printf("network\n");
    // vTaskDelay(100);
    char rxBuffer[50];

    while (1)
    {
        if (xQueueReceive(queue, &(rxBuffer), (TickType_t)5))
        {
            printf("Received data from queue == %s\n", rxBuffer);
            vTaskDelay(10);
        }
    }
}

void thread_memory_handle(void)
{
    // printf("memory\n");
    // vTaskDelay(100);

    while (1)
    {
        vTaskDelay(100);
        // taskYIELD();
    }
}



void thread_app(void *arg)
{
    thread_app_handle();
}

void thread_input(void *arg)
{
    thread_input_handle();
}

void thread_output(void *arg)
{
    thread_output_handle();
}

void thread_network(void *arg)
{
    thread_network_handle();
}

void thread_memory(void *arg)
{
    thread_memory_handle();
}

void app_main(void)
{
    SimpleMutex = xSemaphoreCreateMutex();
    
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
