/**
*  \file    lm20bim7.c
*  \brief   This file contains functions for reading temperature sensor lm20bim7 data.
*  \author  arvtom
*/

/*------------------------------Includes------------------------------*/
#include "lm20bim7.h"

/*------------------------------Defines------------------------------*/

/*------------------------------Variables / Macro calls------------------------------*/
uint32_t err_lm20bim7 = 0u;
adc_cali_handle_t adc_calibration_handle_temperature;
float temperature;

/*------------------------------Public functions------------------------------*/
bool lm20bim7_init(void)
{
    adc_oneshot_chan_cfg_t adc_channel_config_temperature = 
    {
        .bitwidth = ADC_BITWIDTH_12,
        .atten = ADC_ATTEN_DB_6,
    };

    adc_cali_line_fitting_config_t adc_calibration_config_temperature = 
    {
        .unit_id = ADC_UNIT_1,
        .atten = ADC_ATTEN_DB_6,
        .bitwidth = ADC_BITWIDTH_12,
    };

    if (true != adc_init_channel(&adc_channel_config_temperature, &adc_calibration_config_temperature,
                    &adc_calibration_handle_temperature, ADC_CHANNEL_3))
    {
        return false;
    }
    
    return true;
}

bool lm20bim7_handle(void)
{
    // /* temperature */
    // err_adc_drv = adc_oneshot_read(adc1_handle, ADC_CHANNEL_3, &adc_raw_temperature);
    // if (ESP_OK != err_adc_drv)
    // {
    //     return false;
    // }

    // /* Use manufacturer provided calibration */
    // err_adc_drv = adc_cali_raw_to_voltage(adc_calibration_handle_ch3_s, adc_raw_temperature, &adc_voltage_temperature_s32);
    // if (ESP_OK != err_adc_drv)
    // {
    //     return false;
    // }

    int adc_voltage;

    if (true != adc_handle_channel(&adc_calibration_handle_temperature, &adc_voltage, ADC_CHANNEL_3))
    {
        return false;
    }

    // adc_voltage_temperature_f = (float)adc_voltage / 1000;

    temperature = -1481.96 + 
        sqrt(2.1962 * pow(10, 6) + ((1.8639 - ((float)adc_voltage / 1000)) / (3.88 * pow(10, -6))));
    printf("temperature %f\n", temperature);

    return true;
}

float lm20bim7_get_temperature_value(void)
{
    return temperature;
}

/*------------------------------Private functions------------------------------*/