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
    
    return true;
}

// bool nvm_handle(void)
// {

//     return true;
// }

/*------------------------------Private functions------------------------------*/