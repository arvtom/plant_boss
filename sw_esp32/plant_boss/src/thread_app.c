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
char buf_rx_queue_wifi_to_app[20];
uint8_t length_buf_rx_queue_wifi_to_app;

uint8_t buf_tx_queue_memory[10];

uint32_t notification_app = 0u;

extern uint32_t err_thread_input;
extern uint32_t err_thread_output;
extern uint32_t err_thread_network;
extern uint32_t err_thread_memory;

extern QueueHandle_t queue_input_to_app;
extern QueueHandle_t queue_wifi_to_app;
extern QueueHandle_t queue_memory_to_app;
extern QueueHandle_t queue_app_to_wifi;
extern QueueHandle_t queue_app_to_memory;

extern TaskHandle_t handle_app;
extern TaskHandle_t handle_input;
extern TaskHandle_t handle_output;
extern TaskHandle_t handle_network;
extern TaskHandle_t handle_memory;

uint32_t delay_handle_thread_app = DELAY_HANDLE_THREAD_APP;
extern uint16_t threshold_voltage_battery;
uint8_t device_mode = 0u;
uint8_t device_id = 1u;

bool b_settings_updated = false;

UBaseType_t stack_watermark_app = 0u;
UBaseType_t stack_watermark_input = 0u;
UBaseType_t stack_watermark_output = 0u;
UBaseType_t stack_watermark_network = 0u;
UBaseType_t stack_watermark_memory = 0u;

static const char* tag_t_a = "t_a";

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
    // printf("addr err_thread_app 0x%x\n", (unsigned int)&err_thread_app);

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
    xTaskNotifyWait(0u, 0u, &notification_app, portMAX_DELAY);
    if ((notification_app & NOTIFICATION_TO_APP_RES_INIT_MEMORY) == 0u)
    {
        return false;
    }

    ulTaskNotifyValueClear(handle_app, NOTIFICATION_TO_APP_RES_INIT_MEMORY);

    /* Init thread_network, because there is no point for starting other threads if connection to database is not existing. */
    if (pdPASS != xTaskNotify(handle_network, NOTIFICATION_TO_NETWORK_REQ_INIT, eSetBits))
    {
        return false;
    }

    /* Wait until thread_network is init */
    xTaskNotifyWait(0u, 0u, &notification_app, portMAX_DELAY);
    if ((notification_app & NOTIFICATION_TO_APP_RES_INIT_NETWORK) == 0u)
    {
        return false;
    }
    
    ulTaskNotifyValueClear(handle_app, NOTIFICATION_TO_APP_RES_INIT_NETWORK);

    /* Init thread_output */
    if (pdPASS != xTaskNotify(handle_output, NOTIFICATION_TO_OUTPUT_REQ_INIT, eSetBits))
    {
        return false;
    }

    /* Wait until thread_output is init */
    xTaskNotifyWait(0u, 0u, &notification_app, portMAX_DELAY);
    if ((notification_app & NOTIFICATION_TO_APP_RES_INIT_OUTPUT) == 0u)
    {
        return false;
    }

    ulTaskNotifyValueClear(handle_app, NOTIFICATION_TO_APP_RES_INIT_OUTPUT);

    /* Init thread_input */
    if (pdPASS != xTaskNotify(handle_input, NOTIFICATION_TO_INPUT_REQ_INIT, eSetBits))
    {
        return false;
    }

    /* Wait until thread_input is init */
    xTaskNotifyWait(0u, 0u, &notification_app, portMAX_DELAY);
    if ((notification_app & NOTIFICATION_TO_APP_RES_INIT_INPUT) == 0u)
    {
        return false;
    }

    ulTaskNotifyValueClear(handle_app, NOTIFICATION_TO_APP_RES_INIT_INPUT);

    //config sleep mode to wake up from RTC
    if(ESP_OK != esp_sleep_enable_timer_wakeup(TIME_SLEEP))
    {
        return false;
    }

    /* TODO: read mode from nvm */

    ESP_LOGI(tag_t_a, "i");

    /* Give some time to other tasks to prevent WDT reset */
    vTaskDelay(1);

    return true;
}

