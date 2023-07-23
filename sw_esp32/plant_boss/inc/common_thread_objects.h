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
#include <freertos/semphr.h>

/* ---------------------------- Defines ---------------------------- */
#define SIZE_QUEUE_INPUT_TO_APP         16
#define SIZE_QUEUE_WIFI_TO_APP          1
#define SIZE_QUEUE_MEMORY_TO_APP        1
#define SIZE_QUEUE_APP_TO_WIFI          150
#define SIZE_QUEUE_APP_TO_MEMORY        1

/* ---------------------------- Typedefs ---------------------------- */
typedef enum
{
    NOTIFICATION_TO_INPUT_REQ_INIT                      = 0x00000001,     /* bit 0 */
    NOTIFICATION_TO_INPUT_REQ_HANDLE_SENSORS            = 0x00000002,     /* bit 1 */
    NOTIFICATION_TO_INPUT_REQ_HANDLE_BATTERY            = 0x00000004,     /* bit 2 */
    NOTIFICATION_TO_INPUT_RES_HANDLE_PWR_HUMIDITY       = 0x00000008,     /* bit 3 */
    NOTIFICATION_TO_INPUT_RES_HANDLE_PWR_TEMPERATURE    = 0x00000010,     /* bit 4 */
    NOTIFICATION_TO_INPUT_RES_HANDLE_PWR_LIGHT          = 0x00000020,     /* bit 5 */
    // NOTIFICATION_TO_ = 0x00000040,     /* bit 6 */
    // NOTIFICATION_TO_ = 0x00000080,     /* bit 7 */
    // NOTIFICATION_TO_ = 0x00000100,     /* bit 8 */
    // NOTIFICATION_TO_ = 0x00000200,     /* bit 9 */
    // NOTIFICATION_TO_ = 0x00000400,     /* bit 10 */
    // NOTIFICATION_TO_ = 0x00000800,     /* bit 11 */
    // NOTIFICATION_TO_ = 0x00001000,     /* bit 12 */
    // NOTIFICATION_TO_ = 0x00002000,     /* bit 13 */
    // NOTIFICATION_TO_ = 0x00004000,     /* bit 14 */
    // NOTIFICATION_TO_ = 0x00008000,     /* bit 15 */
    // NOTIFICATION_TO_ = 0x00010000,     /* bit 16 */
    // NOTIFICATION_TO_ = 0x00020000,     /* bit 17 */
    // NOTIFICATION_TO_ = 0x00040000,     /* bit 18 */
    // NOTIFICATION_TO_ = 0x00080000,     /* bit 19 */
    // NOTIFICATION_TO_ = 0x00100000,     /* bit 20 */
    // NOTIFICATION_TO_ = 0x00200000,     /* bit 21 */
    // NOTIFICATION_TO_ = 0x00400000,     /* bit 22 */
    // NOTIFICATION_TO_ = 0x00800000,     /* bit 23 */
    // NOTIFICATION_TO_ = 0x01000000,     /* bit 24 */
    // NOTIFICATION_TO_ = 0x02000000,     /* bit 25 */
    // NOTIFICATION_TO_ = 0x04000000,     /* bit 26 */
    // NOTIFICATION_TO_ = 0x08000000,     /* bit 27 */
    // NOTIFICATION_TO_ = 0x10000000,     /* bit 28 */
    // NOTIFICATION_TO_ = 0x20000000,     /* bit 29 */
    // NOTIFICATION_TO_ = 0x40000000,     /* bit 30 */
    // NOTIFICATION_TO_ = 0x80000000,     /* bit 31 */
}
notification_to_input_t;

