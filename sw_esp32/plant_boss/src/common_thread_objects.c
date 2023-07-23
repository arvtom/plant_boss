/**
*  \file    common_thread_objects.c
*  \brief   This file contains common thread objects: notifications and queues.
*  \author  arvtom
*/

/*------------------------------Includes------------------------------*/
#include "common_thread_objects.h"

/*------------------------------Defines------------------------------*/

/*------------------------------Variables / Macro calls------------------------------*/
SemaphoreHandle_t mutex_nvm;
SemaphoreHandle_t mutex_uart;

QueueHandle_t queue_input_to_app;       /* 
                                            read sensor values 
                                        */

QueueHandle_t queue_wifi_to_app;        /* 
                                            read mode 
                                        */

QueueHandle_t queue_memory_to_app;      /* 
                                            read mode
                                            read errors
                                        */

QueueHandle_t queue_app_to_wifi;        /* 
                                            write data packet to database
                                        */
QueueHandle_t queue_app_to_memory;      /* 
                                            write mode
                                            write device id
                                            write errors
                                        */

TaskHandle_t handle_input;
TaskHandle_t handle_output;
TaskHandle_t handle_app;
TaskHandle_t handle_network;
TaskHandle_t handle_memory;

/*------------------------------Public functions------------------------------*/
bool common_thread_objects_init(void)
{
    handle_input = xTaskGetHandle("thread_input");
    if (NULL == handle_input)
    {
        return false;
    }

    handle_output = xTaskGetHandle("thread_output");
    if (NULL == handle_output)
    {
        return false;
    }

    handle_app = xTaskGetHandle("thread_app");
    if (NULL == handle_app)
    {
        return false;
    }

    handle_network = xTaskGetHandle("thread_network");
    if (NULL == handle_network)
    {
        return false;
    }

    handle_memory = xTaskGetHandle("thread_memory");
    if (NULL == handle_memory)
    {
        return false;
    }

    mutex_nvm = xSemaphoreCreateMutex();
    if (NULL == mutex_nvm)
    {
        return false;
    }

    mutex_uart = xSemaphoreCreateMutex();
    if (NULL == mutex_uart)
    {
        return false;
    }

    queue_input_to_app = xQueueCreate(1, SIZE_QUEUE_INPUT_TO_APP); 
    if (queue_input_to_app == NULL)
    {
        return false;
    }

    queue_wifi_to_app = xQueueCreate(1, SIZE_QUEUE_WIFI_TO_APP); 
    if (queue_wifi_to_app == NULL)
    {
        return false;
    }

    queue_memory_to_app = xQueueCreate(1, SIZE_QUEUE_MEMORY_TO_APP); 
    if (queue_memory_to_app == NULL)
    {
        return false;
    }

    queue_app_to_wifi = xQueueCreate(1, SIZE_QUEUE_APP_TO_WIFI); 
    if (queue_app_to_wifi == NULL)
    {
        return false;
    }

    queue_app_to_memory = xQueueCreate(1, SIZE_QUEUE_APP_TO_MEMORY); 
    if (queue_app_to_memory == NULL)
    {
        return false;
    }

    return true;
}


/*------------------------------Private functions------------------------------*/