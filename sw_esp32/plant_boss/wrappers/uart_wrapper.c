/**
*  \file    uart_wrapper.c
*  \brief   This file wraps around esp32 uart driver.
*  \author  arvtom
*/

/*------------------------------Includes------------------------------*/
#include "uart_wrapper.h"

/*------------------------------Defines------------------------------*/

/*------------------------------Variables / Macro calls------------------------------*/

/*------------------------------Public functions------------------------------*/
// bool uart_init(void)
// {
//     uart_config_t uart_config = {
//         .baud_rate = 115200,
//         .data_bits = UART_DATA_8_BITS,
//         .parity = UART_PARITY_DISABLE,
//         .stop_bits = UART_STOP_BITS_1,
//         .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
//         .rx_flow_ctrl_thresh = 122,
//     };
//     // Configure UART parameters
//     ESP_ERROR_CHECK(uart_param_config(UART_NUM_0, &uart_config));

//     // Set UART pins(TX: IO4, RX: IO5, RTS: IO18, CTS: IO19)
//     // ESP_ERROR_CHECK(uart_set_pin(UART_NUM_2, 4, 5, 18, 19));

//     // Setup UART buffered IO with event queue
//     const int uart_buffer_size = (1024 * 2);
//     QueueHandle_t uart_queue;
//     // Install UART driver using an event queue here
//     ESP_ERROR_CHECK(uart_driver_install(UART_NUM_0, uart_buffer_size, uart_buffer_size, 10, &uart_queue, 0));
    
//     return true;
// }

// bool uart_handle(void)
// {
//     // Write data to UART.
//     char* test_str = "This is a test string.\n";
//     uart_write_bytes(UART_NUM_0, (const char*)test_str, strlen(test_str));

//     // Wait for packet to be sent
//     // ESP_ERROR_CHECK(uart_wait_tx_done(UART_NUM_2, 100)); // wait timeout is 100 RTOS ticks (TickType_t)

//     return true;
// }

/*------------------------------Private functions------------------------------*/