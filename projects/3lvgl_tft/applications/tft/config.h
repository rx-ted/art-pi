
#ifndef __TFT_CONFIG_H__
#define __TFT_CONFIG_H__
#include <public.h>
#include <pins.h>

// #define DRIVER_USING_ILI9341
#define DRIVER_USING_R61581

#define TFT_ROTATION 0
#define TFT_WIDTH 320
#define TFT_HEIGHT 480

static rt_tft_driver_t tft_driver = {
    .tft_control_8080{
        .rd = A0,
        .wr = A1,
        .dc = A2,
        .cs = A3,
        .rst = A4,
    },
    .tft_8_parallel{
        .p0 = D0,
        .p1 = D1,
        .p2 = D2,
        .p3 = D3,
        .p4 = D4,
        .p5 = D5,
        .p6 = D6,
        .p7 = D7,
    },
};

#endif //__TFT_CONFIG_H__