#include <ili9341.h>
#include "config.h"
#include <driver.h>
#ifdef DRIVER_USING_ILI9341
#define LOG_TAG "TFT_DRIVER.r61581"
#include <drv_log.h>

uint8_t ili9341Rotation(uint8_t rotation, uint16_t &_width, uint16_t _height)
{
    uint8_t t;
    uint16_t w = *_width;
    uint16_t h = *_height;
    switch (rotation)
    {
    case 2:
        t = ILI9341_MADCTL_MX | ILI9341_MADCTL_BGR;
        _width = &w;
        _height = &h;
        break;
    case 3:
        t = ILI9341_MADCTL_MV | ILI9341_MADCTL_BGR;
        _width = &h;
        _height = &w;
        break;
    case 0:
        t = ILI9341_MADCTL_MY | ILI9341_MADCTL_BGR;
        _width = &w;
        _height = &h;
        break;
    case 1:
        t = ILI9341_MADCTL_MX | ILI9341_MADCTL_MY | ILI9341_MADCTL_MV | ILI9341_MADCTL_BGR;
        _width = &h;
        _height = &w;
        break;
    }
    return t;
}

void void ili9341WriteRegs()
{
    LOG_D("Register ili9341.");
}
#endif