typedef enum
{
    NOTIFICATION_TO_OUTPUT_REQ_INIT                     = 0x00000001,     /* bit 0 */
    NOTIFICATION_TO_OUTPUT_REQ_HANDLE_EXT_LED           = 0x00000002,     /* bit 1 */
    NOTIFICATION_TO_OUTPUT_REQ_HANDLE_PWR_HUMIDITY      = 0x00000004,     /* bit 2 */
    NOTIFICATION_TO_OUTPUT_REQ_HANDLE_PWR_TEMPERATURE   = 0x00000008,     /* bit 3 */
    NOTIFICATION_TO_OUTPUT_REQ_HANDLE_PWR_LIGHT         = 0x00000010,     /* bit 4 */
//     NOTIFICATION_TO_ = 0x00000020,     /* bit 5 */
//     NOTIFICATION_TO_ = 0x00000040,     /* bit 6 */
//     NOTIFICATION_TO_ = 0x00000080,     /* bit 7 */
//     NOTIFICATION_TO_ = 0x00000100,     /* bit 8 */
//     NOTIFICATION_TO_ = 0x00000200,     /* bit 9 */
//     NOTIFICATION_TO_ = 0x00000400,     /* bit 10 */
//     NOTIFICATION_TO_ = 0x00000800,     /* bit 11 */
//     NOTIFICATION_TO_ = 0x00001000,     /* bit 12 */
//     NOTIFICATION_TO_ = 0x00002000,     /* bit 13 */
//     NOTIFICATION_TO_ = 0x00004000,     /* bit 14 */
//     NOTIFICATION_TO_ = 0x00008000,     /* bit 15 */
//     NOTIFICATION_TO_ = 0x00010000,     /* bit 16 */
//     NOTIFICATION_TO_ = 0x00020000,     /* bit 17 */
//     NOTIFICATION_TO_ = 0x00040000,     /* bit 18 */
//     NOTIFICATION_TO_ = 0x00080000,     /* bit 19 */
//     NOTIFICATION_TO_ = 0x00100000,     /* bit 20 */
//     NOTIFICATION_TO_ = 0x00200000,     /* bit 21 */
//     NOTIFICATION_TO_ = 0x00400000,     /* bit 22 */
//     NOTIFICATION_TO_ = 0x00800000,     /* bit 23 */
//     NOTIFICATION_TO_ = 0x01000000,     /* bit 24 */
//     NOTIFICATION_TO_ = 0x02000000,     /* bit 25 */
//     NOTIFICATION_TO_ = 0x04000000,     /* bit 26 */
//     NOTIFICATION_TO_ = 0x08000000,     /* bit 27 */
//     NOTIFICATION_TO_ = 0x10000000,     /* bit 28 */
//     NOTIFICATION_TO_ = 0x20000000,     /* bit 29 */
//     NOTIFICATION_TO_ = 0x40000000,     /* bit 30 */
//     NOTIFICATION_TO_ = 0x80000000,     /* bit 31 */
}
notification_to_output_t;

typedef enum
{
    NOTIFICATION_TO_APP_RES_INIT_INPUT                  = 0x00000001,     /* bit 0 */
    NOTIFICATION_TO_APP_RES_INIT_OUTPUT                 = 0x00000002,     /* bit 1 */
    NOTIFICATION_TO_APP_RES_INIT_NETWORK                = 0x00000004,     /* bit 2 */
    NOTIFICATION_TO_APP_RES_INIT_MEMORY                 = 0x00000008,     /* bit 3 */
    NOTIFICATION_TO_APP_RES_HANDLE_EXT_LED              = 0x00000010,     /* bit 4 */
    // NOTIFICATION_TO_APP_RES_HANDLE_SENSORS              = 0x00000020,     /* bit 5 */
    // NOTIFICATION_TO_APP_RES_HANDLE_BATTERY              = 0x00000040,     /* bit 6 */
    // NOTIFICATION_TO_ = 0x00000080,     /* bit 7 */
    // NOTIFICATION_TO_ = 0x00000100,     /* bit 8 */
    // NOTIFICATION_TO_ = 0x00000200,     /* bit 9 */
    // NOTIFICATION_TO_ = 0x00000400,     /* bit 10 */
    // NOTIFICATION_TO_ = 0x00000800,     /* bit 11 */
    // NOTIFICATION_TO_ = 0x00001000,     /* bit 12 */
    // NOTIFICATION_TO_ = 0x00002000,     /* bit 13 */
    // NOTIFICATION_TO_ = 0x00004000,     /* bit 14 */
    // NOTIFICATION_TO_ = 0x00008000,     /* bit 15 */
    // NOTIFICATION_TO_ = 0x00010000,     /* bit 16 */
    // NOTIFICATION_TO_ = 0x00020000,     /* bit 17 */
    // NOTIFICATION_TO_ = 0x00040000,     /* bit 18 */
    // NOTIFICATION_TO_ = 0x00080000,     /* bit 19 */
    // NOTIFICATION_TO_ = 0x00100000,     /* bit 20 */
    // NOTIFICATION_TO_ = 0x00200000,     /* bit 21 */
    // NOTIFICATION_TO_ = 0x00400000,     /* bit 22 */
    // NOTIFICATION_TO_ = 0x00800000,     /* bit 23 */
    // NOTIFICATION_TO_ = 0x01000000,     /* bit 24 */
    // NOTIFICATION_TO_ = 0x02000000,     /* bit 25 */
    // NOTIFICATION_TO_ = 0x04000000,     /* bit 26 */
    // NOTIFICATION_TO_ = 0x08000000,     /* bit 27 */
    // NOTIFICATION_TO_ = 0x10000000,     /* bit 28 */
    // NOTIFICATION_TO_ = 0x20000000,     /* bit 29 */
    // NOTIFICATION_TO_ = 0x40000000,     /* bit 30 */
    // NOTIFICATION_TO_ = 0x80000000,     /* bit 31 */
}
notification_to_app_t;

