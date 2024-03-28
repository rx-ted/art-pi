/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-02-19     rx-ted       the first version
 */

#include "Arduino.h"

void pinMode(uint8_t pin, uint8_t mode)
{
    rt_pin_mode(pin, mode);
}
void digitalWrite(uint8_t pin, uint8_t val)
{
    rt_pin_write(pin, val);
}
int8_t digitalRead(uint8_t pin)
{
    return rt_pin_read(pin);
}

void delay(unsigned long ms)
{
    rt_thread_mdelay(ms);
}
void delayMicroseconds(unsigned int us)
{
    rt_hw_us_delay(us);
}
