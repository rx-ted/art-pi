/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-02-19     rx-ted       the first version
 */
#ifndef APPLICATIONS_SYS_PINS_H_
#define APPLICATIONS_SYS_PINS_H_

#include <rtthread.h>
#include <rtdevice.h>

#include "drv_gpio.h"

/* pins alias. Must keep in sequence */
// #define D0 GET_PIN(11, 0)
// #define D1 GET_PIN(11, 1)
// #define D2 GET_PIN(5, 0)
// #define D3 GET_PIN(5, 1)
// #define D4 GET_PIN(11, 2)
// #define D5 GET_PIN(11, 3)
// #define D6 GET_PIN(11, 4)
// #define D7 GET_PIN(11, 5)
// #define D8 GET_PIN(5, 6)
// #define D9 GET_PIN(5, 7)
// #define D10 GET_PIN(0, 5)
// #define D11 GET_PIN(0, 2)
// #define D12 GET_PIN(0, 3)
// #define D13 GET_PIN(0, 4)

#define D0 GET_PIN(A, 9)
#define D1 GET_PIN(A, 10)
#define D2 GET_PIN(I, 5)
#define D3 GET_PIN(H, 14)
#define D4 GET_PIN(C, 7)
#define D5 GET_PIN(C, 6)
#define D6 GET_PIN(I, 0)
#define D7 GET_PIN(G, 7)

#define A0 GET_PIN(H, 12)
#define A1 GET_PIN(H, 11)
#define A2 GET_PIN(A, 8)
#define A3 GET_PIN(A, 15)
#define A4 GET_PIN(H, 15)

#define F_CPU 4800000000 /* CPU:100MHz */

#define LED_BUILTIN GET_PIN(0, 0) /* Default Built-in LED */

/* Serial2 : P-TX  P-RX */
#define Serial6 "uart4"

#define Serial Serial6

#endif /* APPLICATIONS_SYS_PINS_H_ */
