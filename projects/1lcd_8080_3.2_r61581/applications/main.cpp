/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-03-17     rx-ted        example
 * 2020-09-02     RT-Thread    first version
 */
#include "font_fixedsys_mono_16.h"
#include <rtthread.h>
#include <rtdevice.h>
#include "drv_common.h"
#include <string>
// #include <Arduino.h>
// #include "lcd.h"
#include "pins.h"
#include "drv_tft.h"

#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF

uint8_t LCD_RESET = A4; // Can alternately just connect to Arduino's reset pin
uint8_t LCD_CS = A3;    // Chip Select goes to Analog 3
uint8_t LCD_CD = A2;    // Command/Data goes to Analog 2
uint8_t LCD_WR = A1;    // LCD Write goes to Analog 1
uint8_t LCD_RD = A0;    // LCD Read goes to Analog 0

rt_base_t d8[8] = {D0, D1, D2, D3, D4, D5, D6, D7};
// TFTLCD tft = TFTLCD(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET, 240, 320, d8);

int main(void)
{
    rt_kprintf("Hello~");
    struct rt_tft_mcu_t *mcu;
    // mcu->rd = LCD_RD;
    // mcu->wr = LCD_WR;
    // mcu->cs = LCD_CS;
    // mcu->dc = LCD_CD;
    // mcu->rst = LCD_RESET;
    // for (uint8_t i = 0; i < 8; i++)
    // {
    //     mcu->d8[i] = d8[i];
    // }
    drv_tft lcd = drv_tft(mcu);

    return RT_EOK;
}

#include "stm32h7xx.h"
static int vtor_config(void)
{
    /* Vector Table Relocation in Internal QSPI_FLASH */
    SCB->VTOR = QSPI_BASE;
    return 0;
}
INIT_BOARD_EXPORT(vtor_config);
