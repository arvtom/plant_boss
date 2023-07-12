
/* ---------------------------- Includes ---------------------------- */
#include "thread_input.h"

/* ---------------------------- Typedefs ---------------------------- */

/* ---------------------------- Global variables ---------------------------- */
esp_err_t err_esp = 0;

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

uint8_t buf_i2c_rx[2] = {0, 0};
uint8_t buf_i2c_tx[2] = {0, 0};

float light = 0;

thread_input_t s_thread_input;

/* ---------------------------- Public functions ---------------------------- */
void thread_input(void *arg)
{
    // thread_app();
    if (true != thread_input_init())
    {
        error_handle();
    }

    while (1)
    {
        if (true != thread_input_handle())
        {
            error_handle();
        }
    }
}

bool thread_input_init(void)
{
    if (true != adc_init())
    {
        printf("error\n");
        return false;
    }

    if (true != gpio_init())
    {
        printf("error\n");
        return false;
    }

    // /* Read light sensor */
    err_esp = i2c_param_config(i2c_master_port, &conf);
    if (ESP_OK != err_esp)
    {
        error_set_u32(&s_thread_input.err, THREAD_INPUT_ERROR_INIT_I2C);

        return false;
    }   

    err_esp = i2c_driver_install(i2c_master_port, I2C_MODE_MASTER, 0, 0, 0);
    if (ESP_OK != err_esp)
    {
        error_set_u32(&s_thread_input.err, THREAD_INPUT_ERROR_INIT_I2C);

        return false;
    }   

    return true;
}

bool thread_input_handle(void)
{
    /* Low resolution mode. Needs 24 ms to finish sampling. */
    buf_i2c_tx[0] = 0b00100011;
    err_esp = i2c_master_write_to_device(i2c_master_port, 0b0100011, (uint8_t *)buf_i2c_tx, 1, 100);
    if (ESP_OK != err_esp)
    {
        error_set_u32(&s_thread_input.err, THREAD_INPUT_ERROR_HANDLE_I2C);

        return false;
    }   

    vTaskDelay(3);

    err_esp = i2c_master_read_from_device(i2c_master_port, 0b0100011, (uint8_t *)buf_i2c_rx, 2, 100);
    if (ESP_OK != err_esp)
    {
        error_set_u32(&s_thread_input.err, THREAD_INPUT_ERROR_HANDLE_I2C);

        return false;
    }

    light = (float)(((uint16_t)buf_i2c_rx[0] << 8) | (uint16_t)buf_i2c_rx[1]) / 1.2;
    printf("light %f\n", light);

    if (true != adc_handle())
    {
        return false;
    }

    printf("\n");
    
    vTaskDelay(100);

    return true;
}

/* ---------------------------- Private functions ---------------------------- */

/* ---------------------------- Interrupt callbacks ---------------------------- */

