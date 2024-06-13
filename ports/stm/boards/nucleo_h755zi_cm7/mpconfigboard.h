// This file is part of the CircuitPython project: https://circuitpython.org
//
// SPDX-FileCopyrightText: Copyright (c) 2024 Lucian Copeland for Adafruit Industries
//
// SPDX-License-Identifier: MIT

#pragma once

// Micropython setup

#define MICROPY_HW_BOARD_NAME       "NUCLEO STM32H755 (CM7)"
#define MICROPY_HW_MCU_NAME         "STM32H755"

#define FLASH_PAGE_SIZE             (0x4000)

// H7 MPU definitions
#define CPY_FLASH_REGION_SIZE   ARM_MPU_REGION_SIZE_1MB   // Using one bank, and leaving the other for the second core
#define CPY_ITCM_REGION_SIZE    ARM_MPU_REGION_SIZE_64KB
#define CPY_DTCM_REGION_SIZE    ARM_MPU_REGION_SIZE_128KB
#define CPY_SRAM_REGION_SIZE    ARM_MPU_REGION_SIZE_512KB
#define CPY_SRAM_SUBMASK        0x00
#define CPY_SRAM_START_ADDR     0x24000000

#define HSE_VALUE                   ((uint32_t)8000000)
#define LSE_VALUE                   ((uint32_t)32768)
#define BOARD_HSE_SOURCE            (RCC_HSE_BYPASS) // ST boards use the STLink clock signal
#define BOARD_HAS_LOW_SPEED_CRYSTAL (1)
#define BOARD_POWER_SUPPLY          (PWR_DIRECT_SMPS_SUPPLY) // Nucleo-H755ZI-Q uses an SMPS by default
#define CPY_CLK_VSCALE              (PWR_REGULATOR_VOLTAGE_SCALE2)
#define CPY_CLK_PLLN                (240) // Running at 240 MHz (instead of maximum 480 MHz) due to power supply

#define CIRCUITPY_CONSOLE_UART_RX (&pin_PD09)
#define CIRCUITPY_CONSOLE_UART_TX (&pin_PD08)
