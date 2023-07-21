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

// #define NOTIFY_APP_TO_INPUT_REQ_INIT
// #define NOTIFY_APP_TO_OUTPUT_REQ_INIT
// #define NOTIFY_APP_TO_NETWORK_REQ_INIT
// #define NOTIFY_APP_TO_MEMORY_REQ_INIT

// #define NOTIFY_APP_TO_INPUT_REQ_HANDLE
// #define

/* ---------------------------- Public functions ---------------------------- */

/* ---------------------------- Private functions ---------------------------- */

/* ---------------------------- Interrupt callbacks ---------------------------- */

#endif