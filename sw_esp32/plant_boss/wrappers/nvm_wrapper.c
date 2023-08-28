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

static const char* tag_nvm = "nvm";

/*------------------------------Public functions------------------------------*/
bool nvm_init(void)
{
    err_nvs_drv = nvs_flash_init();
    if (ESP_OK != err_nvs_drv)
    {
        return false;
    }
    
    return true;
}

bool nvm_handle(void)
{

    return true;
}

/*------------------------------Private functions------------------------------*/