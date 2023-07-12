
/* ---------------------------- Includes ---------------------------- */
#include "thread_input.h"

/* ---------------------------- Typedefs ---------------------------- */

/* ---------------------------- Global variables ---------------------------- */
esp_err_t err_esp = 0;

adc_oneshot_unit_handle_t adc1_handle;
adc_cali_handle_t adc_calibration_handle_ch3_s;
adc_cali_handle_t adc_calibration_handle_ch6_s;
adc_cali_handle_t adc_calibration_handle_ch7_s;

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

float adc_voltage_temperature_f = 0;
float temperature = 0;
int adc_voltage_temperature_s32 = 0;
int adc_voltage_humidity_s32 = 0;
int adc_voltage_battery_s32 = 0;

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
    adc_oneshot_unit_init_cfg_t init_config1 = 
    {
        .unit_id = ADC_UNIT_1,
        .ulp_mode = ADC_ULP_MODE_DISABLE,
    };

    adc_oneshot_chan_cfg_t config_ch3 = 
    {
        .bitwidth = ADC_BITWIDTH_12,
        .atten = ADC_ATTEN_DB_6,
    };

    adc_oneshot_chan_cfg_t config_ch6 = 
    {
        .bitwidth = ADC_BITWIDTH_12,
        .atten = ADC_ATTEN_DB_11,
    };

    adc_oneshot_chan_cfg_t config_ch7 = 
    {
        .bitwidth = ADC_BITWIDTH_12,
        .atten = ADC_ATTEN_DB_11,
    };

    /* Available calibration scheme is ADC_CALI_SCHEME_VER_LINE_FITTING.
        Characterization based on reference voltage stored in eFuse: ADC_CALI_LINE_FITTING_EFUSE_VAL_EFUSE_VREF. */
    adc_cali_line_fitting_config_t adc_calibration_config_ch3_s = 
    {
        .unit_id = ADC_UNIT_1,
        .atten = ADC_ATTEN_DB_6,
        .bitwidth = ADC_BITWIDTH_12,
    };

    adc_cali_line_fitting_config_t adc_calibration_config_ch6_s = 
    {
        .unit_id = ADC_UNIT_1,
        .atten = ADC_ATTEN_DB_11,
        .bitwidth = ADC_BITWIDTH_12,
    };

    adc_cali_line_fitting_config_t adc_calibration_config_ch7_s = 
    {
        .unit_id = ADC_UNIT_1,
        .atten = ADC_ATTEN_DB_11,
        .bitwidth = ADC_BITWIDTH_12,
    };

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

    err_esp = adc_oneshot_new_unit(&init_config1, &adc1_handle);
    if (ESP_OK != err_esp)
    {
        error_set_u32(&s_thread_input.err, THREAD_INPUT_ERROR_INIT_ADC_1);

        return false;
    }

    /* temperature */
    err_esp = adc_oneshot_config_channel(adc1_handle, ADC_CHANNEL_3, &config_ch3);
    if (ESP_OK != err_esp)
    {
        error_set_u32(&s_thread_input.err, THREAD_INPUT_ERROR_INIT_ADC_CHANNEL_TEMPERATURE);

        return false;
    }   

    /* humidity */
    err_esp = adc_oneshot_config_channel(adc1_handle, ADC_CHANNEL_6, &config_ch6);
    if (ESP_OK != err_esp)
    {
        error_set_u32(&s_thread_input.err, THREAD_INPUT_ERROR_INIT_ADC_CHANNEL_HUMIDITY);

        return false;
    }   

    /* battery */
    err_esp = adc_oneshot_config_channel(adc1_handle, ADC_CHANNEL_7, &config_ch7);
    if (ESP_OK != err_esp)
    {
        error_set_u32(&s_thread_input.err, THREAD_INPUT_ERROR_INIT_ADC_CHANNEL_BATTERY);

        return false;
    }   

    err_esp = adc_cali_create_scheme_line_fitting(&adc_calibration_config_ch3_s, &adc_calibration_handle_ch3_s);
    if (ESP_OK != err_esp)
    {
        error_set_u32(&s_thread_input.err, THREAD_INPUT_ERROR_INIT_ADC_CALIBRATION_TEMPERATURE);

        return false;
    }   

    err_esp = adc_cali_create_scheme_line_fitting(&adc_calibration_config_ch6_s, &adc_calibration_handle_ch6_s);
    if (ESP_OK != err_esp)
    {
        error_set_u32(&s_thread_input.err, THREAD_INPUT_ERROR_INIT_ADC_CALIBRATION_HUMIDITY);

        return false;
    }   

    err_esp = adc_cali_create_scheme_line_fitting(&adc_calibration_config_ch7_s, &adc_calibration_handle_ch7_s);
    if (ESP_OK != err_esp)
    {
        error_set_u32(&s_thread_input.err, THREAD_INPUT_ERROR_INIT_ADC_CALIBRATION_BATTERY);

        return false;
    }  

    /* light sensor power supply pin */
    err_esp = gpio_config(&io_conf_4);
    if (ESP_OK != err_esp)
    {
        error_set_u32(&s_thread_input.err, THREAD_INPUT_ERROR_INIT_GPIO_LIGHT_POWER);

        return false;
    }   

    /* light sensor reset pin */
    err_esp = gpio_config(&io_conf_17);
    if (ESP_OK != err_esp)
    {
        error_set_u32(&s_thread_input.err, THREAD_INPUT_ERROR_INIT_GPIO_LIGHT_RESET);

        return false;
    }   

    /* temperature sensor power supply pin */
    err_esp = gpio_config(&io_conf_32);
    if (ESP_OK != err_esp)
    {
        error_set_u32(&s_thread_input.err, THREAD_INPUT_ERROR_INIT_GPIO_TEMPERATURE_POWER);

        return false;
    }   

    /* humidity sensor power supply pin */
    err_esp = gpio_config(&io_conf_33);
    if (ESP_OK != err_esp)
    {
        error_set_u32(&s_thread_input.err, THREAD_INPUT_ERROR_INIT_GPIO_HUMIDITY_POWER);

        return false;
    }   



    err_esp = gpio_set_level(32u, 1);
    if (ESP_OK != err_esp)
    {
        error_set_u32(&s_thread_input.err, THREAD_INPUT_ERROR_HANDLE_GPIO_TEMPERATURE_POWER);

        return false;
    }   

    err_esp = gpio_set_level(33u, 1);
    if (ESP_OK != err_esp)
    {
        error_set_u32(&s_thread_input.err, THREAD_INPUT_ERROR_HANDLE_GPIO_HUMIDITY_POWER);

        return false;
    }   

    err_esp = gpio_set_level(4u, 1);
    if (ESP_OK != err_esp)
    {
        error_set_u32(&s_thread_input.err, THREAD_INPUT_ERROR_HANDLE_GPIO_LIGHT_POWER);

        return false;
    }   
    
    err_esp = gpio_set_level(17u, 0);
    if (ESP_OK != err_esp)
    {
        error_set_u32(&s_thread_input.err, THREAD_INPUT_ERROR_HANDLE_GPIO_LIGHT_RESET);

        return false;
    }   

    vTaskDelay(2);

    err_esp = gpio_set_level(17u, 1);
    if (ESP_OK != err_esp)
    {
        error_set_u32(&s_thread_input.err, THREAD_INPUT_ERROR_HANDLE_GPIO_LIGHT_RESET);

        return false;
    }   

    vTaskDelay(2);

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

    /* temperature */
    err_esp = adc_oneshot_read(adc1_handle, ADC_CHANNEL_3, &adc_raw_temperature);
    if (ESP_OK != err_esp)
    {
        error_set_u32(&s_thread_input.err, THREAD_INPUT_ERROR_HANDLE_ADC);

        return false;
    }

    /* Use manufacturer provided calibration */
    err_esp = adc_cali_raw_to_voltage(adc_calibration_handle_ch3_s, adc_raw_temperature, &adc_voltage_temperature_s32);
    if (ESP_OK != err_esp)
    {
        error_set_u32(&s_thread_input.err, THREAD_INPUT_ERROR_HANDLE_ADC);

        return false;
    }

    adc_voltage_temperature_f = (float)adc_voltage_temperature_s32 / 1000;

    temperature = -1481.96 + 
        sqrt(2.1962 * pow(10, 6) + ((1.8639 - adc_voltage_temperature_f) / (3.88 * pow(10, -6))));
    printf("temperature %f\n", temperature);

    /* humidity */
    err_esp = adc_oneshot_read(adc1_handle, ADC_CHANNEL_6, &adc_raw_humidity);
    if (ESP_OK != err_esp)
    {
        error_set_u32(&s_thread_input.err, THREAD_INPUT_ERROR_HANDLE_ADC);

        return false;
    }

    err_esp = adc_cali_raw_to_voltage(adc_calibration_handle_ch6_s, adc_raw_humidity, &adc_voltage_humidity_s32);
    if (ESP_OK != err_esp)
    {
        error_set_u32(&s_thread_input.err, THREAD_INPUT_ERROR_HANDLE_ADC);

        return false;
    }
    
    printf("adc_voltage_humidity_s32 %d\n", adc_voltage_humidity_s32);

    /* battery */
    err_esp = adc_oneshot_read(adc1_handle, ADC_CHANNEL_7, &adc_raw_battery);
    if (ESP_OK != err_esp)
    {
        error_set_u32(&s_thread_input.err, THREAD_INPUT_ERROR_HANDLE_ADC);

        return false;
    }

    err_esp = adc_cali_raw_to_voltage(adc_calibration_handle_ch7_s, adc_raw_battery, &adc_voltage_battery_s32);
    if (ESP_OK != err_esp)
    {
        error_set_u32(&s_thread_input.err, THREAD_INPUT_ERROR_HANDLE_ADC);

        return false;
    }
    
    printf("adc_voltage_battery_s32 %d\n", adc_voltage_battery_s32);
    
    vTaskDelay(100);

    return true;
}

/* ---------------------------- Private functions ---------------------------- */

/* ---------------------------- Interrupt callbacks ---------------------------- */

