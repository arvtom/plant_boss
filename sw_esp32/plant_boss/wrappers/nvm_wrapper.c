/**
*  \file    nvm_wrapper.c
*  \brief   This file wraps around esp32 nvs driver.
*  \author  arvtom
*/

/*------------------------------Includes------------------------------*/
#include "nvm_wrapper.h"

/*------------------------------Defines------------------------------*/

/*------------------------------Variables / Macro calls------------------------------*/
int err_nvs_drv = 0;
uint32_t err_nvm = 0U;

static const char* tag_nvm = "nvm";
nvs_handle_t handle_nvs;
nvm_contents_t nvm_contents = {0};

/*------------------------------Public functions------------------------------*/
bool nvm_init(void)
{
    ESP_LOGI(tag_nvm, "addr err_nvm 0x%x\n", (unsigned int)&err_nvm);

    err_nvs_drv = nvs_flash_init();
    if (ESP_OK != err_nvs_drv)
    {
        error_set_u32(&err_nvm, NVM_ERROR_INIT);

        return false;
    }

    memset(&nvm_contents, 0u, sizeof(nvm_contents));
    
    return true;
}

bool nvm_handle_read(void)
{
    if (ESP_OK != nvs_open("plant_boss", NVS_READONLY, &handle_nvs)) 
    {
        ESP_LOGI(tag_nvm, "of");

        return false;
    }

    if (ESP_OK != nvs_get_u8(handle_nvs, KEY_NVS_DEVICE_ID, &nvm_contents.id))
    {
        ESP_LOGI(tag_nvm, "0f");

        nvs_close(handle_nvs);

        return false;
    }

    if (ESP_OK != nvs_get_u8(handle_nvs, KEY_NVS_DEVICE_MODE, &nvm_contents.mode))
    {
        ESP_LOGI(tag_nvm, "1f");

        nvs_close(handle_nvs);

        return false;
    }

    if (ESP_OK != nvs_get_u16(handle_nvs, KEY_NVS_THRESHOLD_BAT_VOLTAGE, &nvm_contents.bat_threshold))
    {
        ESP_LOGI(tag_nvm, "2f");

        nvs_close(handle_nvs);

        return false;
    }

    if (ESP_OK != nvs_get_u32(handle_nvs, KEY_NVS_PERIOD_MEASUREMENT, &nvm_contents.measurement_period))
    {
        ESP_LOGI(tag_nvm, "3f");

        nvs_close(handle_nvs);

        return false;
    }

    if (ESP_OK != nvs_get_u32(handle_nvs, KEY_NVS_CALIBRATION_SCALE, &nvm_contents.calibration_scale))
    {
        ESP_LOGI(tag_nvm, "4f");

        nvs_close(handle_nvs);

        return false;
    }

    if (ESP_OK != nvs_get_u32(handle_nvs, KEY_NVS_CALIBRATION_OFFSET, &nvm_contents.calibration_offset))
    {
        ESP_LOGI(tag_nvm, "5f");

        nvs_close(handle_nvs);

        return false;
    }

    if (ESP_OK != nvs_get_u64(handle_nvs, KEY_NVS_ERROR_APP, &nvm_contents.err_app))
    {
        ESP_LOGI(tag_nvm, "6f");

        nvs_close(handle_nvs);

        return false;
    }

    if (ESP_OK != nvs_get_u32(handle_nvs, KEY_NVS_ERROR_INPUT, &nvm_contents.err_input))
    {
        ESP_LOGI(tag_nvm, "7f");

        nvs_close(handle_nvs);

        return false;
    }

    if (ESP_OK != nvs_get_u32(handle_nvs, KEY_NVS_ERROR_OUTPUT, &nvm_contents.err_output))
    {
        ESP_LOGI(tag_nvm, "8f");

        nvs_close(handle_nvs);

        return false;
    }

    if (ESP_OK != nvs_get_u32(handle_nvs, KEY_NVS_ERROR_NETWORK, &nvm_contents.err_network))
    {
        ESP_LOGI(tag_nvm, "9f");

        nvs_close(handle_nvs);

        return false;
    }

    if (ESP_OK != nvs_get_u32(handle_nvs, KEY_NVS_ERROR_MEMORY, &nvm_contents.err_memory))
    {
        ESP_LOGI(tag_nvm, "10f");

        nvs_close(handle_nvs);

        return false;
    }

    if (ESP_OK != nvs_get_u32(handle_nvs, KEY_NVS_CRC_SW, &nvm_contents.crc_sw))
    {
        ESP_LOGI(tag_nvm, "11f");

        nvs_close(handle_nvs);

        return false;
    }

    nvs_close(handle_nvs);

    ESP_LOGI(tag_nvm, "nvs%x,%x,%x,%lx,%lx,%lx,%llx,%lx,%lx,%lx",
        nvm_contents.id,
        nvm_contents.mode,
        nvm_contents.bat_threshold,
        nvm_contents.measurement_period,
        nvm_contents.calibration_scale,
        nvm_contents.calibration_offset
        nvm_contents.err_app,
        nvm_contents.err_input,
        nvm_contents.err_output,
        nvm_contents.err_network,
        nvm_contents.err_memory
        );

    return true;
}

