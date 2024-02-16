
#ifndef THREAD_MEMORY_H
#define THREAD_MEMORY_H

/* ---------------------------- Includes ---------------------------- */
#include <stdio.h>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_log.h>

#include "error.h"
#include "nvm_wrapper.h"
#include "common_thread_objects.h"
#include "memory_crc.h"

/* ---------------------------- Typedefs ---------------------------- */


/* ---------------------------- Public functions ---------------------------- */
void thread_memory(void *arg);
bool thread_memory_init(void);
bool thread_memory_handle(void);

/* ---------------------------- Private functions ---------------------------- */


/* ---------------------------- Interrupt callbacks ---------------------------- */

#endif
