#ifndef __R61581_H__
#define __R61581_H__
#include "config.h"

#ifdef DRIVER_USING_R61581
#include "rtdef.h"

#ifndef TFT_ROTATION
#define TFT_ROTATION 0
#endif
#ifndef TFT_WIDTH
#define TFT_WIDTH 320
#endif
#ifndef TFT_HEIGHT
#define TFT_HEIGHT 480
#endif

#define R61581_VFP 8
#define R61581_VBP 8
#define R61581_DPL 0
#define R61581_EPL 1
#define R61581_HSPL 0
#define R61581_VSPL 0
#define R61581_ORI 0

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

extern uint8_t r61581Rotation(uint8_t rotation, uint16_t &_width, uint16_t _height);
void r61581WriteRegs();
#endif
#endif //__R61581_H__