typedef enum
{
    NOTIFICATION_TO_NETWORK_REQ_INIT                    = 0x00000001,     /* bit 0 */
//     NOTIFICATION_TO_ = 0x00000002,     /* bit 1 */
//     NOTIFICATION_TO_ = 0x00000004,     /* bit 2 */
//     NOTIFICATION_TO_ = 0x00000008,     /* bit 3 */
//     NOTIFICATION_TO_ = 0x00000010,     /* bit 4 */
//     NOTIFICATION_TO_ = 0x00000020,     /* bit 5 */
//     NOTIFICATION_TO_ = 0x00000040,     /* bit 6 */
//     NOTIFICATION_TO_ = 0x00000080,     /* bit 7 */
//     NOTIFICATION_TO_ = 0x00000100,     /* bit 8 */
//     NOTIFICATION_TO_ = 0x00000200,     /* bit 9 */
//     NOTIFICATION_TO_ = 0x00000400,     /* bit 10 */
//     NOTIFICATION_TO_ = 0x00000800,     /* bit 11 */
//     NOTIFICATION_TO_ = 0x00001000,     /* bit 12 */
//     NOTIFICATION_TO_ = 0x00002000,     /* bit 13 */
//     NOTIFICATION_TO_ = 0x00004000,     /* bit 14 */
//     NOTIFICATION_TO_ = 0x00008000,     /* bit 15 */
//     NOTIFICATION_TO_ = 0x00010000,     /* bit 16 */
//     NOTIFICATION_TO_ = 0x00020000,     /* bit 17 */
//     NOTIFICATION_TO_ = 0x00040000,     /* bit 18 */
//     NOTIFICATION_TO_ = 0x00080000,     /* bit 19 */
//     NOTIFICATION_TO_ = 0x00100000,     /* bit 20 */
//     NOTIFICATION_TO_ = 0x00200000,     /* bit 21 */
//     NOTIFICATION_TO_ = 0x00400000,     /* bit 22 */
//     NOTIFICATION_TO_ = 0x00800000,     /* bit 23 */
//     NOTIFICATION_TO_ = 0x01000000,     /* bit 24 */
//     NOTIFICATION_TO_ = 0x02000000,     /* bit 25 */
//     NOTIFICATION_TO_ = 0x04000000,     /* bit 26 */
//     NOTIFICATION_TO_ = 0x08000000,     /* bit 27 */
//     NOTIFICATION_TO_ = 0x10000000,     /* bit 28 */
//     NOTIFICATION_TO_ = 0x20000000,     /* bit 29 */
//     NOTIFICATION_TO_ = 0x40000000,     /* bit 30 */
//     NOTIFICATION_TO_ = 0x80000000,     /* bit 31 */
}
notification_to_network_t;

