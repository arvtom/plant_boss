/**
*  \file    error.c
*  \brief   Error management functions, which use individual bits to represent errors.
*  \author  arvtom
*/

/*------------------------------Includes------------------------------*/
#include "error.h"

/*------------------------------Defines------------------------------*/
static const char* tag_err = "err";

/*------------------------------Variables / Macro calls------------------------------*/

/*------------------------------Public functions------------------------------*/
/**
* \brief Set requested error bit in error variable
*/
void error_set_u32(uint32_t *p_err_var, uint32_t err_bit)
{
    *p_err_var |= err_bit;

    ESP_LOGI(tag_err, "err 0x%x, addr 0x%x\n", (unsigned int)*p_err_var, (unsigned int)p_err_var);
}

/**
* \brief Clear requested error bit in error variable
*/
void error_clear_u32(uint32_t *p_err_var, uint32_t err_bit)
{
    *p_err_var &= (~ err_bit);
}

/**
* \brief Check if requested error bit is set in error variable
*/
// bool error_check_u32(uint32_t *p_err_var, uint32_t err_bit)
// {
//     if (0U == (*p_err_var & err_bit))
//     {
//         return false;
//     }
//     else
//     {
//         return true;
//     }
// }

/**
* \brief Set requested error bit in error variable
*/
void error_set_u64(uint64_t *p_err_var, uint64_t err_bit)
{
    *p_err_var |= err_bit;

    ESP_LOGI(tag_err, "err 0x%llx, addr 0x%x\n", *p_err_var, (unsigned int)p_err_var);
}

/**
* \brief Clear requested error bit in error variable
*/
void error_clear_u64(uint64_t *p_err_var, uint64_t err_bit)
{
    *p_err_var &= (~ err_bit);
}

void error_handle()
{
    ESP_LOGI(tag_err, "err handle");

    vTaskDelay(100);
}

/*------------------------------Private functions------------------------------*/