/**
*  \file    adc_wrapper.h
*  \brief   This file wraps around esp32 adc driver.
*  \author  arvtom
*/

#ifndef ADC_WRAPPER_H
#define ADC_WRAPPER_H

/*------------------------------Includes------------------------------*/
#include <stdbool.h>
#include <math.h>

#include <esp_adc/adc_oneshot.h>
#include <esp_adc/adc_cali.h>
#include <esp_adc/adc_cali_scheme.h>
#include <esp_err.h>
#include <esp_log.h>

#include "error.h"

/*------------------------------Defines------------------------------*/

/*------------------------------Structures / enumerators------------------------------*/
typedef enum
{
    ADC_ERROR_INIT_UNIT                 = 0x00000001U,
    ADC_ERROR_INIT_CHANNEL              = 0x00000002U,
    ADC_ERROR_INIT_CALIBRATION          = 0x00000004U,
    ADC_ERROR_HANDLE_READ               = 0x00000008U,
    ADC_ERROR_HANDLE_READ_CALIBRATION   = 0x00000010U,
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
} adc_error_t;

/*------------------------------Public function prototypes------------------------------*/
bool adc_init(void);
// bool adc_handle(void);

bool adc_init_channel(adc_oneshot_chan_cfg_t* p_channel_config, adc_cali_line_fitting_config_t* p_calibration_config,
    adc_cali_handle_t* p_calibration_handle, adc_channel_t channel);
bool adc_handle_channel(adc_cali_handle_t* p_calibration_handle, int* p_adc_voltage, adc_channel_t channel);

/*------------------------------Private function prototypes------------------------------*/

#endif /* ADC_WRAPPER_H */