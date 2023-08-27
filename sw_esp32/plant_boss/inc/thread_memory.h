
#ifndef THREAD_MEMORY_H
#define THREAD_MEMORY_H

/* ---------------------------- Includes ---------------------------- */
#include <stdio.h>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "error.h"
#include "nvm_wrapper.h"
#include "common_thread_objects.h"

/* ---------------------------- Typedefs ---------------------------- */

/* ---------------------------- Public functions ---------------------------- */
void thread_memory(void *arg);
bool thread_memory_init(void);
bool thread_memory_handle(void);

/* ---------------------------- Private functions ---------------------------- */
bool nvs_handle_read(void);
bool nvs_handle_write(void);

/* ---------------------------- Interrupt callbacks ---------------------------- */

#endif