typedef enum
{
    NOTIFICATION_TO_MEMORY_REQ_INIT                     = 0x00000001,     /* bit 0 */
//     NOTIFICATION_TO_ = 0x00000002,     /* bit 1 */
//     NOTIFICATION_TO_ = 0x00000004,     /* bit 2 */
//     NOTIFICATION_TO_ = 0x00000008,     /* bit 3 */
//     NOTIFICATION_TO_ = 0x00000010,     /* bit 4 */
//     NOTIFICATION_TO_ = 0x00000020,     /* bit 5 */
//     NOTIFICATION_TO_ = 0x00000040,     /* bit 6 */
//     NOTIFICATION_TO_ = 0x00000080,     /* bit 7 */
//     NOTIFICATION_TO_ = 0x00000100,     /* bit 8 */
//     NOTIFICATION_TO_ = 0x00000200,     /* bit 9 */
//     NOTIFICATION_TO_ = 0x00000400,     /* bit 10 */
//     NOTIFICATION_TO_ = 0x00000800,     /* bit 11 */
//     NOTIFICATION_TO_ = 0x00001000,     /* bit 12 */
//     NOTIFICATION_TO_ = 0x00002000,     /* bit 13 */
//     NOTIFICATION_TO_ = 0x00004000,     /* bit 14 */
//     NOTIFICATION_TO_ = 0x00008000,     /* bit 15 */
//     NOTIFICATION_TO_ = 0x00010000,     /* bit 16 */
//     NOTIFICATION_TO_ = 0x00020000,     /* bit 17 */
//     NOTIFICATION_TO_ = 0x00040000,     /* bit 18 */
//     NOTIFICATION_TO_ = 0x00080000,     /* bit 19 */
//     NOTIFICATION_TO_ = 0x00100000,     /* bit 20 */
//     NOTIFICATION_TO_ = 0x00200000,     /* bit 21 */
//     NOTIFICATION_TO_ = 0x00400000,     /* bit 22 */
//     NOTIFICATION_TO_ = 0x00800000,     /* bit 23 */
//     NOTIFICATION_TO_ = 0x01000000,     /* bit 24 */
//     NOTIFICATION_TO_ = 0x02000000,     /* bit 25 */
//     NOTIFICATION_TO_ = 0x04000000,     /* bit 26 */
//     NOTIFICATION_TO_ = 0x08000000,     /* bit 27 */
//     NOTIFICATION_TO_ = 0x10000000,     /* bit 28 */
//     NOTIFICATION_TO_ = 0x20000000,     /* bit 29 */
//     NOTIFICATION_TO_ = 0x40000000,     /* bit 30 */
//     NOTIFICATION_TO_ = 0x80000000,     /* bit 31 */
}
notification_to_memory_t;

// typedef enum
// {
//     NOTIFICATION_TO_ = 0x00000001,     /* bit 0 */
//     NOTIFICATION_TO_ = 0x00000002,     /* bit 1 */
//     NOTIFICATION_TO_ = 0x00000004,     /* bit 2 */
//     NOTIFICATION_TO_ = 0x00000008,     /* bit 3 */
//     NOTIFICATION_TO_ = 0x00000010,     /* bit 4 */
//     NOTIFICATION_TO_ = 0x00000020,     /* bit 5 */
//     NOTIFICATION_TO_ = 0x00000040,     /* bit 6 */
//     NOTIFICATION_TO_ = 0x00000080,     /* bit 7 */
//     NOTIFICATION_TO_ = 0x00000100,     /* bit 8 */
//     NOTIFICATION_TO_ = 0x00000200,     /* bit 9 */
//     NOTIFICATION_TO_ = 0x00000400,     /* bit 10 */
//     NOTIFICATION_TO_ = 0x00000800,     /* bit 11 */
//     NOTIFICATION_TO_ = 0x00001000,     /* bit 12 */
//     NOTIFICATION_TO_ = 0x00002000,     /* bit 13 */
//     NOTIFICATION_TO_ = 0x00004000,     /* bit 14 */
//     NOTIFICATION_TO_ = 0x00008000,     /* bit 15 */
//     NOTIFICATION_TO_ = 0x00010000,     /* bit 16 */
//     NOTIFICATION_TO_ = 0x00020000,     /* bit 17 */
//     NOTIFICATION_TO_ = 0x00040000,     /* bit 18 */
//     NOTIFICATION_TO_ = 0x00080000,     /* bit 19 */
//     NOTIFICATION_TO_ = 0x00100000,     /* bit 20 */
//     NOTIFICATION_TO_ = 0x00200000,     /* bit 21 */
//     NOTIFICATION_TO_ = 0x00400000,     /* bit 22 */
//     NOTIFICATION_TO_ = 0x00800000,     /* bit 23 */
//     NOTIFICATION_TO_ = 0x01000000,     /* bit 24 */
//     NOTIFICATION_TO_ = 0x02000000,     /* bit 25 */
//     NOTIFICATION_TO_ = 0x04000000,     /* bit 26 */
//     NOTIFICATION_TO_ = 0x08000000,     /* bit 27 */
//     NOTIFICATION_TO_ = 0x10000000,     /* bit 28 */
//     NOTIFICATION_TO_ = 0x20000000,     /* bit 29 */
//     NOTIFICATION_TO_ = 0x40000000,     /* bit 30 */
//     NOTIFICATION_TO_ = 0x80000000,     /* bit 31 */
// }
// notification_to__t;

/* ---------------------------- Public functions ---------------------------- */
bool common_thread_objects_init(void);

/* ---------------------------- Private functions ---------------------------- */

/* ---------------------------- Interrupt callbacks ---------------------------- */

#endif