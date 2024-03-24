#include "drv_tft.h"
#include <rtdbg.h>

drv_tft::drv_tft(struct rt_tft_mcu_t *mcu)
{
    rt_err_t result = 0;

    RT_ASSERT(mcu);
    tft_device.mcu = mcu;
    result = _init(tft_device.mcu);
}

rt_err_t drv_tft::_init(rt_tft_mcu_t *mcu)
{
    RT_ASSERT(tft_device.mcu->cs);
    RT_ASSERT(tft_device.mcu->dc);
    RT_ASSERT(tft_device.mcu->wr);
    RT_ASSERT(tft_device.mcu->rd);
    rt_pin_mode(tft_device.mcu->cs, PIN_MODE_OUTPUT); // Enable outputs
    rt_pin_mode(tft_device.mcu->dc, PIN_MODE_OUTPUT);
    rt_pin_mode(tft_device.mcu->wr, PIN_MODE_OUTPUT);
    rt_pin_mode(tft_device.mcu->rd, PIN_MODE_OUTPUT);
    CS_IDLE;
    DC_DAT;
    RD_IDLE;
    WR_IDLE;
    RT_ASSERT(tft_device.mcu->rst);
    if (tft_device.mcu->rst)
    {
        rt_pin_mode(tft_device.mcu->rst, PIN_MODE_OUTPUT);
        RST_IDLE;
    }

    return RT_EOK;
}

drv_tft::~drv_tft()
{
}