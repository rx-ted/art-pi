#include "tft.h"
#include "registers.h"
#include <itoa.h>
#include <driver/public.h>
#include "driver/r61581.h"

#define MSG

TFT::TFT(struct tft_mcu_t mcu)
{
    tft_device.mcu = mcu;
    _width = TFT_WIDTH;
    _height = TFT_HEIGHT;
    _rotation = 0;
    _cs = tft_device.mcu.cs;
    _rd = tft_device.mcu.rd;
    _wr = tft_device.mcu.wr;
    _dc = tft_device.mcu.dc;
    _rst = tft_device.mcu.rst;
    _p8[0] = tft_device.mcu.p8.p0;
    _p8[1] = tft_device.mcu.p8.p1;
    _p8[2] = tft_device.mcu.p8.p2;
    _p8[3] = tft_device.mcu.p8.p3;
    _p8[4] = tft_device.mcu.p8.p4;
    _p8[5] = tft_device.mcu.p8.p5;
    _p8[6] = tft_device.mcu.p8.p6;
    _p8[7] = tft_device.mcu.p8.p7;
}

TFT::~TFT()
{
}
int8_t TFT::destory()
{
    return 0;
}

int8_t TFT::begin()
{
    _init();
    return ERR_OK;
}

int8_t TFT::_init()
{
    delay(500);
    CONTROL_8080(OUTPUT);
    SET_8P_MODE(OUTPUT);
    CONTROL_8080_INITIALIZE;
    DATA_P8_WRITE(0XFF);
    tft_device.driver_id = _findDeviceName(tft_device.mcu.name);
    if (tft_device.driver_id == 0xff)
    {
        LOG_E("%s: %s is not found id:%x.\n", TFT_NAME, tft_device.driver_id);
        return ERR_NOT_FIND_DEVICE;
    }
    activeDrive(tft_device.driver_id);
    return RT_EOK;
}

uint8_t TFT::getCurrentPinStatus()
{
    return read8();
}

inline void TFT::writeReg(std::vector<std::vector<uint8_t>> reg)
{

    for (size_t i = 0; i < reg.size(); i++)
    {
        writeCommand(reg[i][0]);
        for (size_t j = 1; j < reg[i].size(); j++)
        {
            writeData(reg[i][j]);
        }
    }
}

inline void TFT::writeCommand(uint8_t cmd)
{
    CS_ACTIVE();
    DC_CMD();
    write8(cmd);
    DC_DAT();
    CS_IDLE();
}

inline void TFT::writeData(uint8_t data)
{
    CS_ACTIVE();
    DC_DAT();
    write8(data);
    CS_IDLE();
}
inline void TFT::writeData16(uint16_t data)
{
    CS_ACTIVE();
    DC_DAT();
    write8(data >> 8);
    write8(data);
    CS_IDLE();
}

inline void TFT::write8(uint8_t data)
{
    SET_8P_MODE(OUTPUT);
    DATA_P8_WRITE(data);
    WR_STROBE();
}

inline uint8_t TFT::read8()
{
    SET_8P_MODE(INPUT);
    CS_ACTIVE();
    RD_ACTIVE();
    // TODO(Ben)
    uint8_t result = DATA_P8_READ();
    RD_IDLE();
    CS_IDLE();
    return result;
}

uint8_t TFT::_findDeviceName(char *name)
{
    char *tmp = toLowerCase(name);
    if (tmp == NULL)
    {
        return ERR_NOT_VALUE;
    }
    if (equal(tmp, (char *)"ili9341"))
    {
        return 0x01;
    }
    else if (equal(tmp, (char *)"r61581"))
    {
        return 0x02;
    }
    // if you have more driver, can add here.
    return 0xff;
}

