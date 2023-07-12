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
adc_cali_handle_t adc_calibration_handle_ch3_s;
adc_cali_handle_t adc_calibration_handle_ch6_s;
adc_cali_handle_t adc_calibration_handle_ch7_s;

int adc_raw_temperature = 0;
int adc_raw_humidity = 0;
int adc_raw_battery = 0;

float adc_voltage_temperature_f = 0;
float temperature = 0;
int adc_voltage_temperature_s32 = 0;
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
    /* temperature */
    err_adc_drv = adc_oneshot_read(adc1_handle, ADC_CHANNEL_3, &adc_raw_temperature);
    if (ESP_OK != err_adc_drv)
    {
        return false;
    }

    /* Use manufacturer provided calibration */
    err_adc_drv = adc_cali_raw_to_voltage(adc_calibration_handle_ch3_s, adc_raw_temperature, &adc_voltage_temperature_s32);
    if (ESP_OK != err_adc_drv)
    {
        return false;
    }

    adc_voltage_temperature_f = (float)adc_voltage_temperature_s32 / 1000;

    temperature = -1481.96 + 
        sqrt(2.1962 * pow(10, 6) + ((1.8639 - adc_voltage_temperature_f) / (3.88 * pow(10, -6))));
    printf("temperature %f\n", temperature);

    /* humidity */
    err_adc_drv = adc_oneshot_read(adc1_handle, ADC_CHANNEL_6, &adc_raw_humidity);
    if (ESP_OK != err_adc_drv)
    {
        return false;
    }

    err_adc_drv = adc_cali_raw_to_voltage(adc_calibration_handle_ch6_s, adc_raw_humidity, &adc_voltage_humidity_s32);
    if (ESP_OK != err_adc_drv)
    {
        return false;
    }
    
    printf("adc_voltage_humidity_s32 %d\n", adc_voltage_humidity_s32);

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

/*------------------------------Private functions------------------------------*/
bool adc_init_channels(void)
{
    adc_oneshot_chan_cfg_t config_ch3 = 
    {
        .bitwidth = ADC_BITWIDTH_12,
        .atten = ADC_ATTEN_DB_6,
    };

    adc_oneshot_chan_cfg_t config_ch6 = 
    {
        .bitwidth = ADC_BITWIDTH_12,
        .atten = ADC_ATTEN_DB_11,
    };

    adc_oneshot_chan_cfg_t config_ch7 = 
    {
        .bitwidth = ADC_BITWIDTH_12,
        .atten = ADC_ATTEN_DB_11,
    };

    /* Available calibration scheme is ADC_CALI_SCHEME_VER_LINE_FITTING.
        Characterization based on reference voltage stored in eFuse: ADC_CALI_LINE_FITTING_EFUSE_VAL_EFUSE_VREF. */
    adc_cali_line_fitting_config_t adc_calibration_config_ch3_s = 
    {
        .unit_id = ADC_UNIT_1,
        .atten = ADC_ATTEN_DB_6,
        .bitwidth = ADC_BITWIDTH_12,
    };

    adc_cali_line_fitting_config_t adc_calibration_config_ch6_s = 
    {
        .unit_id = ADC_UNIT_1,
        .atten = ADC_ATTEN_DB_11,
        .bitwidth = ADC_BITWIDTH_12,
    };

    adc_cali_line_fitting_config_t adc_calibration_config_ch7_s = 
    {
        .unit_id = ADC_UNIT_1,
        .atten = ADC_ATTEN_DB_11,
        .bitwidth = ADC_BITWIDTH_12,
    };

    /* temperature */
    err_adc_drv = adc_oneshot_config_channel(adc1_handle, ADC_CHANNEL_3, &config_ch3);
    if (ESP_OK != err_adc_drv)
    {
        printf("error\n");

        return false;
    }   

    /* humidity */
    err_adc_drv = adc_oneshot_config_channel(adc1_handle, ADC_CHANNEL_6, &config_ch6);
    if (ESP_OK != err_adc_drv)
    {
        printf("error\n");

        return false;
    }   

    /* battery */
    err_adc_drv = adc_oneshot_config_channel(adc1_handle, ADC_CHANNEL_7, &config_ch7);
    if (ESP_OK != err_adc_drv)
    {
        printf("error\n");

        return false;
    }   

    err_adc_drv = adc_cali_create_scheme_line_fitting(&adc_calibration_config_ch3_s, &adc_calibration_handle_ch3_s);
    if (ESP_OK != err_adc_drv)
    {
        printf("error\n");

        return false;
    }   

    err_adc_drv = adc_cali_create_scheme_line_fitting(&adc_calibration_config_ch6_s, &adc_calibration_handle_ch6_s);
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
