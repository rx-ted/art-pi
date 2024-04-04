#include "tft.h"
#include "registers.h"
#include <itoa.h>
#define MSG

TFT::TFT(struct tft_mcu_t mcu)
{
    tft_device.mcu = mcu;
    _width = tft_device.mcu.width;
    _height = tft_device.mcu.height;
    _rotation = 0;
    _cs = tft_device.mcu.cs;
    _rd = tft_device.mcu.rd;
    _wr = tft_device.mcu.wr;
    _dc = tft_device.mcu.dc;
    _rst = tft_device.mcu.rst;
    _d0 = tft_device.mcu.p8.p0;
    _d1 = tft_device.mcu.p8.p1;
    _d2 = tft_device.mcu.p8.p2;
    _d3 = tft_device.mcu.p8.p3;
    _d4 = tft_device.mcu.p8.p4;
    _d5 = tft_device.mcu.p8.p5;
    _d6 = tft_device.mcu.p8.p6;
    _d7 = tft_device.mcu.p8.p7;

    init();
}

TFT::~TFT()
{
    if (!active)
    {
        active = false;
        CS_IDLE();
    }
}

int8_t TFT::begin()
{
    tft_device.driver_id = _findDeviceName(tft_device.mcu.name);
    if (tft_device.driver_id == 0xff)
    {
        LOG_E("%s: %s is not found id:%x.\n", TFT_NAME, tft_device.driver_id);
        return ERR_NOT_FIND_DEVICE;
    }
    if (!active)
    {
        active = true;
        CS_ACTIVE();
        WR_IDLE();
        RD_IDLE();
        RST_IDLE();
        delay(20);
        RST_ACTIVE();
        delay(20);
        RST_IDLE();
        CS_IDLE();
    }
    activeDrive(tft_device.driver_id);
    return ERR_OK;
}

int8_t TFT::init()
{

    rt_pin_mode(_cs, OUTPUT);
    rt_pin_mode(_wr, OUTPUT);
    rt_pin_mode(_rd, OUTPUT);
    rt_pin_mode(_dc, OUTPUT);
    rt_pin_mode(_rst, OUTPUT);

    return RT_EOK;
}

inline void TFT::writeCommand(uint8_t cmd)
{
    DC_CMD();
    write8(cmd);
    DC_DAT();
}
inline void TFT::writeCommand16(uint16_t cmd)
{
    DC_CMD();
    write8(cmd >> 8);
    write8(cmd);
    DC_DAT();
}
inline void TFT::writeData(uint8_t data)
{
    DC_DAT();
    write8(data);
}
inline void TFT::writeData(uint8_t *data, uint32_t len)
{
    DC_DAT();
    while (len > 31)
    {

        write8(*data++);
        write8(*data++);
        write8(*data++);
        write8(*data++);
        write8(*data++);
        write8(*data++);
        write8(*data++);
        write8(*data++);
        write8(*data++);
        write8(*data++);
        write8(*data++);
        write8(*data++);
        write8(*data++);
        write8(*data++);
        write8(*data++);
        write8(*data++);
        write8(*data++);
        write8(*data++);
        write8(*data++);
        write8(*data++);
        write8(*data++);
        write8(*data++);
        write8(*data++);
        write8(*data++);
        write8(*data++);
        write8(*data++);
        write8(*data++);
        write8(*data++);
        write8(*data++);
        write8(*data++);
        write8(*data++);
        write8(*data++);
        len -= 32;
    }
    while (len > 7)
    {

        write8(*data++);
        write8(*data++);
        write8(*data++);
        write8(*data++);
        write8(*data++);
        write8(*data++);
        write8(*data++);
        write8(*data++);
        len -= 8;
    }
    while (len-- > 0)
    {
        write8(*data++);
    }
}
inline void TFT::writeData16(uint16_t data)
{
    DC_DAT();
    write8(data >> 8);
    write8(data);
}

inline void TFT::write8(uint8_t data)
{
    set8pMode(OUTPUT);
    rt_pin_write(_d0, (data >> 0) & 0x01);
    rt_pin_write(_d1, (data >> 1) & 0x01);
    rt_pin_write(_d2, (data >> 2) & 0x01);
    rt_pin_write(_d3, (data >> 3) & 0x01);
    rt_pin_write(_d4, (data >> 4) & 0x01);
    rt_pin_write(_d5, (data >> 5) & 0x01);
    rt_pin_write(_d6, (data >> 6) & 0x01);
    rt_pin_write(_d7, (data >> 7) & 0x01);
    WR_STROBE();
}

inline int8_t TFT::read8()
{
    
    int8_t data;
    RD_ACTIVE();
    // TODO(Ben)
    set8pMode(INPUT);
    data = rt_pin_read(_d0) << 0 |
           rt_pin_read(_d1) << 1 |
           rt_pin_read(_d2) << 2 |
           rt_pin_read(_d3) << 3 |
           rt_pin_read(_d4) << 4 |
           rt_pin_read(_d5) << 5 |
           rt_pin_read(_d6) << 6 |
           rt_pin_read(_d7) << 7;
    RD_IDLE();
    return data;
}