bool nvm_handle_write(void)
{
    if (ESP_OK != nvs_open("plant_boss", NVS_READWRITE, &handle_nvs)) 
    {
        return false;
    } 

    if (ESP_OK != nvs_set_u8(handle_nvs, KEY_NVS_DEVICE_ID, &nvm_contents.id))
    {
        nvs_close(handle_nvs);

        return false;
    }

    if (ESP_OK != nvs_set_u8(handle_nvs, KEY_NVS_DEVICE_MODE, &nvm_contents.mode))
    {
        nvs_close(handle_nvs);

        return false;
    }

    if (ESP_OK != nvs_set_u16(handle_nvs, KEY_NVS_THRESHOLD_BAT_VOLTAGE, &nvm_contents.bat_threshold))
    {
        nvs_close(handle_nvs);

        return false;
    }

    if (ESP_OK != nvs_set_u32(handle_nvs, KEY_NVS_PERIOD_MEASUREMENT, &nvm_contents.measurement_period))
    {
        nvs_close(handle_nvs);

        return false;
    }

    if (ESP_OK != nvs_set_u32(handle_nvs, KEY_NVS_CALIBRATION_SCALE, &nvm_contents.calibration_scale))
    {
        nvs_close(handle_nvs);

        return false;
    }

    if (ESP_OK != nvs_set_u32(handle_nvs, KEY_NVS_CALIBRATION_OFFSET, &nvm_contents.calibration_offset))
    {
        nvs_close(handle_nvs);

        return false;
    }

    if (ESP_OK != nvs_set_u64(handle_nvs, KEY_NVS_ERROR_APP, &nvm_contents.err_app))
    {
        nvs_close(handle_nvs);

        return false;
    }

    if (ESP_OK != nvs_set_u32(handle_nvs, KEY_NVS_ERROR_INPUT, &nvm_contents.err_input))
    {
        nvs_close(handle_nvs);

        return false;
    }

    if (ESP_OK != nvs_set_u32(handle_nvs, KEY_NVS_ERROR_OUTPUT, &nvm_contents.err_output))
    {
        nvs_close(handle_nvs);

        return false;
    }

    if (ESP_OK != nvs_set_u32(handle_nvs, KEY_NVS_ERROR_NETWORK, &nvm_contents.err_network))
    {
        nvs_close(handle_nvs);

        return false;
    }

    if (ESP_OK != nvs_set_u32(handle_nvs, KEY_NVS_ERROR_MEMORY, &nvm_contents.err_memory))
    {
        nvs_close(handle_nvs);

        return false;
    }

    if (ESP_OK != nvs_commit(handle_nvs))
    {
        nvs_close(handle_nvs);

        return false;
    }

    nvs_close(handle_nvs);

    return true;
}

uint8_t nvm_get_id(void)
{
    return nvm_contents.id;
}

uint8_t nvm_get_mode(void)
{
    return nvm_contents.mode;
}

uint16_t nvm_get_bat_threshold(void)
{
    return nvm_contents.bat_threshold;
}

uint32_t nvm_get_measurement_period(void)
{
    return nvm_contents.measurement_period;
}

float nvm_get_calibration_scale(void)
{
    return nvm_contents.calibration_scale;
}

float nvm_get_calibration_offset(void)
{
    return nvm_contents.calibration_offset;
}

uint64_t nvm_get_err_app(void)
{
    return nvm_contents.err_app;
}

uint32_t nvm_get_err_input(void)
{
    return nvm_contents.err_input;
}

uint32_t nvm_get_err_output(void)
{
    return nvm_contents.err_output;
}

uint32_t nvm_get_err_network(void)
{
    return nvm_contents.err_network;
}

uint32_t nvm_get_err_memory(void)
{
    return nvm_contents.err_memory;
}

/*------------------------------Private functions------------------------------*/