/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-02-19     rx-ted       the first version
 */
#ifndef __SYS_PINS_H__
#define __SYS_PINS_H__

#include "drv_gpio.h"

/* pins alias. Must keep in sequence */
#define USE_RGB888

// use art-pi p1 pinout
#ifdef USE_P1
#define D0 GET_PIN(A, 9)
#define D1 GET_PIN(A, 10)
#define D2 GET_PIN(I, 5)
#define D3 GET_PIN(H, 14)
#define D4 GET_PIN(C, 7)
#define D5 GET_PIN(C, 6)
#define D6 GET_PIN(G, 7)
#define D7 GET_PIN(G, 8)
#define A0 GET_PIN(H, 12)
#define A1 GET_PIN(H, 11)
#define A2 GET_PIN(A, 8)
#define A3 GET_PIN(A, 15)
#define A4 GET_PIN(H, 15)
#define A5 GET_PIN(H, 13)
#endif
#ifdef USE_RGB888
#define D0 GET_PIN(J, 12)
#define D1 GET_PIN(J, 13)
#define D2 GET_PIN(J, 14)
#define D3 GET_PIN(J, 15)
#define D4 GET_PIN(K, 3)
#define D5 GET_PIN(K, 4)
#define D6 GET_PIN(K, 5)
#define D7 GET_PIN(K, 6)
#define A0 GET_PIN(J, 11)
#define A1 GET_PIN(K, 0)
#define A2 GET_PIN(K, 1)
#define A3 GET_PIN(K, 2)
#define A4 GET_PIN(D, 3)
#endif

#endif /* __SYS_PINS_H__ */
