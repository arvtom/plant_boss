/**
*  \file    i2c_wrapper.c
*  \brief   This file wraps around esp32 i2c driver.
*  \author  arvtom
*/

/*------------------------------Includes------------------------------*/
#include "i2c_wrapper.h"

/*------------------------------Defines------------------------------*/

/*------------------------------Variables / Macro calls------------------------------*/
int err_i2c_drv = 0;
i2c_port_t i2c_master_port = 0;
i2c_config_t conf = {
    .mode = I2C_MODE_MASTER,
    .sda_io_num = 21,         // select SDA GPIO specific to your project
    .sda_pullup_en = GPIO_PULLUP_ENABLE,
    .scl_io_num = 22,         // select SCL GPIO specific to your project
    .scl_pullup_en = GPIO_PULLUP_ENABLE,
    .master.clk_speed = 10000,  // select frequency specific to your project
    .clk_flags = 0,                          // optional; you can use I2C_SCLK_SRC_FLAG_* flags to choose i2c source clock here
};

/*------------------------------Public functions------------------------------*/
bool i2c_init(void)
{
    // /* Read light sensor */
    err_i2c_drv = i2c_param_config(i2c_master_port, &conf);
    if (ESP_OK != err_i2c_drv)
    {

        return false;
    }   

    err_i2c_drv = i2c_driver_install(i2c_master_port, I2C_MODE_MASTER, 0, 0, 0);
    if (ESP_OK != err_i2c_drv)
    {

        return false;
    }   
    
    return true;
}

bool i2c_handle(void)
{

    return true;
}

bool i2c_handle_write(uint8_t addr, uint8_t* p_buf, uint8_t count, uint8_t timeout)
{
    err_i2c_drv = i2c_master_write_to_device(i2c_master_port, addr, p_buf, count, timeout);
    if (ESP_OK != err_i2c_drv)
    {
        printf("error i2c write %d\n", err_i2c_drv);
        return false;
    }   

    return true;
}

bool i2c_handle_read(uint8_t addr, uint8_t* p_buf, uint8_t count, uint8_t timeout)
{
    err_i2c_drv = i2c_master_read_from_device(i2c_master_port, addr, p_buf, count, timeout);
    if (ESP_OK != err_i2c_drv)
    {
        printf("error i2c read\n");
        return false;
    }

    return true;
}

/*------------------------------Private functions------------------------------*/