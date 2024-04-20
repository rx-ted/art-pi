#ifndef __PUBLIC_H__
#define __PUBLIC_H__

#include <rtdef.h>


#define TFT_CASET 0x2A
#define TFT_PASET 0x2B
#define TFT_RAMWR 0x2C
#define TFT_MADCTL 0x36

typedef struct
{
    rt_base_t rd;
    rt_base_t wr;
    rt_base_t dc;
    rt_base_t cs;
    rt_base_t rst;
} rt_tft_control_8080_t;

// 8 parallel
typedef struct
{
    rt_base_t p0;
    rt_base_t p1;
    rt_base_t p2;
    rt_base_t p3;
    rt_base_t p4;
    rt_base_t p5;
    rt_base_t p6;
    rt_base_t p7;
} rt_tft_8_parallel_t;

typedef struct
{
    rt_tft_control_8080_t tft_control_8080;
    rt_tft_8_parallel_t tft_8_parallel;
} rt_tft_driver_t;

// mcu info
struct tft_mcu_t
{
    char *name;
    uint16_t width;
    uint16_t height;
    rt_base_t rd;
    rt_base_t wr;
    rt_base_t dc;
    rt_base_t cs;
    rt_base_t rst;
    rt_tft_8_parallel_t p8;
};

// register tft device
struct tft_device_t
{
    uint8_t driver_id;
    struct tft_mcu_t mcu;
};

enum tft_driver_name_t
{
    DRIVER_R61581 = 0x01,
    DRIVER_ILI9341 = 0x02
};

#endif // __PUBLIC_H__