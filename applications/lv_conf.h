/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2022-01-28     Rudy Lo       The first version
 */

#ifndef LV_CONF_H
#define LV_CONF_H

#include <rtconfig.h>

#define LCD_W 480
#define LCD_H 320

#define LV_COLOR_DEPTH 16
#define LV_USE_PERF_MONITOR 1
#define LV_HOR_RES_MAX LCD_W
#define LV_VER_RES_MAX LCD_H

#define LV_USE_DEMO_STRESS 1
#define LV_USE_DEMO_BENCHMARK 1
#endif