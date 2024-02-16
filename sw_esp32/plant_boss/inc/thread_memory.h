
#ifndef THREAD_MEMORY_H
#define THREAD_MEMORY_H

/* ---------------------------- Includes ---------------------------- */
#include <stdio.h>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_log.h>
#include <esp_flash_spi_init.h>
#include <rom/crc.h>

#include "error.h"
#include "nvm_wrapper.h"
#include "common_thread_objects.h"

/* ---------------------------- Typedefs ---------------------------- */
#define CRC32_INIT_VALUE            (0x00000000)
#define CRC32_XOR_VALUE             (0xffffffff)
#define CRC32_POLYNOME              (0x04c11db7)        /* already used by crc32_le function from esp lib. */
#define CRC32_REFLECT_IN_TRUE                           /* already used in source code */
#define CRC32_REFLECT_OUT_TRUE                          /* already used in source code */

/* ---------------------------- Public functions ---------------------------- */
void thread_memory(void *arg);
bool thread_memory_init(void);
bool thread_memory_handle(void);

/* ---------------------------- Private functions ---------------------------- */
bool thread_memory_init_check_flash_crc(void);

/* ---------------------------- Interrupt callbacks ---------------------------- */

#endif
