
#ifndef THREAD_NETWORK_H
#define THREAD_NETWORK_H

/* ---------------------------- Includes ---------------------------- */
#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>
// #include <freertos/semphr.h>

/* ---------------------------- Typedefs ---------------------------- */

/* ---------------------------- Public functions ---------------------------- */
void thread_network(void *arg);
bool thread_network_init(void);
void thread_network_handle(void);

/* ---------------------------- Private functions ---------------------------- */

/* ---------------------------- Interrupt callbacks ---------------------------- */

#endif
