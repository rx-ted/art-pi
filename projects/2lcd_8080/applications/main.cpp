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
#include "tft1.h"
// #include <lcd.h>
#include "WString_test.h"
// #include "pins.h"

int main(int argc, char const *argv[])
{
    TFT1 tft = TFT1();
    rt_kprintf("get current pin status: %02x\n", tft.getCurrentPinStatus());
    rt_kprintf("get Driver Id: %04x\n", tft.getDriverId());
    rt_kprintf("get current pin status: %02x\n", tft.getCurrentPinStatus());
    tft.fillScreen(RED);
    tft.fillScreen(BLUE);
    tft.fillScreen(GREEN);
    tft.fillScreen(GRAY);

    return 0;
}

#include "stm32h7xx.h"
#include <stm32h750xx.h>
static int vtor_config(void)
{
    /* Vector Table Relocation in Internal QSPI_FLASH */
    SCB->VTOR = QSPI_BASE;
    return 0;
}
INIT_BOARD_EXPORT(vtor_config);
