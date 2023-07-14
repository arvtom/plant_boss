/* File purpose is to control operating modes: 
    normal with sleep
    real time */

/* ---------------------------- Includes ---------------------------- */
#include "thread_app.h"

/* ---------------------------- Typedefs ---------------------------- */

/* ---------------------------- Global variables ---------------------------- */
SemaphoreHandle_t not_so_simple_mutex;
extern QueueHandle_t queue_wifi;
char buf_tx_queue_wifi[50];

extern QueueHandle_t queue_input;
uint8_t buf_rx_queue_input[16];

extern bool b_ready_thread_input;

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

bool thread_app_handle(void)
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

    if (false == b_ready_thread_input)
    {
        return true;
    }

    if (xQueueReceive(queue_input, &(buf_rx_queue_input), (TickType_t)5))
    {
        // printf("light: 0x%x%x%x%x\n", buf_rx_queue_input[0], buf_rx_queue_input[1], buf_rx_queue_input[2], buf_rx_queue_input[3]);

        float light_input;
        float temperature_input;
        float humidity_input;
        float voltage_battery_input;

        memcpy(&light_input, &buf_rx_queue_input, 4);
        memcpy(&temperature_input, &buf_rx_queue_input[4], 4);
        memcpy(&humidity_input, &buf_rx_queue_input[8], 4);
        memcpy(&voltage_battery_input, &buf_rx_queue_input[12], 4);

        int ret = snprintf(&buf_tx_queue_wifi[0], 50, "a1=%.1f&a2=%.1f&a3=%.1f&a4=%.1f", 
            light_input, temperature_input, humidity_input, voltage_battery_input);
        if (ret < 0 || ret > 50)
        {
            return false;
        }

        xQueueSend(queue_wifi, (void*)buf_tx_queue_wifi, (TickType_t)0);

        vTaskDelay(10);
    }

    vTaskDelay(100);

    return true;
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

