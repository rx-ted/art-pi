
#include "rtdef.h"
#include <vector>

#define TFT_WIDTH 240
#define TFT_HEIGHT 320

// Register names from Peter Barrett's Microtouch code

#define ILI9341_SOFTRESET 0x01
#define ILI9341_SLEEPIN 0x10
#define ILI9341_SLEEPOUT 0x11
#define ILI9341_NORMALDISP 0x13
#define ILI9341_INVERTOFF 0x20
#define ILI9341_INVERTON 0x21
#define ILI9341_GAMMASET 0x26
#define ILI9341_DISPLAYOFF 0x28
#define ILI9341_DISPLAYON 0x29
#define ILI9341_COLADDRSET 0x2A
#define ILI9341_PAGEADDRSET 0x2B
#define ILI9341_MEMORYWRITE 0x2C
#define ILI9341_PIXELFORMAT 0x3A
#define ILI9341_VSCRDEF 0x33
#define ILI9341_VSCRSADD 0x37
#define ILI9341_FRAMECONTROL 0xB1
#define ILI9341_DISPLAYFUNC 0xB6
#define ILI9341_ENTRYMODE 0xB7
#define ILI9341_POWERCONTROL1 0xC0
#define ILI9341_POWERCONTROL2 0xC1
#define ILI9341_VCOMCONTROL1 0xC5
#define ILI9341_VCOMCONTROL2 0xC7
#define ILI9341_MEMCONTROL 0x36
#define ILI9341_MADCTL 0x36
#define ILI9341_MADCTL_MY 0x80
#define ILI9341_MADCTL_MX 0x40
#define ILI9341_MADCTL_MV 0x20
#define ILI9341_MADCTL_ML 0x10
#define ILI9341_MADCTL_RGB 0x00
#define ILI9341_MADCTL_BGR 0x08
#define ILI9341_MADCTL_MH 0x04

std::vector<std::vector<uint8_t>> reg = {{}};

uint8_t getRotation(uint8_t rotation, uint16_t *_width, uint16_t *_height)
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