/**
 * @file main.cpp
 * @author rx-ted (gjy.18sui@gmail.com)
 * @brief main
 * @version 0.1
 * @date 2024-04-17
 * @copyright Copyright (c) 2024
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <drv_gpio.h>

#define LED0_PIN GET_PIN(I, 8)
int main(void)
{
    rt_pin_mode(LED0_PIN, PIN_MODE_OUTPUT);
    for (size_t i = 0; i < 10; i++)
    {
        rt_pin_write(LED0_PIN, PIN_HIGH);
        rt_thread_mdelay(100);
        rt_pin_write(LED0_PIN, PIN_LOW);
        rt_thread_mdelay(100);
    }

    rt_kprintf("Hello!\n");
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
