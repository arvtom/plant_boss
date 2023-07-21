/**
*  \file    common_thread_objects.h
*  \brief   This file contains common thread objects: notifications and queues.
*  \author  arvtom
*/

#ifndef COMMON_THREAD_OBJECTS_H
#define COMMON_THREAD_OBJECTS_H

/* ---------------------------- Includes ---------------------------- */
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>

/* ---------------------------- Typedefs ---------------------------- */

#define THREAD_MEMORY_TO_APP_RESULT_INIT        0x00000001
#define THREAD_APP_TO_NETWORK_REQUEST_INIT      0x00000002
#define THREAD_NETWORK_TO_APP_RESULT_INIT       0x00000004

/* Try to group according who is receiving thread, because only these message values cannot repeat. Perhaps use typedef enum for this. */
#define NOTIFY_REQ_INIT_INPUT
#define NOTIFY_REQ_INIT_OUTPUT
#define NOTIFY_REQ_INIT_NETWORK
#define NOTIFY_REQ_INIT_MEMORY

#define NOTIFY_RES_INIT_INPUT
#define NOTIFY_RES_INIT_OUTPUT
#define NOTIFY_RES_INIT_NETWORK
#define NOTIFY_RES_INIT_MEMORY

#define NOTIFY_REQ_HANDLE_INPUT
/* result is arrived queue */

#define NOTIFY_REQ_HANDLE_INPUT_BATTERY
/* result is arrived queue */

#define NOTIFY_REQ_HANDLE_OUTPUT_PWR_HUMIDITY
#define NOTIFY_REQ_HANDLE_OUTPUT_PWR_TEMPERATURE
#define NOTIFY_REQ_HANDLE_OUTPUT_PWR_LIGHT

#define NOTIFY_RES_HANDLE_OUTPUT_PWR_HUMIDITY
#define NOTIFY_RES_HANDLE_OUTPUT_PWR_TEMPERATURE
#define NOTIFY_RES_HANDLE_OUTPUT_PWR_LIGHT

/* ---------------------------- Public functions ---------------------------- */
bool common_thread_objects_init(void);

/* ---------------------------- Private functions ---------------------------- */

/* ---------------------------- Interrupt callbacks ---------------------------- */

#endif