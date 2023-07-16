/**
*  \file    gpio_wrapper.c
*  \brief   This file wraps around esp32 gpio driver.
*  \author  arvtom
*/

/*------------------------------Includes------------------------------*/
#include "gpio_wrapper.h"

/*------------------------------Defines------------------------------*/

/*------------------------------Variables / Macro calls------------------------------*/
int err_gpio_drv = 0;

/*------------------------------Public functions------------------------------*/
// bool gpio_init(void)
// {

//     return true;
// }

// bool gpio_handle(void)
// {

//     return true;
// }

bool gpio_init_pin(uint8_t pin, gpio_mode_t mode, gpio_pullup_t pull_up, gpio_pulldown_t pull_down, gpio_int_type_t intr)
{
    gpio_config_t config = {};
    config.pin_bit_mask = (1ULL<<pin);
    config.mode = mode;
    config.pull_up_en = pull_up;
    config.pull_down_en = pull_down;
    config.intr_type = intr;

    err_gpio_drv = gpio_config(&config);
    if (ESP_OK != err_gpio_drv)
    {
        return false;
    }  

    return true;
}

bool gpio_handle_pin_output(uint8_t pin, bool level)
{
    err_gpio_drv = gpio_set_level(pin, level);
    if (ESP_OK != err_gpio_drv)
    {
        return false;
    }
    
    return true;
}

/*------------------------------Private functions------------------------------*/