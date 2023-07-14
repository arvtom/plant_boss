
#ifndef THREAD_APP_H
#define THREAD_APP_H

/* ---------------------------- Includes ---------------------------- */
#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>
#include <freertos/queue.h>

/* ---------------------------- Typedefs ---------------------------- */
// typedef struct
// {

// }thread_app_t;

/* ---------------------------- Public functions ---------------------------- */
void thread_app(void *arg);
bool thread_app_init(void);
bool thread_app_handle(void);
uint8_t app_function(void);

/* ---------------------------- Private functions ---------------------------- */

/* ---------------------------- Interrupt callbacks ---------------------------- */

#endif
