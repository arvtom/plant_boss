/**
*  \file    bh1750fvi.c
*  \brief   This file contains functions for reading light sensor bh1750fvi data.
*  \author  arvtom
*/

/*------------------------------Includes------------------------------*/
#include "bh1750fvi.h"

/*------------------------------Defines------------------------------*/

/*------------------------------Variables / Macro calls------------------------------*/

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
    if (true != i2c_handle())
    {
        return false;
    }

    return true;
}

/*------------------------------Private functions------------------------------*/