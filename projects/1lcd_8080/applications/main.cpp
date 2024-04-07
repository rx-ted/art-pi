/***
 * @Author: rx-ted 1552488649@qq.com
 * @Date: 2024-03-03 18:20:39
 * @LastEditors: rx-ted 1552488649@qq.com
 * @LastEditTime: 2024-03-07 23:30:05
 * @Description: LCD DEMO
 * @Copyright (c) 2024 by rx-ted, All Rights Reserved.
 */

#include "sys.h"
#include "rtdevice.h"
#include <rtthread.h>
#include <rthw.h>
#include "drv_common.h"
#include "tft.h"
// #include <lcd.h>
#include "WString_test.h"
#include <tft_test.h>
// #include "pins.h"

int main(void)
{

    test_tft();
}

void lcd_demo1()
{
    char *name = (char *)"ili9341";
    tft_8_parallel_t p8 = {
        D0, D1, D2, D3, D4, D5, D6, D7};
    tft_mcu_t mcu = {
        name, 240, 320, A0, A1, A2, A3, A4, p8};
    TFT tft = TFT(mcu);
    tft.begin();
    tft.fillScreen(RED);
    tft.fillScreen(GREEN);
    tft.fillScreen(BLUE);
    tft.fillScreen(YELLOW);
    delay(100);
    tft.fillScreen(WHITE);
    tft.setRotation(0);
    tft.fillScreen(PURPLE);
    delay(300);
    rt_kprintf("Using TFT, id is %x\n", tft.getDriverId());
    tft.destory();
}
MSH_CMD_EXPORT(lcd_demo1, "ili9341 tft demo");

void lcd_demo2()
{
    char *name = (char *)"r61581";
    tft_8_parallel_t p8 = {
        D0, D1, D2, D3, D4, D5, D6, D7};
    tft_mcu_t mcu = {
        name, 240, 320, A0, A1, A2, A3, A4, p8};
    TFT tft = TFT(mcu);
    tft.begin();
    tft.fillScreen(RED);
    tft.fillScreen(GREEN);
    tft.fillScreen(BLUE);
    tft.fillScreen(YELLOW);
    delay(100);
    tft.fillScreen(WHITE);
    tft.setRotation(0);
    tft.fillScreen(PURPLE);
    delay(300);
    rt_kprintf("Using TFT, id is %x\n", tft.getDriverId());
    tft.destory();
}
MSH_CMD_EXPORT(lcd_demo2, "r61581 tft demo");

#include "stm32h7xx.h"
#include <stm32h750xx.h>
static int vtor_config(void)
{
    /* Vector Table Relocation in Internal QSPI_FLASH */
    SCB->VTOR = QSPI_BASE;
    return 0;
}
INIT_BOARD_EXPORT(vtor_config);
