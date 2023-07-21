/* File purpose is to control operating modes: 
    normal with sleep
    real time */

/* ---------------------------- Includes ---------------------------- */
#include "thread_app.h"

/* ---------------------------- Typedefs ---------------------------- */

/* ---------------------------- Global variables ---------------------------- */
uint32_t err_thread_app = 0u;

extern uint32_t err_thread_input;
extern uint32_t err_thread_output;
extern uint32_t err_thread_network;
extern uint32_t err_thread_memory;

uint16_t length_buf_tx_queue_wifi = 0u;

SemaphoreHandle_t not_so_simple_mutex;
extern QueueHandle_t queue_wifi;
char buf_tx_queue_wifi[150];

extern QueueHandle_t queue_input;
uint8_t buf_rx_queue_input[16];

extern bool b_ready_thread_input;

/* ---------------------------- Public functions ---------------------------- */
void thread_app(void *arg)
{
    thread_app_init();

    while (1)
    {
        thread_app_handle();
    }
}

bool thread_app_init(void)
{
    vTaskDelay(100);
    printf("addr err_thread_app 0x%x\n", (unsigned int)&err_thread_app);
    
    uint8_t res = app_function();
    printf("res=%d\n", res);

    uint32_t value_notification;
    xTaskNotifyWait(0u, 0u, &value_notification, portMAX_DELAY);

    if (THREAD_MEMORY_TO_APP_RESULT_INIT != value_notification)
    {
        printf("error, unknown notification %lx\n", value_notification);

        return false;
    }

    printf("notification received\n");

    vTaskDelay(1);

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
        float light_input;
        float temperature_input;
        float humidity_input;
        float voltage_battery_input;

        memcpy(&light_input, &buf_rx_queue_input, 4);
        memcpy(&temperature_input, &buf_rx_queue_input[4], 4);
        memcpy(&humidity_input, &buf_rx_queue_input[8], 4);
        memcpy(&voltage_battery_input, &buf_rx_queue_input[12], 4);

        uint8_t device_id = 1u;
        int8_t rssi_wifi = wifi_get_rssi_value();
        uint8_t mode = 0u;
        uint8_t bat_low_flag = 0u;
        uint32_t sw_version = 20230816;
        uint32_t timer = (uint32_t)xTaskGetTickCount();

        /* calculate buf_tx length
            device 0-255                3B + 3
            humidity 0.0-100.0%         5B + 4
            light 0.0-65535.0           7B + 4
            temperature -30-60          3B + 4
            bat_voltage 0.0-4.2         3B + 4
            rssi_wifi -100-100          4B + 4
            mode 0-3                    1B + 4
            bat_low_flag 0-1            1B + 4
            error_app                   4B + 4
            error_input                 4B + 5
            error_output                4B + 5
            error_network               4B + 5
            error_memory                4B + 5
            sw_version                  4B + 5
            timer_or_period             4B + 5

            total                       55 + 35 = 90   
            */
           
        int ret = snprintf(buf_tx_queue_wifi, 150, 
            "a1=%d&a2=%3.1f&a3=%5.1f&a4=%2.1f&a5=%1.1f&a6=%d&a7=%d&a8=%d&a9=0x%x&a10=0x%x&a11=0x%x&a12=0x%x&a13=0x%x&a14=0x%x&a15=0x%x",
            device_id, humidity_input, light_input, temperature_input, voltage_battery_input,
            rssi_wifi, mode, bat_low_flag, 
            (unsigned int)err_thread_app, (unsigned int)err_thread_input, (unsigned int)err_thread_output, 
            (unsigned int)err_thread_network, (unsigned int)err_thread_memory, (unsigned int)sw_version, (unsigned int)timer);

        if (ret < 0 || ret > 150)
        {
            return false;
        }

        length_buf_tx_queue_wifi = (uint16_t)ret;

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

