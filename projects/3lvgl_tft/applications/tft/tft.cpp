#include "tft.h"
#include <itoa.h>
#include <driver.h>
#include <config.h>

TFT tft;
TFT::TFT()
{
    _width = TFT_WIDTH;
    _height = TFT_HEIGHT;
    _rotation = TFT_ROTATION;
    _rd = tft_driver.tft_control_8080.rd;
    _wr = tft_driver.tft_control_8080.wr;
    _dc = tft_driver.tft_control_8080.dc;
    _cs = tft_driver.tft_control_8080.cs;
    _rst = tft_driver.tft_control_8080.rst;
    _p8[0] = tft_driver.tft_8_parallel.p0;
    _p8[1] = tft_driver.tft_8_parallel.p1;
    _p8[2] = tft_driver.tft_8_parallel.p2;
    _p8[3] = tft_driver.tft_8_parallel.p3;
    _p8[4] = tft_driver.tft_8_parallel.p4;
    _p8[5] = tft_driver.tft_8_parallel.p5;
    _p8[6] = tft_driver.tft_8_parallel.p6;
    _p8[7] = tft_driver.tft_8_parallel.p7;
}

TFT::~TFT()
{
    delete &tft;
}
int8_t TFT::destory()
{
    return 0;
}

int8_t TFT::begin(String name)
{
    _init(name);
    return RT_EOK;
}

int8_t TFT::_init(String name)
{
    _driver_name.operator=(name);
    delay(100);
    CONTROL_8080(OUTPUT);
    SET_8P_MODE(OUTPUT);
    CONTROL_8080_INITIALIZE;
    DATA_P8_WRITE(0XFF);
    _driver_id = findDriverName(_driver_name.c_str()); // if has new driver pls open to add here.
    writeRegs();
    return RT_EOK;
}

uint8_t TFT::getCurrentPinStatus()
{
    return read8();
}

void TFT::writeReg(uint8_t *reg, uint8_t len)
{
    writeCommand(reg[0]);
    for (size_t i = 1; i < len; i++)
    {
        writeData(reg[i]);
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

uint8_t TFT::findDriverId()
{
    return _driver_id;
}

char *TFT::getDriverName()
{
    return _driver_name.c_str();
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
void TFT::fillArray(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t *color_p)
{
    setAddrWindow(x1, y1, x2, y2);
    setAreaWindow(color_p, (uint32_t)(x2 - x1 + 1) * (y2 - y1 + 1));
}

void TFT::fillArray(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
{
    setAddrWindow(x1, y1, x2, y2);
    setAreaWindow(color, (uint32_t)(x2 - x1 + 1) * (y2 - y1 + 1));
}

void TFT::setAreaWindow(uint16_t *color, uint32_t len)
{
    while (len--)
    {
        writeData16(*color);
        color++;
    }
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
