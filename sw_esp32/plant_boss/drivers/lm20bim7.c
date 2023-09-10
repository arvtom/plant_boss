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

static const char* tag_lm20bim7 = "lm20bim7";

/*------------------------------Public functions------------------------------*/
bool lm20bim7_init(void)
{
    ESP_LOGI(tag_lm20bim7, "addr err_lm20bim7 0x%x\n", (unsigned int)&err_lm20bim7);

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
        error_set_u32(&err_lm20bim7, LM20BIM7_ERROR_INIT_ADC);

        return false;
    }
    
    return true;
}

bool lm20bim7_handle(void)
{
    int adc_voltage;

    if (true != adc_handle_channel(&adc_calibration_handle_temperature, &adc_voltage, ADC_CHANNEL_3))
    {
        error_set_u32(&err_lm20bim7, LM20BIM7_ERROR_HANDLE_ADC);

        return false;
    }

    temperature = -1481.96 + 
        sqrt(2.1962 * pow(10, 6) + ((1.8639 - ((float)adc_voltage / 1000)) / (3.88 * pow(10, -6))));

    return true;
}

float lm20bim7_get_temperature_value(void)
{
    return temperature;
}

/*------------------------------Private functions------------------------------*/