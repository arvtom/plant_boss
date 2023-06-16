
#include <stdint.h>
#include <driver/gpio.h>
#include <esp_adc/adc_oneshot.h>
#include <driver/i2c.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

uint8_t counter = 0;
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
uint8_t buf_i2c_rx[2];

void app_main(void)
{
    printf("hello\n");
    // esp_err_t adc_oneshot_new_unit(const adc_oneshot_unit_init_cfg_t *init_config, adc_oneshot_unit_handle_t *ret_unit);
    // esp_err_t adc_oneshot_config_channel(adc_oneshot_unit_handle_t handle, adc_channel_t channel, const adc_oneshot_chan_cfg_t *config);
    // esp_err_t adc_oneshot_read(adc_oneshot_unit_handle_t handle, adc_channel_t chan, int *out_raw);

    // esp_err_t gpio_config(const gpio_config_t *pGPIOConfig);
    // esp_err_t gpio_set_level(gpio_num_t gpio_num, uint32_t level);

    gpio_config_t io_conf_27 = {};
    io_conf_27.intr_type = GPIO_INTR_DISABLE;
    io_conf_27.mode = GPIO_MODE_OUTPUT;
    io_conf_27.pin_bit_mask = (1ULL<<27u);
    io_conf_27.pull_down_en = 0;
    io_conf_27.pull_up_en = 0;
    err_esp = gpio_config(&io_conf_27);
    printf("err_esp %d\n", (int)err_esp);

    gpio_config_t io_conf_4 = {};
    io_conf_4.intr_type = GPIO_INTR_DISABLE;
    io_conf_4.mode = GPIO_MODE_OUTPUT;
    io_conf_4.pin_bit_mask = (1ULL<<4u);
    io_conf_4.pull_down_en = 0;
    io_conf_4.pull_up_en = 0;
    err_esp = gpio_config(&io_conf_4);
    printf("err_esp %d\n", (int)err_esp);

    gpio_config_t io_conf_17 = {};
    io_conf_17.intr_type = GPIO_INTR_DISABLE;
    io_conf_17.mode = GPIO_MODE_OUTPUT;
    io_conf_17.pin_bit_mask = (1ULL<<17u);
    io_conf_17.pull_down_en = 0;
    io_conf_17.pull_up_en = 0;
    err_esp = gpio_config(&io_conf_17);
    printf("err_esp %d\n", (int)err_esp);

    err_esp = gpio_set_level(4u, 1);
    printf("err_esp %d\n", (int)err_esp);
    
    err_esp = gpio_set_level(17u, 0);
    printf("err_esp %d\n", (int)err_esp);

    vTaskDelay(2);

    err_esp = gpio_set_level(17u, 1);
    printf("err_esp %d\n", (int)err_esp);

    vTaskDelay(2);

    // /* Read light sensor */
    err_esp = i2c_param_config(i2c_master_port, &conf);
    printf("err_esp %d\n", (int)err_esp);

    err_esp = i2c_driver_install(i2c_master_port, I2C_MODE_MASTER, 0, 0, 0);
    printf("err_esp %d\n", (int)err_esp);

    err_esp = i2c_master_read_from_device(i2c_master_port, 0b0100011, (uint8_t *)buf_i2c_rx, 2, 100);
    printf("err_esp %d\n", (int)err_esp);
    printf("buf %d%d\n", buf_i2c_rx[0], buf_i2c_rx[1]);

    while(1)
    {
        printf("%d, %d, %d\n", counter, buf_i2c_rx[0], buf_i2c_rx[1]);
        counter++;

        err_esp = gpio_set_level(27u, counter % 2);
        printf("err_esp %d\n", (int)err_esp);

        vTaskDelay(100);
        // vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}