#include <r61581.h>
#include "config.h"
#include <driver.h>
#ifdef DRIVER_USING_R61581
#define LOG_TAG "TFT_DRIVER.r61581"
#include <drv_log.h>

#include "tft.h"
extern TFT tft;

extern uint8_t r61581Rotation(uint8_t rotation, uint16_t &_width, uint16_t _height)
{
    uint16_t w = _width, h = _height;
    uint8_t t = 0;
    switch (rotation % 2)
    {
    case 1:
        t = R61581_MAD_MY;
        _width = TFT_WIDTH;
        _height = TFT_HEIGHT;
        break;
    case 0:
        t = R61581_MAD_MV | R61581_MAD_MX | R61581_MAD_MY;
        _width = TFT_HEIGHT;
        _height = TFT_WIDTH;
        break;
    }
    return t;
}

uint8_t cmd_B0[] = {0xB0, 0x00};
uint8_t cmd_B3[] = {0xB3, 0x02, 0x00, 0x00, 0x10};
uint8_t cmd_B4[] = {0xB4, 0x00};
uint8_t cmd_B9[] = {0xB9, 0x01, 0xff, 0xff, 0x18};
uint8_t cmd_C0[] = {0xC0, 0x02, 0x3B, 0x00, 0x00, 0x00, 0x01, 0x00, 0x43};
// uint8_t cmd_C0[] = {0xC0, 0x03, 0x3B, 0x00, 0x00, 0x00, 0x01, 0x00, 0x43};
uint8_t cmd_C1[] = {0xC1, 0x08, 0x15, R61581_VFP, R61581_VBP};
uint8_t cmd_C4[] = {0xC4, 0x15, 0x03, 0x03, 0x01};
uint8_t cmd_C6[] = {0xC6, ((R61581_DPL << 0) |
                           (R61581_EPL << 1) |
                           (R61581_HSPL << 4) |
                           (R61581_VSPL << 5))};
uint8_t cmd_C8[] = {0xC8, 0x0c, 0x05, 0x0a, 0x6b, 0x04, 0x06, 0x15, 0x10, 0x00, 0x31};
uint8_t cmd_36[] = {0x36, R61581_ORI == 0 ? 0xe0 : 0x20};
uint8_t cmd_0C[] = {0x0C, 0x55};
uint8_t cmd_3A[] = {0x3A, 0x55};
uint8_t cmd_38[] = {0x38};
uint8_t cmd_D0[] = {0xD0, 0x07, 0x07, 0x14, 0xa2};
uint8_t cmd_D1[] = {0xD1, 0x03, 0x5a, 0x10};
uint8_t cmd_D2[] = {0xD2, 0x03, 0x04, 0x04};
uint8_t cmd_11[] = {0x11};
uint8_t cmd_2A[] = {0x2A, 0x00, 0x00, (uint8_t)(((tft.getWidth() - 1) >> 8) & 0XFF), (uint8_t)((tft.getWidth() - 1) & 0XFF)};
uint8_t cmd_2B[] = {0x2B, 0x00, 0x00, (uint8_t)(((tft.getHeight() - 1) >> 8) & 0XFF), (uint8_t)((tft.getHeight() - 1) & 0XFF)};
uint8_t cmd_29[] = {0x29};
uint8_t cmd_2C[] = {0x2C};

void r61581WriteRegs()
{
    LOG_D("Register r61581.");
    tft.writeReg(cmd_B0, sizeof(cmd_B0));
    tft.writeReg(cmd_B3, sizeof(cmd_B3));
    tft.writeReg(cmd_B4, sizeof(cmd_B4));
    tft.writeReg(cmd_B9, sizeof(cmd_B9));
    tft.writeReg(cmd_C0, sizeof(cmd_C0));
    tft.writeReg(cmd_C1, sizeof(cmd_C1));
    tft.writeReg(cmd_C4, sizeof(cmd_C4));
    tft.writeReg(cmd_C6, sizeof(cmd_C6));
    tft.writeReg(cmd_C8, sizeof(cmd_C8));
    tft.writeReg(cmd_36, sizeof(cmd_36));
    tft.writeReg(cmd_0C, sizeof(cmd_0C));
    tft.writeReg(cmd_3A, sizeof(cmd_3A));
    tft.writeReg(cmd_38, sizeof(cmd_38));
    tft.writeReg(cmd_D0, sizeof(cmd_D0));
    tft.writeReg(cmd_D1, sizeof(cmd_D1));
    tft.writeReg(cmd_D2, sizeof(cmd_D2));
    tft.writeReg(cmd_11, sizeof(cmd_11));
    tft.writeReg(cmd_2A, sizeof(cmd_2A));
    tft.writeReg(cmd_2B, sizeof(cmd_2B));
    tft.writeReg(cmd_29, sizeof(cmd_29));
    tft.writeReg(cmd_2C, sizeof(cmd_2C));
}
#endif