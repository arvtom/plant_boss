/**
*  \file    error.h
*  \brief   Error management functions, which use individual bits to represent errors.
*  \author  arvtom
*/

/*------------------------------Includes------------------------------*/
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_log.h>

/*------------------------------Defines------------------------------*/

/*------------------------------Structures / enumerators------------------------------*/
/* 32bit error enumerator */
// typedef enum
// {
    // ERROR_BIT = 0x00000001U,
    // ERROR_BIT = 0x00000002U,
    // ERROR_BIT = 0x00000004U,
    // ERROR_BIT = 0x00000008U,
    // ERROR_BIT = 0x00000010U,
    // ERROR_BIT = 0x00000020U,
    // ERROR_BIT = 0x00000040U,
    // ERROR_BIT = 0x00000080U,
    // ERROR_BIT = 0x00000100U,
    // ERROR_BIT = 0x00000200U,
    // ERROR_BIT = 0x00000400U,
    // ERROR_BIT = 0x00000800U,
    // ERROR_BIT = 0x00001000U,
    // ERROR_BIT = 0x00002000U,
    // ERROR_BIT = 0x00004000U,
    // ERROR_BIT = 0x00008000U,
    // ERROR_BIT = 0x00010000U,
    // ERROR_BIT = 0x00020000U,
    // ERROR_BIT = 0x00040000U,
    // ERROR_BIT = 0x00080000U,
    // ERROR_BIT = 0x00100000U,
    // ERROR_BIT = 0x00200000U,
    // ERROR_BIT = 0x00400000U,
    // ERROR_BIT = 0x00800000U,
    // ERROR_BIT = 0x01000000U,
    // ERROR_BIT = 0x02000000U,
    // ERROR_BIT = 0x04000000U,
    // ERROR_BIT = 0x08000000U,
    // ERROR_BIT = 0x10000000U,
    // ERROR_BIT = 0x20000000U,
    // ERROR_BIT = 0x40000000U,
    // ERROR_BIT = 0x80000000U,
// }pcf8591_error_t;

/*------------------------------Public function prototypes------------------------------*/
void error_set_u32(uint32_t *p_err_var, uint32_t err_bit);
void error_clear_u32(uint32_t *p_err_var, uint32_t err_bit);
bool error_check_u32(uint32_t *p_err_var, uint32_t err_bit);
void error_handle(void);

/*------------------------------Private function prototypes------------------------------*/