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
    _p8[0] = tft_device.mcu.p8.p0;
    _p8[1] = tft_device.mcu.p8.p1;
    _p8[2] = tft_device.mcu.p8.p2;
    _p8[3] = tft_device.mcu.p8.p3;
    _p8[4] = tft_device.mcu.p8.p4;
    _p8[5] = tft_device.mcu.p8.p5;
    _p8[6] = tft_device.mcu.p8.p6;
    _p8[7] = tft_device.mcu.p8.p7;
    init();
}

TFT::~TFT()
{
    active = false;
    pinInitialize();
}
int8_t TFT::destory()
{
    if (active)
    {
        active = false;
        pinInitialize();
    }
}

int8_t TFT::begin()
{
    if (!active)
    {
        active = true;
        CS_ACTIVE();
    }
    // activeDrive(tft_device.driver_id);
    return ERR_OK;
}

int8_t TFT::init()
{

    rt_pin_mode(_cs, OUTPUT);
    rt_pin_mode(_wr, OUTPUT);
    rt_pin_mode(_rd, OUTPUT);
    rt_pin_mode(_dc, OUTPUT);
    rt_pin_mode(_rst, OUTPUT);
    pinInitialize();
    tft_device.driver_id = _findDeviceName(tft_device.mcu.name);
    if (tft_device.driver_id == 0xff)
    {
        LOG_E("%s: %s is not found id:%x.\n", TFT_NAME, tft_device.driver_id);
        return ERR_NOT_FIND_DEVICE;
    }
    activeDrive(tft_device.driver_id);
    return RT_EOK;
}

uint8_t TFT::pinInitialize()
{
    set8pMode(OUTPUT);
    DATA_P8_STATUS(HIGH);
    RD_IDLE();
    WR_IDLE();
    DC_DAT();
    RST_IDLE();
    delay(100);
    RST_ACTIVE();
    delay(100);
    RST_IDLE();
    delay(100);
    uint8_t result = pinReadALl();
    return result;
}

uint8_t TFT::pinReadALl()
{
    uint8_t result = 0;
    result |= digitalRead(_rd) << 0;
    result |= digitalRead(_wr) << 1;
    result |= digitalRead(_dc) << 2;
    result |= digitalRead(_cs) << 3;
    result |= digitalRead(_rst) << 4;
    return result;
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
    for (uint8_t i = 0; i < 8; i++)
    {
        digitalWrite(_p8[i], (data >> i) & 0x01);
    }
    WR_STROBE();
}

inline uint8_t TFT::read8()
{

    uint8_t data = 0;
    RD_ACTIVE();
    // TODO(Ben)
    set8pMode(INPUT);
    for (uint8_t i = 0; i < 8; i++)
    {
        data |= (digitalRead(_p8[i]) & 0x01) << i;
    }

    RD_IDLE();
    return data;
}

inline void TFT::set8pMode(uint8_t mode)
{
    if (_mode == mode)
    {
        return;
    }
    for (uint8_t i = 0; i < 8; i++)
    {
        rt_pin_mode(_p8[i], mode);
    }
    _mode = mode;
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
    rt_kprintf("id is %d\n", id);
    switch (id)
    {
    case 1: // ili9341
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
    case 2:
        RST_IDLE();
        delay(5);
        RST_ACTIVE();
        delay(15);
        RST_IDLE();
        delay(5);
        writeCommand(0xB0);
        writeData(0x00);
        writeCommand(0xB3);
        writeData(0x02);
        writeData(0x00);
        writeData(0x00);
        writeData(0x00);
        writeCommand(0xC0);
        writeData(0x13);
        writeData(0x3B);
        writeData(0x00);
        writeData(0x02);
        writeData(0x00);
        writeData(0x01);
        writeData(0x00);
        writeData(0x43);
        writeCommand(0xC1);
        writeData(0x08);
        writeData(0x16);
        writeData(0x08);
        writeData(0x08);
        writeCommand(0xC4);
        writeData(0x11);
        writeData(0x07);
        writeData(0x03);
        writeData(0x03);
        writeCommand(0xC6);
        writeData(0x00);
        writeCommand(0xC8);
        writeData(0x03);
        writeData(0x03);
        writeData(0x13);
        writeData(0x5C);
        writeData(0x03);
        writeData(0x07);
        writeData(0x14);
        writeData(0x08);
        writeData(0x00);
        writeData(0x21);
        writeData(0x08);
        writeData(0x14);
        writeData(0x07);
        writeData(0x53);
        writeData(0x0C);
        writeData(0x13);
        writeData(0x03);
        writeData(0x03);
        writeData(0x21);
        writeData(0x00);
        writeCommand(0x0C);
        writeData(0x55);
        writeCommand(0x38);
        writeCommand(0x3A);
        writeData(0x55);
        writeCommand(0xD0);
        writeData(0x07);
        writeData(0x07);
        writeData(0x1D);
        writeData(0x03);
        writeCommand(0xD1);
        writeData(0x03);
        writeData(0x30);
        writeData(0x10);
        writeCommand(0xD2);
        writeData(0x03);
        writeData(0x14);
        writeData(0x04);
        writeCommand(0x11);
        writeCommand(0x2A);
        writeData16(0x0000);
        writeData16(_width - 1);
        writeCommand(0x2B);
        writeData16(0x0000);
        writeData16(_height - 1);
        writeCommand(0x29);
        writeCommand(0x2C);
        fillScreen(0x00);
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
                write8(color_high);
                write8(color_low);
                write8(color_high);
                write8(color_low); // 2
                write8(color_high);
                write8(color_low);
                write8(color_high);
                write8(color_low); // 4
            }
        }
        pass_count = len & 63;
        while (pass_count--)
        {
            // write here the remaining data
            write8(color_high);
            write8(color_low);
        }
    }
}

void TFT::fillScreen(uint16_t color)
{

    setAddrWindow(0, 0, _width - 1, _height - 1);
    setAreaWindow(color, (uint32_t)_width * _height);
}

uint16_t TFT::getDriverId()
{
    if (!active)
    {
        return ERR_NOT_ACTIVE;
    }
    writeCommand(0xd3);
    uint16_t result = 0;
    result |= read8() << 8 | read8();
    return result;
}
