/**
*  \file    common_thread_objects.c
*  \brief   This file contains common thread objects: notifications and queues.
*  \author  arvtom
*/

/*------------------------------Includes------------------------------*/
#include "common_thread_objects.h"

/*------------------------------Defines------------------------------*/

/*------------------------------Variables / Macro calls------------------------------*/
TaskHandle_t handle_input;
TaskHandle_t handle_output;
TaskHandle_t handle_app;
TaskHandle_t handle_network;
TaskHandle_t handle_memory;

QueueHandle_t queue_input_to_app;       /* 
                                            read sensor values 
                                        */

QueueHandle_t queue_app_to_wifi;        /* 
                                            write data packet to database
                                        */
QueueHandle_t queue_app_to_memory;      /* 
                                            write mode
                                            write device id
                                            write errors
                                        */

QueueHandle_t queue_wifi_to_app;        /* 
                                            read mode 
                                        */

QueueHandle_t queue_memory_to_app;      /* 
                                            read mode
                                            read errors
                                        */

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

    return true;
}


/*------------------------------Private functions------------------------------*/