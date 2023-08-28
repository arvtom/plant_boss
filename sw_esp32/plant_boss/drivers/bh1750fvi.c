/**
*  \file    bh1750fvi.c
*  \brief   This file contains functions for reading light sensor bh1750fvi data.
*  \author  arvtom
*/

/*------------------------------Includes------------------------------*/
#include "bh1750fvi.h"

/*------------------------------Defines------------------------------*/

/*------------------------------Variables / Macro calls------------------------------*/
uint32_t err_bh1750fvi = 0u;
float light = 0.0;

// static const char* tag_bh1750fvi = "bh1750fvi";

/*------------------------------Public functions------------------------------*/
bool bh1750fvi_init(void)
{
    // printf("addr err_bh1750fvi 0x%x\n", (unsigned int)&err_bh1750fvi);

    if (true != i2c_init())
    {
        error_set_u32(&err_bh1750fvi, BH1750FVI_ERROR_INIT);

        return false;
    }
    
    return true;
}

bool bh1750fvi_handle(void)
{
    /* Low resolution mode. Needs 24 ms to finish sampling. */
    uint8_t buf_tx[1];
    buf_tx[0] = BH1750FVI_I2C_COMMAND_MEASURE;

    if (true != i2c_handle_write(BH1750FVI_I2C_ADDR_MEASURE, (uint8_t *)buf_tx, 1, BH1750FVI_I2C_TIMEOUT))
    {
        error_set_u32(&err_bh1750fvi, BH1750FVI_ERROR_HANDLE);
        
        return false;
    }

    /* wait 30ms */
    vTaskDelay(3);

    uint8_t buf_rx[2];

    if (true != i2c_handle_read(BH1750FVI_I2C_ADDR_RESULT, (uint8_t *)buf_rx, 2, BH1750FVI_I2C_TIMEOUT))
    {
        error_set_u32(&err_bh1750fvi, BH1750FVI_ERROR_HANDLE);

        return false;
    }

    light = (float)(((uint16_t)buf_rx[0] << 8) | (uint16_t)buf_rx[1]) / 1.2;

    return true;
}

float bh1750fvi_get_light_value(void)
{
    return light;
}

/*------------------------------Private functions------------------------------*/