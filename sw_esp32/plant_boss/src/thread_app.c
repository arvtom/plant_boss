/* File purpose is to control operating modes: 
    normal with sleep
    real time */

/* ---------------------------- Includes ---------------------------- */
#include "thread_app.h"

/* ---------------------------- Typedefs ---------------------------- */

/* ---------------------------- Global variables ---------------------------- */
uint32_t err_thread_app = 0u;

uint16_t length_buf_tx_queue_wifi = 0u;
char buf_tx_queue_wifi[150];
uint8_t buf_rx_queue_input[16];

uint32_t value_notification;

extern uint32_t err_thread_input;
extern uint32_t err_thread_output;
extern uint32_t err_thread_network;
extern uint32_t err_thread_memory;

extern QueueHandle_t queue_input_to_app;
extern QueueHandle_t queue_wifi_to_app;
extern QueueHandle_t queue_memory_to_app;
extern QueueHandle_t queue_app_to_wifi;
extern QueueHandle_t queue_app_to_memory;

extern TaskHandle_t handle_input;
extern TaskHandle_t handle_output;
extern TaskHandle_t handle_network;
extern TaskHandle_t handle_memory;

/* ---------------------------- Public functions ---------------------------- */
void thread_app(void *arg)
{
    if (true != thread_app_init())
    {
        error_handle();
    }

    while (1)
    {
        if (true != thread_app_handle())
        {
            error_handle();
        }
    }
}

bool thread_app_init(void)
{
    vTaskDelay(100);
    printf("addr err_thread_app 0x%x\n", (unsigned int)&err_thread_app);

    if (true != common_thread_objects_init())
    {
        return false;
    }

    /* Init thread_memory first, because it is needed by wifi. */
    if (pdPASS != xTaskNotify(handle_memory, NOTIFICATION_TO_MEMORY_REQ_INIT, eSetBits))
    {
        return false;
    }

    /* Wait until thread_memory is init. */
    xTaskNotifyWait(NOTIFICATION_TO_APP_RES_INIT_MEMORY, 0u, &value_notification, portMAX_DELAY);
    if (NOTIFICATION_TO_APP_RES_INIT_MEMORY != value_notification)
    {
        return false;
    }

    /* Init thread_network, because there is no point for starting other threads if connection to database is not existing. */
    if (pdPASS != xTaskNotify(handle_network, NOTIFICATION_TO_NETWORK_REQ_INIT, eSetBits))
    {
        return false;
    }

    /* Wait until thread_network is init */
    xTaskNotifyWait(NOTIFICATION_TO_APP_RES_INIT_NETWORK, 0u, &value_notification, portMAX_DELAY);
    if (NOTIFICATION_TO_APP_RES_INIT_NETWORK != value_notification)
    {
        return false;
    }

    /* Init thread_input */
    if (pdPASS != xTaskNotify(handle_input, NOTIFICATION_TO_INPUT_REQ_INIT, eSetBits))
    {
        return false;
    }

    /* Wait until thread_input is init */
    xTaskNotifyWait(NOTIFICATION_TO_APP_RES_INIT_INPUT, 0u, &value_notification, portMAX_DELAY);
    if (NOTIFICATION_TO_APP_RES_INIT_INPUT != value_notification)
    {
        return false;
    }

    /* Init thread_output */
    if (pdPASS != xTaskNotify(handle_output, NOTIFICATION_TO_OUTPUT_REQ_INIT, eSetBits))
    {
        return false;
    }

    /* Wait until thread_output is init */
    xTaskNotifyWait(NOTIFICATION_TO_APP_RES_INIT_OUTPUT, 0u, &value_notification, portMAX_DELAY);
    if (NOTIFICATION_TO_APP_RES_INIT_OUTPUT != value_notification)
    {
        return false;
    }

    /* TODO: read mode from nvm */

    printf("thread_app init ok\n");

    /* Give some time to other tasks to prevent WDT reset */
    vTaskDelay(1);

    return true;
}

bool thread_app_handle(void)
{
    /* Request data from thread_input */
    if (pdPASS != xTaskNotify(handle_input, NOTIFICATION_TO_INPUT_REQ_HANDLE_SENSORS, eSetBits))
    {
        return false;
    }

    /* Wait for data to arrive from thread_input */
    if (xQueueReceive(queue_input_to_app, &(buf_rx_queue_input), portMAX_DELAY))
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

        xQueueSend(queue_app_to_wifi, (void*)buf_tx_queue_wifi, (TickType_t)0);

        vTaskDelay(10);
    }

    /* TODO: 
        check queue from network, if mode needs to be changed. If yes, write to nvm. 
        enter to sleep depending on mode
    */

    printf("thread_app handle ok\n");

    vTaskDelay(100);

    return true;
}

/* ---------------------------- Private functions ---------------------------- */

/* ---------------------------- Interrupt callbacks ---------------------------- */

