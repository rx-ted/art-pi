#ifndef __DRIVER_H__
#define __DRIVER_H__

#include <rtdef.h>
#include <config.h>
#define LOG_TAG "TFT_DRIVER"
#include <drv_log.h>
#include <public.h>
#include <itoa.h>
#include <r61581.h>
#include <ili9341.h>



void writeRegs()
{
#ifdef DRIVER_USING_ILI9341
    ili9341WriteRegs();
#endif
#ifdef DRIVER_USING_R61581
    r61581WriteRegs();
#endif
}

uint8_t getRotation(uint8_t rotation, uint16_t &width, uint16_t height)
{
#ifdef DRIVER_USING_ILI9341
    return ili9341Rotation(rotation, width, height);
#endif

#ifdef DRIVER_USING_R61581
    return r61581Rotation(rotation, width, height);
#endif
}

uint8_t findDriverName(char *name)
{
    char *tmp = toLowerCase(name);
    if (tmp == NULL)
    {
        return RT_EEMPTY;
    }

    if (equal(tmp, (char *)"ili9341"))
    {

        return DRIVER_ILI9341;
    }
    else if (equal(tmp, (char *)"r61581"))
    {

        return DRIVER_R61581;
    }
    return 0xff;
}

#endif // __DRIVER_H__