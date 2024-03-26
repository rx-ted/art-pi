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

#include <rtthread.h>
#include <rtdevice.h>
#include "drv_common.h"

#include <string>

#define LED_PIN GET_PIN(I, 8)

int blink_demo(float second, int times)
{
    rt_pin_mode(LED_PIN, PIN_MODE_OUTPUT);
    rt_uint32_t count = 0;
    while (count < times)
    {
        rt_thread_mdelay(second * 1000);
        rt_pin_write(LED_PIN, PIN_HIGH);
        rt_thread_mdelay(second * 1000);
        rt_pin_write(LED_PIN, PIN_LOW);
        count++;
    }
    return RT_EOK;
}

void blink(int argc, char *argv[])
{
    if (argc > 2)
    {
        rt_kprintf("%s second and %s times to blink\n", argv[1], argv[2]);
        blink_demo(std::stof(argv[1]), std::stof(argv[2]));
    }
}

MSH_CMD_EXPORT(blink, "blink 1 10 => 1 second, loop to 10");

int main(void)
{
    rt_kprintf("blink demo usage:\n");
    rt_kprintf("e.g. blink 1 10  =>  the led blink swtich 1 second in 10 times.\n");
    blink_demo(1.0, 10);
    rt_kprintf("e.g. blink 0.1 20  =>  the led blink swtich 0.1 second in 20 times.\n");
    blink_demo(0.1, 20);
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
