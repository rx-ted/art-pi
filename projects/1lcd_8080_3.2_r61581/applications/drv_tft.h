/**
 * driver tft
 * @author: rx-ted
 * interface is spi | iic | 8080 | rgb565 | rgb666
 */

#include "rtthread.h"
#include <rtthread.h>
#include <rtdevice.h>
#include "drv_common.h"
#include <drivers/classes/graphic.h>

#define BSP_USING_DRV_TFT
#define DRV_TFT_USING_8080

// BSP_USING_DRV_TFT
#ifdef BSP_USING_DRV_TFT
#define BSP_USING_DRV_TFT

// PUBLIC USE OBJECT
#define CS_ACTIVE rt_pin_write(tft_device.mcu->cs, PIN_LOW)
#define CS_IDLE rt_pin_write(tft_device.mcu->cs, PIN_HIGH)
#define DC_CMD rt_pin_write(tft_device.mcu->dc, PIN_LOW)
#define DC_DAT rt_pin_write(tft_device.mcu->dc, PIN_HIGH)
#define WR_ACTIVE rt_pin_write(tft_device.mcu->wr, PIN_LOW)
#define WR_IDLE rt_pin_write(tft_device.mcu->wr, PIN_HIGH)
#define RD_ACTIVE rt_pin_write(tft_device.mcu->rd, PIN_LOW)
#define RD_IDLE rt_pin_write(tft_device.mcu->rd, PIN_HIGH)
#define WR_STROBE  \
    {              \
        WR_ACTIVE; \
        WR_IDLE;   \
    }
#define RST_ACTIVE rt_pin_write(tft_device.mcu->rst, PIN_LOW)
#define RST_IDLE rt_pin_write(tft_device.mcu->rst, PIN_HIGH)

struct rt_tft_mcu_t
{
    rt_base_t rd;
    rt_base_t wr;
    rt_base_t cs;
    rt_base_t dc;
    rt_base_t rst;
    rt_base_t d8[8];
};

struct rt_tft_8080_device_t
{
    struct rt_device parent;
    struct rt_tft_mcu_t *mcu;
    struct rt_device_graphic_info *info;
    void *user_data;
};

static struct rt_tft_8080_device_t tft_device;

class drv_tft
{
private:
    rt_err_t _init(rt_tft_mcu_t *mcu);

public:
    drv_tft(struct rt_tft_mcu_t *mcu);
    ~drv_tft();
};

// DRV_TFT_USING_8080
#ifdef DRV_TFT_USING_8080
#define DRV_TFT_USING_8080
#endif // DRV_TFT_USING_8080

// DRV_TFT_USING_IIC
#ifdef DRV_TFT_USING_IIC
#define DRV_TFT_USING_IIC
#endif // DRV_TFT_USING_IIC

// DRV_TFT_USING_IIC
#ifdef DRV_TFT_USING_SPI
#define DRV_TFT_USING_SPI
#endif // DRV_TFT_USING_IIC

#else
#error "BSP_USING_DRV_TFT Library, please use what's mode connect tft."
#endif // BSP_USING_DRV_TFT