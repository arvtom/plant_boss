/**
*  \file    battery.c
*  \brief   This file contains functions for battery management.
*  \author  arvtom
*/

/*------------------------------Includes------------------------------*/
#include "battery.h"

/*------------------------------Defines------------------------------*/
static const char* tag_bat = "bat";

/*------------------------------Variables / Macro calls------------------------------*/
uint32_t err_battery = 0u;

adc_cali_handle_t adc_calibration_handle_voltage_battery;
float voltage_battery;
uint16_t threshold_voltage_battery = THRESHOLD_VOLTAGE_BATTERY;

static const char* tag_battery = "battery";

/*------------------------------Public functions------------------------------*/
bool battery_init(void)
{
    ESP_LOGI(tag_battery, "addr err_battery 0x%x\n", (unsigned int)&err_battery);

    adc_oneshot_chan_cfg_t adc_channel_config_voltage_battery = 
    {
        .bitwidth = ADC_BITWIDTH_12,
        .atten = ADC_ATTEN_DB_11,
    };

    adc_cali_line_fitting_config_t adc_calibration_config_voltage_battery = 
    {
        .unit_id = ADC_UNIT_1,
        .atten = ADC_ATTEN_DB_11,
        .bitwidth = ADC_BITWIDTH_12,
    };

    if (true != adc_init_channel(&adc_channel_config_voltage_battery, &adc_calibration_config_voltage_battery,
                    &adc_calibration_handle_voltage_battery, ADC_CHANNEL_7))
    {
        error_set_u32(&err_battery, BATTERY_ERROR_INIT_ADC);

        return false;
    }
    
    return true;
}

bool battery_handle(void)
{
    int adc_voltage;

    if (true != adc_handle_channel(&adc_calibration_handle_voltage_battery, &adc_voltage, ADC_CHANNEL_7))
    {
        error_set_u32(&err_battery, BATTERY_ERROR_HANDLE_ADC);

        return false;
    }

    voltage_battery = adc_voltage;

    if (voltage_battery < threshold_voltage_battery)
    {
        ESP_LOGI(tag_bat, "low battery");
    }

    return true;
}

float battery_get_voltage_value(void)
{
    return voltage_battery;
}

/*------------------------------Private functions------------------------------*/
