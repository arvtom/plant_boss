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
bool gpio_init(void)
{
    /* light sensor power supply pin */
    gpio_config_t io_conf_4 = {};
    io_conf_4.intr_type = GPIO_INTR_DISABLE;
    io_conf_4.mode = GPIO_MODE_OUTPUT;
    io_conf_4.pin_bit_mask = (1ULL<<4u);
    io_conf_4.pull_down_en = 0;
    io_conf_4.pull_up_en = 0;

    /* light sensor reset pin */
    gpio_config_t io_conf_17 = {};
    io_conf_17.intr_type = GPIO_INTR_DISABLE;
    io_conf_17.mode = GPIO_MODE_OUTPUT;
    io_conf_17.pin_bit_mask = (1ULL<<17u);
    io_conf_17.pull_down_en = 0;
    io_conf_17.pull_up_en = 0;

    /* temperature sensor power supply pin */
    gpio_config_t io_conf_32 = {};
    io_conf_32.intr_type = GPIO_INTR_DISABLE;
    io_conf_32.mode = GPIO_MODE_OUTPUT;
    io_conf_32.pin_bit_mask = (1ULL<<32u);
    io_conf_32.pull_down_en = 0;
    io_conf_32.pull_up_en = 0;

    /* humidity sensor power supply pin */
    gpio_config_t io_conf_33 = {};
    io_conf_33.intr_type = GPIO_INTR_DISABLE;
    io_conf_33.mode = GPIO_MODE_OUTPUT;
    io_conf_33.pin_bit_mask = (1ULL<<33u);
    io_conf_33.pull_down_en = 0;
    io_conf_33.pull_up_en = 0;

    /* light sensor power supply pin */
    err_gpio_drv = gpio_config(&io_conf_4);
    if (ESP_OK != err_gpio_drv)
    {
        return false;
    }   

    /* light sensor reset pin */
    err_gpio_drv = gpio_config(&io_conf_17);
    if (ESP_OK != err_gpio_drv)
    {
        return false;
    }   

    /* temperature sensor power supply pin */
    err_gpio_drv = gpio_config(&io_conf_32);
    if (ESP_OK != err_gpio_drv)
    {
        return false;
    }   

    /* humidity sensor power supply pin */
    err_gpio_drv = gpio_config(&io_conf_33);
    if (ESP_OK != err_gpio_drv)
    {
        return false;
    }   

    err_gpio_drv = gpio_set_level(32u, 1);
    if (ESP_OK != err_gpio_drv)
    {
        return false;
    }   

    err_gpio_drv = gpio_set_level(33u, 1);
    if (ESP_OK != err_gpio_drv)
    {
        return false;
    }   

    err_gpio_drv = gpio_set_level(4u, 1);
    if (ESP_OK != err_gpio_drv)
    {
        return false;
    }   
    
    err_gpio_drv = gpio_set_level(17u, 0);
    if (ESP_OK != err_gpio_drv)
    {
        return false;
    }   

    vTaskDelay(2);

    err_gpio_drv = gpio_set_level(17u, 1);
    if (ESP_OK != err_gpio_drv)
    {
        return false;
    }   

    vTaskDelay(2);
    
    return true;
}

bool gpio_handle(void)
{

    return true;
}

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