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
uint32_t err_adc = 0u;

adc_oneshot_unit_handle_t adc1_handle;

static const char* tag_adc = "adc";

/*------------------------------Public functions------------------------------*/
bool adc_init(void)
{
    ESP_LOGI(tag_adc, "addr err_adc 0x%x\n", (unsigned int)&err_adc);

    adc_oneshot_unit_init_cfg_t init_config1 = 
    {
        .unit_id = ADC_UNIT_1,
        .ulp_mode = ADC_ULP_MODE_DISABLE,
    };

    err_adc_drv = adc_oneshot_new_unit(&init_config1, &adc1_handle);
    if (ESP_OK != err_adc_drv)
    {
        error_set_u32(&err_adc, ADC_ERROR_INIT_UNIT);

        return false;
    }

    return true;
}

// bool adc_handle(void)
// {

//     return true;
// }

bool adc_init_channel(adc_oneshot_chan_cfg_t* p_channel_config, adc_cali_line_fitting_config_t* p_calibration_config,
    adc_cali_handle_t* p_calibration_handle, adc_channel_t channel)
{
    err_adc_drv = adc_oneshot_config_channel(adc1_handle, channel, p_channel_config);
    if (ESP_OK != err_adc_drv)
    {
        error_set_u32(&err_adc, ADC_ERROR_INIT_CHANNEL);

        return false;
    }   

    /* Available calibration scheme is ADC_CALI_SCHEME_VER_LINE_FITTING.
        Characterization based on reference voltage stored in eFuse: ADC_CALI_LINE_FITTING_EFUSE_VAL_EFUSE_VREF. */

    err_adc_drv = adc_cali_create_scheme_line_fitting(p_calibration_config, p_calibration_handle);
    if (ESP_OK != err_adc_drv)
    {
        error_set_u32(&err_adc, ADC_ERROR_INIT_CALIBRATION);

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
        error_set_u32(&err_adc, ADC_ERROR_HANDLE_READ);

        return false;
    }

    /* Use manufacturer provided calibration */
    err_adc_drv = adc_cali_raw_to_voltage(*p_calibration_handle, adc_raw, p_adc_voltage);
    if (ESP_OK != err_adc_drv)
    {
        error_set_u32(&err_adc, ADC_ERROR_HANDLE_READ_CALIBRATION);

        return false;
    }

    return true;
}

/*------------------------------Private functions------------------------------*/