bool thread_app_handle(void)
{
    // stack_watermark_app = uxTaskGetStackHighWaterMark(handle_app);
    // stack_watermark_input = uxTaskGetStackHighWaterMark(handle_input);
    // stack_watermark_output = uxTaskGetStackHighWaterMark(handle_output);
    // stack_watermark_network = uxTaskGetStackHighWaterMark(handle_network);
    // stack_watermark_memory = uxTaskGetStackHighWaterMark(handle_memory);

    // ESP_LOGI(tag_t_a, "a%d", stack_watermark_app);
    // ESP_LOGI(tag_t_a, "i%d", stack_watermark_input);
    // ESP_LOGI(tag_t_a, "o%d", stack_watermark_output);
    // ESP_LOGI(tag_t_a, "n%d", stack_watermark_network);
    // ESP_LOGI(tag_t_a, "m%d", stack_watermark_memory);

    /* Request settings from thread_network */
    if (pdPASS != xTaskNotify(handle_network, NOTIFICATION_TO_NETWORK_REQ_SETTINGS, eSetBits))
    {
        return false;
    }

    /* Wait for data to arrive from thread_network */
    if (xQueueReceive(queue_wifi_to_app, &buf_rx_queue_wifi_to_app, 1u))
    {
        if (true != thread_app_handle_settings())
        {
            return false;
        }
    }
    
    /* Request data from thread_input */
    if (pdPASS != xTaskNotify(handle_input, NOTIFICATION_TO_INPUT_REQ_HANDLE_SENSORS, eSetBits))
    {
        return false;
    }

    /* Wait for data to arrive from thread_input */
    if (xQueueReceive(queue_input_to_app, &(buf_rx_queue_input), 1))
    {
        if (true != thread_app_handle_data_packet())
        {
            return false;
        }
    }

    /* TODO: 
        check queue from network, if mode needs to be changed. If yes, write to nvm. 
        enter to sleep depending on mode
    */

    if (pdPASS != xTaskNotify(handle_output, NOTIFICATION_TO_OUTPUT_REQ_HANDLE_EXT_LED, eSetBits))
    {
        return false;
    }

    xTaskNotifyWait(0u, 0u, &notification_app, 1);
    if ((notification_app & NOTIFICATION_TO_APP_RES_HANDLE_EXT_LED) == 0u)
    {
        return false;
    }

    ulTaskNotifyValueClear(handle_app, NOTIFICATION_TO_APP_RES_HANDLE_EXT_LED);

    ESP_LOGI(tag_t_a, "h");

    if (1u == device_mode)
    {
        //deinit wifi before entering sleep mode
        esp_wifi_stop();

        /* Enter deep sleep. RAM will be deleted, so plant_boss will start from beginning. */
        esp_deep_sleep_start();
    }

    
    vTaskDelay(delay_handle_thread_app);

    return true;
}

/* ---------------------------- Private functions ---------------------------- */

bool thread_app_handle_settings(void)
{
    b_settings_updated = false;

    /* find length of data packet */
    uint8_t index_character = 0u;
    uint8_t index_delimiter = 0u;

    while (index_character < 20u)
    {
        if (';' == buf_rx_queue_wifi_to_app[index_character])
        {
            index_delimiter ++;

            if (index_delimiter >= 4u)
            {
                break;
            }
        }

        index_character ++;
    }

    length_buf_rx_queue_wifi_to_app = index_character + 1;

    ESP_LOGI(tag_t_a, "s%.*s", length_buf_rx_queue_wifi_to_app, (char *)buf_rx_queue_wifi_to_app);

    // Extract the first token
    char *token = strtok(buf_rx_queue_wifi_to_app, ";");
    // loop through the string to extract all other tokens
    uint8_t index = 0u;
    while (NULL != token) 
    {
        switch (index)
        {
            case 1u:
                uint8_t temp_mode = (uint8_t)strtol(token, NULL, 10);
                if (temp_mode != 0u && temp_mode != 1u)
                {
                    return false;
                }

                if (device_mode != temp_mode)
                {
                    b_settings_updated = true;
                }

                device_mode = temp_mode;
            break;

            case 2u:
                uint16_t temp_threshold = (uint16_t)(strtof(token, NULL) * 1000);
                if (temp_threshold < 3000u || temp_threshold > 4000u)
                {
                    return false;
                }

                if (threshold_voltage_battery != temp_threshold)
                {
                    b_settings_updated = true;
                }

                threshold_voltage_battery = temp_threshold;
            break;

            case 3u:
                uint32_t temp_delay = (uint32_t)(strtof(token, NULL) * 100.0);
                if (temp_delay < 100u || temp_delay > 8640000u)
                {
                    return false;
                }

                if (delay_handle_thread_app != temp_delay)
                {
                    b_settings_updated = true;
                }

                delay_handle_thread_app = temp_delay;
            break;

            default:
                //do nothing
        }

        token = strtok(NULL, ";");
        index ++;
    }

    if (true == b_settings_updated)
    {
        /* save new settings in nvm */
        memcpy(&buf_tx_queue_memory[0], &device_id, 1);
        memcpy(&buf_tx_queue_memory[1], &device_mode, 1);
        memcpy(&buf_tx_queue_memory[2], &threshold_voltage_battery, 2);
        memcpy(&buf_tx_queue_memory[4], &delay_handle_thread_app, 4);

        xQueueSend(queue_app_to_memory, (void*)buf_tx_queue_memory, (TickType_t)0);
    }

    return true;
}

bool thread_app_handle_data_packet(void)
{
    float light_input;
    float temperature_input;
    float humidity_input;
    float voltage_battery_input;

    memcpy(&light_input, &buf_rx_queue_input, 4);
    memcpy(&temperature_input, &buf_rx_queue_input[4], 4);
    memcpy(&humidity_input, &buf_rx_queue_input[8], 4);
    memcpy(&voltage_battery_input, &buf_rx_queue_input[12], 4);

    int8_t rssi_wifi = wifi_get_rssi_value();
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
        rssi_wifi, device_mode, bat_low_flag, 
        (unsigned int)err_thread_app, (unsigned int)err_thread_input, (unsigned int)err_thread_output, 
        (unsigned int)err_thread_network, (unsigned int)err_thread_memory, (unsigned int)sw_version, (unsigned int)timer);

    if (ret < 0 || ret > 150)
    {
        return false;
    }

    length_buf_tx_queue_wifi = (uint16_t)ret;

    xQueueSend(queue_app_to_wifi, (void*)buf_tx_queue_wifi, (TickType_t)0);

    return true;
}

/* ---------------------------- Interrupt callbacks ---------------------------- */

