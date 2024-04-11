// #include<driver/driver.h>

// #ifdef TFT_USING_R61581
// #define TFT_USING_R61581
#include "rtdef.h"
#include <vector>

#define TFT_WIDTH 320
#define TFT_HEIGHT 480

#define R61581_VFP 0
#define R61581_VBP 0
#define R61581_DPL 0
#define R61581_EPL 0
#define R61581_HSPL 0
#define R61581_VSPL 0

#define R61581_NOP 0x00
#define R61581_SWRST 0x01

#define R61581_SLPIN 0x10
#define R61581_SLPOUT 0x11

#define R61581_INVOFF 0x20
#define R61581_INVON 0x21

#define R61581_DISPOFF 0x28
#define R61581_DISPON 0x29


#define R61581_RAMRD 0x2E
#define R61581_MADCTL 0x36
#define R61581_MAD_MY 0x80
#define R61581_MAD_MX 0x40
#define R61581_MAD_MV 0x20
#define R61581_MAD_ML 0x10
#define R61581_MAD_RGB 0x00
#define R61581_MAD_BGR 0x08
#define R61581_MAD_MH 0x04
#define R61581_MAD_SS 0x02
#define R61581_MAD_GS 0x01

std::vector<std::vector<uint8_t>> reg = {
    {0xB0, 0x00},
    {0xB3, 0x02, 0x00, 0x00, 0x00},
    {0xC0, 0x13, 0x3B, 0x00, 0x02, 0x00, 0x01, 0x00, 0x43},
    // {0xC0, 0x02, 0x3B, 0x00, 0x00, 0x00, 0x01, 0x00, 0x43},
    {0xC1, 0x08, 0x16, 0x08, 0x08},
    {0xC4, 0x11, 0x07, 0x03, 0x03},
    {0xC6, 0x00},
    {0xC8, 0x03, 0x03, 0x13, 0x5C, 0x03, 0x07, 0x14, 0x08, 0x00, 0x21, 0x08, 0x14, 0x07, 0x53, 0x0C, 0x13, 0x03, 0x03, 0x21, 0x00},
    {0x0C, 0x55},
    {0x36, 0x00},
    {0x38},
    {0x3A, 0x55},
    {0xD0, 0x07, 0x07, 0x1D, 0x03},
    {0xD1, 0x03, 0x30, 0x10},
    {0xD2, 0x03, 0x14, 0x04},
    {0x11},
    {0x2A, 0x00, 0x00, ((TFT_WIDTH - 1) >> 8) & 0XFF, (TFT_WIDTH - 1) & 0XFF},
    {0x2B, 0x00, 0x00, ((TFT_HEIGHT - 1) >> 8) & 0XFF, (TFT_HEIGHT - 1) & 0XFF},
    {0x29},
    {0x2C}};

uint8_t getRotation(uint8_t rotation, uint16_t &_width, uint16_t &_height)
{
    uint16_t w = _width, h = _height;
    uint8_t t;
    switch (rotation)
    {
    case 2:
        t = R61581_MAD_BGR | R61581_MAD_GS;
        _width = TFT_WIDTH;
        _height = TFT_HEIGHT;
        break;
    case 1:
        t = R61581_MAD_MV | R61581_MAD_BGR;
        _width = TFT_HEIGHT;
        _height = TFT_WIDTH;
        break;
    case 0:
        t = R61581_MAD_BGR | R61581_MAD_MX;
        _width = w;
        _height = h;
        break;
    case 3:
        t = R61581_MAD_MV | R61581_MAD_BGR | R61581_MAD_MX | R61581_MAD_GS;
        _width = TFT_HEIGHT;
        _height = TFT_WIDTH;
        break;
    }
    return t;
}

// #endif