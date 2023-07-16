
#ifndef THREAD_MEMORY_H
#define THREAD_MEMORY_H

/* ---------------------------- Includes ---------------------------- */
#include <stdio.h>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "nvm_wrapper.h"

/* ---------------------------- Typedefs ---------------------------- */

/* ---------------------------- Public functions ---------------------------- */
void thread_memory(void *arg);
bool thread_memory_init(void);
void thread_memory_handle(void);

/* ---------------------------- Private functions ---------------------------- */

/* ---------------------------- Interrupt callbacks ---------------------------- */

#endif