inline void TFT::set8pMode(uint8_t mode)
{
    if (_mode == mode)
    {
        return;
    }
    rt_pin_mode(_d0, mode);
    rt_pin_mode(_d1, mode);
    rt_pin_mode(_d2, mode);
    rt_pin_mode(_d3, mode);
    rt_pin_mode(_d4, mode);
    rt_pin_mode(_d5, mode);
    rt_pin_mode(_d6, mode);
    rt_pin_mode(_d7, mode);
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
    case 0x01: // ili9341
        writeCommand(ILI9341_SOFTRESET);
        writeData(0);
        delay(50);
        writeCommand(ILI9341_DISPLAYOFF);
        writeData(0);
        writeCommand(ILI9341_POWERCONTROL1);
        writeData(0x23);
        writeCommand(ILI9341_POWERCONTROL2);
        writeData(0x12);
        writeCommand(ILI9341_VCOMCONTROL1);
        writeData16(0x2B2B);
        writeCommand(ILI9341_VCOMCONTROL2);
        writeData(0xC0);
        writeCommand(ILI9341_MEMCONTROL);
        writeData(ILI9341_MADCTL_MY | ILI9341_MADCTL_BGR);
        writeCommand(ILI9341_PIXELFORMAT);
        writeData(0x55);
        writeCommand(ILI9341_FRAMECONTROL);
        writeData16(0x001B);
        writeCommand(ILI9341_ENTRYMODE);
        writeData(0x07);
        writeCommand(ILI9341_SLEEPOUT);
        writeData(0);
        delay(150);
        writeCommand(ILI9341_DISPLAYON);
        writeData(0);
        setRotation(_rotation);
        break;
    case 0x02:

        break;

    default:
        LOG_E("TFT: %s not match driver id!", id);
        break;
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
    uint16_t w = _width, h = _height;
    switch (rotation)
    {
    case 2:
        t = ILI9341_MADCTL_MX | ILI9341_MADCTL_BGR;
        _width = w;
        _height = h;
        break;
    case 3:
        t = ILI9341_MADCTL_MV | ILI9341_MADCTL_BGR;
        _width = h;
        _height = w;
        break;
    case 0:
        t = ILI9341_MADCTL_MY | ILI9341_MADCTL_BGR;
        _width = w;
        _height = h;
        break;
    case 1:
        t = ILI9341_MADCTL_MX | ILI9341_MADCTL_MY | ILI9341_MADCTL_MV | ILI9341_MADCTL_BGR;
        _width = h;
        _height = w;
        break;
    }
    writeCommand(ILI9341_MADCTL);
    writeData(t);
    setAddrWindow(0, 0, _width - 1, _height - 1);
}

void TFT::setAddrWindow(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
    writeCommand(ILI9341_COLADDRSET);
    writeData16(x1);
    writeData16(x2);
    writeCommand(ILI9341_PAGEADDRSET);
    writeData16(y1);
    writeData16(y2);
    writeCommand(ILI9341_MEMORYWRITE);
}

void TFT::fillScreen(uint16_t color)
{

    setAddrWindow(0, 0, _width - 1, _height - 1);
    pushBlock16(color, (uint32_t)_width * _height);
}

void TFT::pushBlock16(uint16_t color, uint32_t len)
{
    DC_DAT();
    while (len > 31)
    {
        writeData16(color);
        writeData16(color);
        writeData16(color);
        writeData16(color);
        writeData16(color);
        writeData16(color);
        writeData16(color);
        writeData16(color);
        writeData16(color);
        writeData16(color);
        writeData16(color);
        writeData16(color);
        writeData16(color);
        writeData16(color);
        writeData16(color);
        writeData16(color);
        writeData16(color);
        writeData16(color);
        writeData16(color);
        writeData16(color);
        writeData16(color);
        writeData16(color);
        writeData16(color);
        writeData16(color);
        writeData16(color);
        writeData16(color);
        writeData16(color);
        writeData16(color);
        writeData16(color);
        writeData16(color);
        writeData16(color);
        writeData16(color);
        len -= 32;
    }

    while (len > 7)
    {
        writeData16(color);
        writeData16(color);
        writeData16(color);
        writeData16(color);
        writeData16(color);
        writeData16(color);
        writeData16(color);
        writeData16(color);
        len -= 8;
    }

    while (len--)
        writeData16(color);
}

uint16_t TFT::getDriverId()
{
    uint8_t hi, lo;
    uint16_t id;

    writeCommand(0x00);
    WR_STROBE();
    // d8_wr_or_rd(INPUT);
    DC_DAT();
    hi = read8();
    lo = read8();
    id = hi;
    id <<= 8;
    id |= lo;
    return id;
}