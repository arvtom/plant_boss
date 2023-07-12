/* File purpose is to control operating modes: 
    normal with sleep
    real time */

/* ---------------------------- Includes ---------------------------- */
#include "thread_app.h"

/* ---------------------------- Typedefs ---------------------------- */

/* ---------------------------- Global variables ---------------------------- */
SemaphoreHandle_t not_so_simple_mutex;
extern QueueHandle_t queue_message_wifi;
char buffer_tx_queue_message_wifi[50];

/* ---------------------------- Public functions ---------------------------- */
void thread_app(void *arg)
{
    // thread_app();
    thread_app_init();

    while (1)
    {
        thread_app_handle();
    }
}

bool thread_app_init(void)
{
    uint8_t res = app_function();
    printf("res=%d\n", res);

    return true;
}

void thread_app_handle(void)
{
        // printf("app\n");

    // xSemaphoreTake(sys.rtos.mutex_measure_humidity, portMAX_DELAY);

    // /* Critical section, which is protected from other threads by using mutex */
    // printf("measuring\n");

    // xSemaphoreGive(sys.rtos.mutex_measure_humidity);

    // sprintf(buffer_tx_queue_message_wifi, "Hello from Demo_Task 1\n");
    // xQueueSend(queue_message_wifi, (void*)buffer_tx_queue_message_wifi, (TickType_t)0);

    // sprintf(buffer_tx_queue_message_wifi, "Hello from Demo_Task 2\n");
    // xQueueSend(queue_message_wifi, (void*)buffer_tx_queue_message_wifi, (TickType_t)0); 

    // uint8_t res = app_function();
    // printf("res=%d\n", res+1);

    vTaskDelay(100);
}

uint8_t app_function(void)
{
    not_so_simple_mutex = xSemaphoreCreateMutex();
    xSemaphoreTake(not_so_simple_mutex, portMAX_DELAY);

    /* Critical section, which is protected from other threads by using mutex */
    // printf("calculating\n");

    xSemaphoreGive(not_so_simple_mutex);

    return 2u;
}

/* ---------------------------- Private functions ---------------------------- */

/* ---------------------------- Interrupt callbacks ---------------------------- */

