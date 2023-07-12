/**
*  \file    bh1750fvi.c
*  \brief   This file contains functions for reading light sensor bh1750fvi data.
*  \author  arvtom
*/

/*------------------------------Includes------------------------------*/
#include "bh1750fvi.h"

/*------------------------------Defines------------------------------*/

/*------------------------------Variables / Macro calls------------------------------*/
float light;

/*------------------------------Public functions------------------------------*/
bool bh1750fvi_init(void)
{
    if (true != i2c_init())
    {
        return false;
    }
    
    return true;
}

bool bh1750fvi_handle(void)
{
    /* Low resolution mode. Needs 24 ms to finish sampling. */
    uint8_t buf_tx[2];
    buf_tx[0] = BH1750FVI_I2C_COMMAND_MEASURE;

    if (true != i2c_handle_write(BH1750FVI_I2C_ADDR_MEASURE, (uint8_t *)buf_tx, 1, BH1750FVI_I2C_TIMEOUT))
    {
        return false;
    }

    /* wait 30ms */
    vTaskDelay(3);

    uint8_t buf_rx[2];

    if (true != i2c_handle_read(BH1750FVI_I2C_ADDR_RESULT, (uint8_t *)buf_rx, 2, BH1750FVI_I2C_TIMEOUT))
    {
        return false;
    }

    light = (float)(((uint16_t)buf_rx[0] << 8) | (uint16_t)buf_rx[1]) / 1.2;
    printf("light %f\n", light);

    return true;
}

/*------------------------------Private functions------------------------------*/