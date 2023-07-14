/**
*  \file    adc_wrapper.c
*  \brief   This file wraps around esp32 adc driver.
*  \author  arvtom
*/

/*------------------------------Includes------------------------------*/
#include "adc_wrapper.h"

/*------------------------------Defines------------------------------*/

/*------------------------------Variables / Macro calls------------------------------*/
int err_adc_drv = 0;

adc_oneshot_unit_handle_t adc1_handle;
adc_cali_handle_t adc_calibration_handle_ch7_s;

int adc_raw_humidity = 0;
int adc_raw_battery = 0;

int adc_voltage_humidity_s32 = 0;
int adc_voltage_battery_s32 = 0;

/*------------------------------Public functions------------------------------*/
bool adc_init(void)
{
    adc_oneshot_unit_init_cfg_t init_config1 = 
    {
        .unit_id = ADC_UNIT_1,
        .ulp_mode = ADC_ULP_MODE_DISABLE,
    };

    err_adc_drv = adc_oneshot_new_unit(&init_config1, &adc1_handle);
    if (ESP_OK != err_adc_drv)
    {

        return false;
    }

    if (true != adc_init_channels())
    {
        return false;
    }

    return true;
}

bool adc_handle(void)
{
    /* battery */
    err_adc_drv = adc_oneshot_read(adc1_handle, ADC_CHANNEL_7, &adc_raw_battery);
    if (ESP_OK != err_adc_drv)
    {
        return false;
    }

    err_adc_drv = adc_cali_raw_to_voltage(adc_calibration_handle_ch7_s, adc_raw_battery, &adc_voltage_battery_s32);
    if (ESP_OK != err_adc_drv)
    {
        return false;
    }
    
    printf("adc_voltage_battery_s32 %d\n", adc_voltage_battery_s32);

    return true;
}

bool adc_init_channel(adc_oneshot_chan_cfg_t* p_channel_config, adc_cali_line_fitting_config_t* p_calibration_config,
    adc_cali_handle_t* p_calibration_handle, adc_channel_t channel)
{
    err_adc_drv = adc_oneshot_config_channel(adc1_handle, channel, p_channel_config);
    if (ESP_OK != err_adc_drv)
    {
        printf("error\n");

        return false;
    }   

    err_adc_drv = adc_cali_create_scheme_line_fitting(p_calibration_config, p_calibration_handle);
    if (ESP_OK != err_adc_drv)
    {
        printf("error\n");

        return false;
    }

    return true;
}

bool adc_handle_channel(adc_cali_handle_t* p_calibration_handle, int* p_adc_voltage, adc_channel_t channel)
{
    int adc_raw;
    
    err_adc_drv = adc_oneshot_read(adc1_handle, channel, &adc_raw);
    if (ESP_OK != err_adc_drv)
    {
        return false;
    }

    /* Use manufacturer provided calibration */
    err_adc_drv = adc_cali_raw_to_voltage(*p_calibration_handle, adc_raw, p_adc_voltage);
    if (ESP_OK != err_adc_drv)
    {
        return false;
    }

    return true;
}

/*------------------------------Private functions------------------------------*/
bool adc_init_channels(void)
{
    adc_oneshot_chan_cfg_t config_ch7 = 
    {
        .bitwidth = ADC_BITWIDTH_12,
        .atten = ADC_ATTEN_DB_11,
    };

    /* Available calibration scheme is ADC_CALI_SCHEME_VER_LINE_FITTING.
        Characterization based on reference voltage stored in eFuse: ADC_CALI_LINE_FITTING_EFUSE_VAL_EFUSE_VREF. */

    adc_cali_line_fitting_config_t adc_calibration_config_ch7_s = 
    {
        .unit_id = ADC_UNIT_1,
        .atten = ADC_ATTEN_DB_11,
        .bitwidth = ADC_BITWIDTH_12,
    };

    /* battery */
    err_adc_drv = adc_oneshot_config_channel(adc1_handle, ADC_CHANNEL_7, &config_ch7);
    if (ESP_OK != err_adc_drv)
    {
        printf("error\n");

        return false;
    }    

    err_adc_drv = adc_cali_create_scheme_line_fitting(&adc_calibration_config_ch7_s, &adc_calibration_handle_ch7_s);
    if (ESP_OK != err_adc_drv)
    {
        printf("error\n");

        return false;
    }  

    return true;
}
