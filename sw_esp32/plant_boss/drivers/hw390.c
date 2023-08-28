/**
*  \file    hw390.c
*  \brief   This file contains functions for reading soil moisture sensor hw390 data.
*  \author  arvtom
*/

/*------------------------------Includes------------------------------*/
#include "hw390.h"

/*------------------------------Defines------------------------------*/

/*------------------------------Variables / Macro calls------------------------------*/
adc_cali_handle_t adc_calibration_handle_humidity;
float humidity;
uint32_t err_hw390 = 0u;

// static const char* tag_hw390 = "hw390";

/*------------------------------Public functions------------------------------*/
bool hw390_init(void)
{
    // printf("addr err_hw390 0x%x\n", (unsigned int)&err_hw390);

    adc_oneshot_chan_cfg_t adc_channel_config_humidity = 
    {
        .bitwidth = ADC_BITWIDTH_12,
        .atten = ADC_ATTEN_DB_11,
    };

    adc_cali_line_fitting_config_t adc_calibration_config_humidity = 
    {
        .unit_id = ADC_UNIT_1,
        .atten = ADC_ATTEN_DB_11,
        .bitwidth = ADC_BITWIDTH_12,
    }; 
    
    if (true != adc_init_channel(&adc_channel_config_humidity, &adc_calibration_config_humidity,
                    &adc_calibration_handle_humidity, ADC_CHANNEL_6))
    {
        return false;
    }
    
    return true;
}

bool hw390_handle(void)
{
    int adc_voltage;

    if (true != adc_handle_channel(&adc_calibration_handle_humidity, &adc_voltage, ADC_CHANNEL_6))
    {
        return false;
    }

    humidity = (float)adc_voltage / 3000 * 100;

    return true;
}

float hw390_get_humidity_value(void)
{
    return humidity;
}

/*------------------------------Private functions------------------------------*/