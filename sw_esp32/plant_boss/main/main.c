
#include <stdint.h>
#include <math.h>
#include <driver/gpio.h>
#include <esp_adc/adc_oneshot.h>
#include <driver/i2c.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#define ADC_REFERENCE_VOLTAGE   1.1
#define ADC_12BIT_MAX_VALUE     4095

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

uint8_t buf_i2c_rx[2] = {0, 0};
uint8_t buf_i2c_tx[2] = {0, 0};

int adc_raw_temperature = 0;
int adc_raw_humidity = 0;
int adc_raw_battery = 0;

float adc_voltage_temperature = 0; /* mV */
float temperature = 0;

float light = 0;

void app_main(void)
{
    printf("hello\n");
    // esp_err_t adc_oneshot_new_unit(const adc_oneshot_unit_init_cfg_t *init_config, adc_oneshot_unit_handle_t *ret_unit);
    // esp_err_t adc_oneshot_config_channel(adc_oneshot_unit_handle_t handle, adc_channel_t channel, const adc_oneshot_chan_cfg_t *config);
    // esp_err_t adc_oneshot_read(adc_oneshot_unit_handle_t handle, adc_channel_t chan, int *out_raw);

    adc_oneshot_unit_handle_t adc1_handle;
    adc_oneshot_unit_init_cfg_t init_config1 = {
        .unit_id = ADC_UNIT_1,
        .ulp_mode = ADC_ULP_MODE_DISABLE,
    };

    err_esp = adc_oneshot_new_unit(&init_config1, &adc1_handle);
    printf("err_esp %d\n", (int)err_esp);

    adc_oneshot_chan_cfg_t config_ch3 = {
        .bitwidth = ADC_BITWIDTH_12,
        .atten = ADC_ATTEN_DB_6,
    };

    adc_oneshot_chan_cfg_t config_ch6 = {
        .bitwidth = ADC_BITWIDTH_12,
        .atten = ADC_ATTEN_DB_11,
    };

    adc_oneshot_chan_cfg_t config_ch7 = {
        .bitwidth = ADC_BITWIDTH_12,
        .atten = ADC_ATTEN_DB_11,
    };

    /* temperature */
    err_esp = adc_oneshot_config_channel(adc1_handle, ADC_CHANNEL_3, &config_ch3);
    printf("err_esp %d\n", (int)err_esp);

    /* humidity */
    err_esp = adc_oneshot_config_channel(adc1_handle, ADC_CHANNEL_6, &config_ch6);
    printf("err_esp %d\n", (int)err_esp);

    /* battery */
    err_esp = adc_oneshot_config_channel(adc1_handle, ADC_CHANNEL_7, &config_ch7);
    printf("err_esp %d\n", (int)err_esp);

    /* external led pin */
    gpio_config_t io_conf_27 = {};
    io_conf_27.intr_type = GPIO_INTR_DISABLE;
    io_conf_27.mode = GPIO_MODE_OUTPUT;
    io_conf_27.pin_bit_mask = (1ULL<<27u);
    io_conf_27.pull_down_en = 0;
    io_conf_27.pull_up_en = 0;
    err_esp = gpio_config(&io_conf_27);
    printf("err_esp %d\n", (int)err_esp);

    /* light sensor power supply pin */
    gpio_config_t io_conf_4 = {};
    io_conf_4.intr_type = GPIO_INTR_DISABLE;
    io_conf_4.mode = GPIO_MODE_OUTPUT;
    io_conf_4.pin_bit_mask = (1ULL<<4u);
    io_conf_4.pull_down_en = 0;
    io_conf_4.pull_up_en = 0;
    err_esp = gpio_config(&io_conf_4);
    printf("err_esp %d\n", (int)err_esp);

    /* light sensor reset pin */
    gpio_config_t io_conf_17 = {};
    io_conf_17.intr_type = GPIO_INTR_DISABLE;
    io_conf_17.mode = GPIO_MODE_OUTPUT;
    io_conf_17.pin_bit_mask = (1ULL<<17u);
    io_conf_17.pull_down_en = 0;
    io_conf_17.pull_up_en = 0;
    err_esp = gpio_config(&io_conf_17);
    printf("err_esp %d\n", (int)err_esp);

    /* temperature sensor power supply pin */
    gpio_config_t io_conf_32 = {};
    io_conf_32.intr_type = GPIO_INTR_DISABLE;
    io_conf_32.mode = GPIO_MODE_OUTPUT;
    io_conf_32.pin_bit_mask = (1ULL<<32u);
    io_conf_32.pull_down_en = 0;
    io_conf_32.pull_up_en = 0;
    err_esp = gpio_config(&io_conf_32);
    printf("err_esp %d\n", (int)err_esp);

    /* humidity sensor power supply pin */
    gpio_config_t io_conf_33 = {};
    io_conf_33.intr_type = GPIO_INTR_DISABLE;
    io_conf_33.mode = GPIO_MODE_OUTPUT;
    io_conf_33.pin_bit_mask = (1ULL<<33u);
    io_conf_33.pull_down_en = 0;
    io_conf_33.pull_up_en = 0;
    err_esp = gpio_config(&io_conf_33);
    printf("err_esp %d\n", (int)err_esp);

    err_esp = gpio_set_level(32u, 1);
    printf("err_esp %d\n", (int)err_esp); 

    err_esp = gpio_set_level(33u, 1);
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

    while(1)
    {
        // printf("%d, %d, %d\n", counter, buf_i2c_rx[0], buf_i2c_rx[1]);
        counter++;

        err_esp = gpio_set_level(27u, counter % 2);

        /* Low resolution mode. Needs 24 ms to finish sampling. */
        buf_i2c_tx[0] = 0b00100011;
        err_esp = i2c_master_write_to_device(i2c_master_port, 0b0100011, (uint8_t *)buf_i2c_tx, 1, 100);
        printf("err_esp %d\n", (int)err_esp);

        vTaskDelay(3);

        err_esp = i2c_master_read_from_device(i2c_master_port, 0b0100011, (uint8_t *)buf_i2c_rx, 2, 100);
        printf("err_esp %d\n", (int)err_esp);

        light = (float)(((uint16_t)buf_i2c_rx[0] << 8) | (uint16_t)buf_i2c_rx[1]) / 1.2;
        printf("light %f\n", light);

        /* temperature */
        err_esp = adc_oneshot_read(adc1_handle, ADC_CHANNEL_3, &adc_raw_temperature);
        printf("err_esp %d\n", (int)err_esp);


        /* Input voltage was attenuated, so multiply by 2. */
        adc_voltage_temperature = (float)adc_raw_temperature * 2 / (float)ADC_12BIT_MAX_VALUE * ADC_REFERENCE_VOLTAGE;

        temperature = -1481.96 + 
            sqrt(2.1962 * pow(10, 6) + ((1.8639 - adc_voltage_temperature) / (3.88 * pow(10, -6))));

        printf("adc_raw_temperature %d, adc_voltage_temperature %f, temperature %f\n", adc_raw_temperature, adc_voltage_temperature, temperature);

        /* humidity */
        err_esp = adc_oneshot_read(adc1_handle, ADC_CHANNEL_6, &adc_raw_humidity);
        printf("err_esp %d\n", (int)err_esp);
        printf("adc_raw_humidity %d\n", adc_raw_humidity);

        /* battery */
        err_esp = adc_oneshot_read(adc1_handle, ADC_CHANNEL_7, &adc_raw_battery);
        printf("err_esp %d\n", (int)err_esp);
        printf("adc_raw_battery %d\n", adc_raw_battery);

        vTaskDelay(100);
        // vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}