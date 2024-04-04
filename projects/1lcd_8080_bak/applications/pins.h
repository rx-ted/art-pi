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

#define USE_1_PERALLEL
// #define USE_1_PERALLEL

#define D0 GET_PIN(A, 9)
#define D1 GET_PIN(A, 10)
#define D2 GET_PIN(I, 5)
#define D3 GET_PIN(H, 14)
#define D4 GET_PIN(C, 7)
#define D5 GET_PIN(C, 6)
#define D6 GET_PIN(G, 7)
#define D7 GET_PIN(G, 8)

// #if defined(USE_1_PERALLEL)
// #define D0 GET_PIN(A, 9)
// #elif defined(USE_8_PERALLEL)
// #define D0 GET_PIN(A, 9)
// #define D1 GET_PIN(A, 10)
// #define D2 GET_PIN(I, 5)
// #define D3 GET_PIN(H, 14)
// #define D4 GET_PIN(C, 7)
// #define D5 GET_PIN(C, 6)
// #define D6 GET_PIN(G, 7)
// #define D7 GET_PIN(G, 8)
// #elif !defined(USE_8_PERALLEL) || !defined(USE_1_PERALLEL)
// #error "Pls use USE_8_PERALLEL or USE_1_PERALLEL"
// #endif

#define A0 GET_PIN(H, 12)
#define A1 GET_PIN(H, 11)
#define A2 GET_PIN(A, 8)
#define A3 GET_PIN(A, 15)
#define A4 GET_PIN(H, 15)
#define A5 GET_PIN(H, 13)

#endif /* APPLICATIONS_SYS_PINS_H_ */