void TFT::activeDrive(uint8_t id)
{
    switch (id)
    {
    case 1: // ili9341
        // writeCommand(ILI9341_SOFTRESET);
        // writeData(0);
        // delay(50);
        // writeCommand(ILI9341_DISPLAYOFF);
        // writeData(0);
        // writeCommand(ILI9341_POWERCONTROL1);
        // writeData(0x23);
        // writeCommand(ILI9341_POWERCONTROL2);
        // writeData(0x12);
        // writeCommand(ILI9341_VCOMCONTROL1);
        // writeData16(0x2B2B);
        // writeCommand(ILI9341_VCOMCONTROL2);
        // writeData(0xC0);
        // writeCommand(ILI9341_MEMCONTROL);
        // writeData(ILI9341_MADCTL_MY | ILI9341_MADCTL_BGR);
        // writeCommand(ILI9341_PIXELFORMAT);
        // writeData(0x55);
        // writeCommand(ILI9341_FRAMECONTROL);
        // writeData16(0x001B);
        // writeCommand(ILI9341_ENTRYMODE);
        // writeData(0x07);
        // writeCommand(ILI9341_SLEEPOUT);
        // writeData(0);
        // delay(150);
        // writeCommand(ILI9341_DISPLAYON);
        // writeData(0);
        // setRotation(_rotation);
        break;
    case 2:
#define TFT_USING_R61581
        writeReg(reg);
        break;
        // TODO(Ben)
    }
}
uint8_t TFT::findDriverId()
{
    return tft_device.driver_id;
}

char *TFT::getDriverName()
{
    return tft_device.mcu.name;
}

uint16_t TFT::getHeight()
{
    return _height;
}
uint16_t TFT::getWidth()
{
    return _width;
}

void TFT::setRotation(uint8_t rotation)
{
    _rotation = rotation;
    uint8_t t;
    writeCommand(TFT_MADCTL);
    writeData(getRotation(_rotation, _width, _height));
    setAddrWindow(0, 0, _width - 1, _height - 1);
}

void TFT::setAddrWindow(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
    writeCommand(TFT_CASET);
    writeData16(x1);
    writeData16(x2);
    writeCommand(TFT_PASET);
    writeData16(y1);
    writeData16(y2);
    writeCommand(TFT_RAMWR);
}
void TFT::fillScreen(uint16_t color)
{
    setAddrWindow(0, 0, _width - 1, _height - 1);
    setAreaWindow(color, (uint32_t)_width * _height);
}

void TFT::setAreaWindow(uint16_t color, uint32_t len)
{
    uint16_t blocks = (uint16_t)(len / 64); // 64 pixels/block
    uint8_t pass_count;
    uint8_t color_high = color >> 8;
    uint8_t color_low = color;
    writeData16(color);
    len--;
    // If higher byte and lower byte are identical,
    // just strobe the WR pin to send the previous data
    if (color_high == color_low)
    {
        while (blocks--)
        {
            // pass count = number of blocks / pixels per pass = 64 / 4
            pass_count = 16;
            while (pass_count--)
            {
                for (uint8_t i = 0; i < 8; ++i)
                    WR_STROBE();
            }
        }
        // Fill any remaining pixels (1 to 64)
        pass_count = len & 63;
        while (pass_count--)
        {
            WR_STROBE();
            WR_STROBE();
        }
    }
    // If higher and lower bytes are different, send those bytes
    else
    {
        while (blocks--)
        {
            pass_count = 16;
            while (pass_count--)
            {
                writeData(color_high);
                writeData(color_low);
                writeData(color_high);
                writeData(color_low); // 2
                writeData(color_high);
                writeData(color_low);
                writeData(color_high);
                writeData(color_low); // 4
            }
        }
        pass_count = len & 63;
        while (pass_count--)
        {
            // write here the remaining data
            writeData(color_high);
            writeData(color_low);
        }
    }
}

uint16_t TFT::getDriverId()
{
    writeCommand(0x0a);
    uint16_t result = 0;
    result |= read8() << 8 | read8();
    return result;
}
