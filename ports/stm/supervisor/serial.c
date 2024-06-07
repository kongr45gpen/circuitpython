// This file is part of the CircuitPython project: https://circuitpython.org
//
// SPDX-FileCopyrightText: Copyright (c) 2017, 2018 Scott Shawcroft for Adafruit Industries
// SPDX-FileCopyrightText: Copyright (c) 2019 Lucian Copeland for Adafruit Industries
//
// SPDX-License-Identifier: MIT

#include "py/mphal.h"
#include <string.h>
#include "supervisor/shared/serial.h"

// I'm not sure how this was supposed to have worked?
#define CPY_STM32H7 1

#if CPY_STM32F4
#include "stm32f4xx_hal.h"
#include "stm32f4/gpio.h"
// TODO: Switch this to using DEBUG_UART.

UART_HandleTypeDef huart;
#elif CPY_STM32H7
#include "stm32h7xx_hal.h"
// #include "stm32h7/gpio.h"
// TODO: Switch this to using DEBUG_UART.

UART_HandleTypeDef huart;
#endif

void port_serial_init(void) {
    #if CPY_STM32F4
    huart.Instance = USART2;
    huart.Init.BaudRate = 115200;
    huart.Init.WordLength = UART_WORDLENGTH_8B;
    huart.Init.StopBits = UART_STOPBITS_1;
    huart.Init.Parity = UART_PARITY_NONE;
    huart.Init.Mode = UART_MODE_TX_RX;
    huart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart.Init.OverSampling = UART_OVERSAMPLING_16;
    if (HAL_UART_Init(&huart) == HAL_OK) {
        stm32f4_peripherals_status_led(1, 1);
    }
    #elif CPY_STM32H7
    huart.Instance = USART3;
    huart.Init.BaudRate = 115200;
    huart.Init.WordLength = UART_WORDLENGTH_8B;
    huart.Init.StopBits = UART_STOPBITS_1;
    huart.Init.Parity = UART_PARITY_NONE;
    huart.Init.Mode = UART_MODE_TX_RX;
    huart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart.Init.OverSampling = UART_OVERSAMPLING_16;
    huart.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
    huart.Init.ClockPrescaler = UART_PRESCALER_DIV1;
    huart.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
    // HAL_UART_Init(&huart);
    // HAL_UARTEx_SetTxFifoThreshold(&huart, UART_TXFIFO_THRESHOLD_1_8);
    // HAL_UARTEx_SetRxFifoThreshold(&huart, UART_RXFIFO_THRESHOLD_1_8);
    // HAL_UARTEx_DisableFifoMode(&huart);
    #else
    #error "Check your UART!!!"
    #endif
}

bool port_serial_connected(void) {
    return true;
}

char port_serial_read(void) {
    #if CPY_STM32F4 || CPY_STM32H7
    uint8_t data;
    HAL_UART_Receive(&huart, &data, 1, 500);
    return data;
    #else
    return -1;
    #endif
}

// There is no easy way to find the number of pending characters, so just say there's 1.
// TODO: Use FIFO on STM32H7?
uint32_t port_serial_bytes_available(void) {
    #if (CPY_STM32F4) || (CPY_STM32H7)
    return __HAL_UART_GET_FLAG(&huart, UART_FLAG_RXNE) ? 1 : 0;
    #else
    #error "Check your UART"
    return 0;
    #endif
}

void port_serial_write_substring(const char *text, uint32_t len) {
    #if (CPY_STM32F4) || (CPY_STM32H7)
    HAL_UART_Transmit(&huart, (uint8_t *)text, len, 5000);
    #endif
}
