#include "drv_tft.h"
#include "board.h"
#include <rtdbg.h>

drv_tft::~drv_tft()
{
    _locked = false;
#ifdef TFT_CS
    rt_pin_write(TFT_CS, PIN_HIGH);
#endif
}

drv_tft::drv_tft()
{
    if (!_locked)
    {
        _locked = true;
    }
    else
    {
        LOG_E("THe chip select pinout is used to board!");
    }

#if defined(TFT_CS)
    tft_drive.mcu->cs = TFT_CS;
#else
    tft_drive.mcu->cs = -1;
#endif

#if defined(USER_SETUP_INFO)
    tft_drive.mcu->info = USER_SETUP_INFO;
#else
    tft_drive.mcu->info = "NA";
#endif
    tft_drive.mcu->tft_driver = -1;
    tft_drive.mcu->tft_width = TFT_WIDTH;
    tft_drive.mcu->tft_height = TFT_HEIGHT;
    tft_drive.mcu->rotation = 0; // DEFINE TO 0
#if defined(TFT_MOSI)
    tft_drive.mcu->mosi = TFT_MOSI;
#else
    tft_drive.mcu->mosi = -1;
#endif

#if defined(TFT_MISO)
    tft_drive.mcu->miso = TFT_MISO;
#else
    tft_drive.mcu->miso = -1;
#endif

#if defined(TFT_SCLK)
    tft_drive.mcu->clk = TFT_SCLK;
#else
    tft_drive.mcu->clk = -1;
#endif

#if defined(TFT_DC)
    tft_drive.mcu->dc = TFT_DC;
#else
    tft_drive.mcu->dc = -1;
#endif

#if defined(TFT_RD)
    tft_drive.mcu->rd = TFT_RD;
#else
    tft_drive.mcu->rd = -1;
#endif

#if defined(TFT_WR)
    tft_drive.mcu->wr = TFT_WR;
#else
    tft_drive.mcu->wr = -1;
#endif

#if defined(TFT_RST)
    tft_drive.mcu->rst = TFT_RST;
#else
    tft_drive.mcu->rst = -1;
#endif

#if defined(TFT_PARALLEL_8_BIT)
    tft_drive.mcu->d0 = TFT_D0;
    tft_drive.mcu->d1 = TFT_D1;
    tft_drive.mcu->d2 = TFT_D2;
    tft_drive.mcu->d3 = TFT_D3;
    tft_drive.mcu->d4 = TFT_D4;
    tft_drive.mcu->d5 = TFT_D5;
    tft_drive.mcu->d6 = TFT_D6;
    tft_drive.mcu->d7 = TFT_D7;
#else
    tft_drive.mcu->d0 = -1;
    tft_drive.mcu->d1 = -1;
    tft_drive.mcu->d2 = -1;
    tft_drive.mcu->d3 = -1;
    tft_drive.mcu->d4 = -1;
    tft_drive.mcu->d5 = -1;
    tft_drive.mcu->d6 = -1;
    tft_drive.mcu->d7 = -1;
#endif
}

void drv_tft::_init()
{
    _initBus();

    reset();
    rt_thread_mdelay(200);
#if defined(TFT_CS)
    rt_pin_write(TFT_CS, PIN_LOW);
#endif
    writeCommand(ILI9341_SOFTRESET);
    writeData8(0);
    rt_thread_mdelay(50);
    writeCommand(ILI9341_DISPLAYOFF);
    writeData8(0);
    writeCommand(ILI9341_POWERCONTROL1);
    writeData8(0x23);
    writeCommand(ILI9341_POWERCONTROL2);
    writeData8(0x12);
    writeCommand(ILI9341_VCOMCONTROL1);
    writeData16(0x2B2B);
    writeCommand(ILI9341_VCOMCONTROL2);
    writeData8(0xC0);
    writeCommand(ILI9341_MEMCONTROL);
    writeData8(ILI9341_MADCTL_MY | ILI9341_MADCTL_BGR);
    writeCommand(ILI9341_PIXELFORMAT);
    writeData8(0x55);
    writeCommand(ILI9341_FRAMECONTROL);
    writeData16(0x001B);
    writeCommand(ILI9341_ENTRYMODE);
    writeData8(0x07);
    writeCommand(ILI9341_SLEEPOUT);
    writeData8(0);
    rt_thread_mdelay(150);
    writeCommand(ILI9341_DISPLAYON);
    writeData8(0);
    rt_thread_mdelay(500);
    setRotation(tft_drive.mcu->rotation);
}

void drv_tft::reset()
{

#ifdef TFT_DC
    rt_pin_write(TFT_DC, PIN_HIGH);
#endif
#ifdef TFT_WR
    rt_pin_write(TFT_WR, PIN_HIGH);
#endif

#ifdef TFT_RD
    rt_pin_write(TFT_RD, PIN_HIGH);
#endif

#ifdef TFT_CS
    rt_pin_write(TFT_CS, PIN_HIGH);
#endif

#ifdef TFT_RST
    if (TFT_RST)
    {
        rt_pin_write(TFT_RST, PIN_LOW);
        rt_thread_mdelay(2);
        rt_pin_write(TFT_RST, PIN_HIGH);
        rt_thread_mdelay(2);
    }

    rt_pin_write(TFT_RD, PIN_HIGH);
#endif

#ifdef TFT_CS
    rt_pin_write(TFT_CS, PIN_LOW);
#endif

#ifdef TFT_DC
    rt_pin_write(TFT_DC, PIN_LOW);
#endif
    writeData8(0x00);
#ifdef TFT_WR
    rt_pin_write(TFT_WR, PIN_LOW);
    rt_pin_write(TFT_WR, PIN_HIGH);
#endif
}

void drv_tft::_initBus()
{

#ifdef TFT_CS
    if (TFT_CS >= 0)
    {
        rt_pin_mode(TFT_CS, PIN_MODE_OUTPUT);
        rt_pin_write(TFT_CS, PIN_HIGH);
    }
#endif

#if defined(TFT_WR)
    if (TFT_WR >= 0)
    {
        rt_pin_mode(TFT_WR, PIN_MODE_OUTPUT);
        rt_pin_write(TFT_WR, PIN_HIGH); // Set write strobe high (inactive)
    }
#endif
#if defined(TFT_RD)
    // Make sure read is high before we set the bus to output
    if (TFT_RD >= 0)
    {
        rt_pin_mode(TFT_RD, PIN_MODE_OUTPUT);
        rt_pin_write(TFT_RD, PIN_HIGH);
    }
#endif

#ifdef TFT_DC
    if (TFT_DC >= 0)
    {
        rt_pin_mode(TFT_DC, PIN_MODE_OUTPUT);
        rt_pin_write(TFT_DC, PIN_HIGH); // Data/Command high = data mode
    }
#endif

#ifdef TFT_RST
    if (TFT_RST >= 0)
    {
        rt_pin_mode(TFT_RST, PIN_MODE_OUTPUT);
        rt_pin_write(TFT_RST, PIN_HIGH); // Set high, do not share pin with another SPI device
    }
#endif

#if defined(TFT_PARALLEL_8_BIT)
    rt_pin_mode(TFT_D0, PIN_MODE_OUTPUT);
    rt_pin_write(TFT_D0, PIN_HIGH);
    rt_pin_mode(TFT_D1, PIN_MODE_OUTPUT);
    rt_pin_write(TFT_D1, PIN_HIGH);
    rt_pin_mode(TFT_D2, PIN_MODE_OUTPUT);
    rt_pin_write(TFT_D2, PIN_HIGH);
    rt_pin_mode(TFT_D3, PIN_MODE_OUTPUT);
    rt_pin_write(TFT_D3, PIN_HIGH);
    rt_pin_mode(TFT_D4, PIN_MODE_OUTPUT);
    rt_pin_write(TFT_D4, PIN_HIGH);
    rt_pin_mode(TFT_D5, PIN_MODE_OUTPUT);
    rt_pin_write(TFT_D5, PIN_HIGH);
    rt_pin_mode(TFT_D6, PIN_MODE_OUTPUT);
    rt_pin_write(TFT_D6, PIN_HIGH);
    rt_pin_mode(TFT_D7, PIN_MODE_OUTPUT);
    rt_pin_write(TFT_D7, PIN_HIGH);
#endif
}

void drv_tft::_pin_mode_write()
{
    if (_pin_mode_status == 1)
        return;
    _pin_mode_status = 1;
#if defined(TFT_PARALLEL_8_BIT)
    rt_pin_mode(TFT_D0, PIN_MODE_OUTPUT);
    rt_pin_mode(TFT_D1, PIN_MODE_OUTPUT);
    rt_pin_mode(TFT_D2, PIN_MODE_OUTPUT);
    rt_pin_mode(TFT_D3, PIN_MODE_OUTPUT);
    rt_pin_mode(TFT_D4, PIN_MODE_OUTPUT);
    rt_pin_mode(TFT_D5, PIN_MODE_OUTPUT);
    rt_pin_mode(TFT_D6, PIN_MODE_OUTPUT);
    rt_pin_mode(TFT_D7, PIN_MODE_OUTPUT);
#endif
}
void drv_tft::_pin_mode_read()
{
    if (_pin_mode_status == 2)
        return;
    _pin_mode_status = 2;
#if defined(TFT_PARALLEL_8_BIT)
    rt_pin_mode(TFT_D0, PIN_MODE_INPUT);
    rt_pin_mode(TFT_D1, PIN_MODE_INPUT);
    rt_pin_mode(TFT_D2, PIN_MODE_INPUT);
    rt_pin_mode(TFT_D3, PIN_MODE_INPUT);
    rt_pin_mode(TFT_D4, PIN_MODE_INPUT);
    rt_pin_mode(TFT_D5, PIN_MODE_INPUT);
    rt_pin_mode(TFT_D6, PIN_MODE_INPUT);
    rt_pin_mode(TFT_D7, PIN_MODE_INPUT);
#endif
}

void drv_tft::write8(uint8_t d)
{
    _pin_mode_write();
#if defined(TFT_PARALLEL_8_BIT)
    rt_pin_write(TFT_D0, (d >> 0) & 0x01);
    rt_pin_write(TFT_D1, (d >> 1) & 0x01);
    rt_pin_write(TFT_D2, (d >> 2) & 0x01);
    rt_pin_write(TFT_D3, (d >> 3) & 0x01);
    rt_pin_write(TFT_D4, (d >> 4) & 0x01);
    rt_pin_write(TFT_D5, (d >> 5) & 0x01);
    rt_pin_write(TFT_D6, (d >> 6) & 0x01);
    rt_pin_write(TFT_D7, (d >> 7) & 0x01);
#if defined(TFT_WR)
    rt_pin_write(TFT_WR, PIN_LOW);
    rt_pin_write(TFT_WR, PIN_HIGH);
#endif
#endif
}

void drv_tft::writeCommand(uint16_t c)
{
#if defined(TFT_DC)
    rt_pin_write(TFT_DC, PIN_LOW);
#endif
    write8(c);
}

void drv_tft::writeData8(uint8_t d)
{
#if defined(TFT_DC)
    rt_pin_write(TFT_DC, PIN_HIGH);
#endif
    write8(d);
}
void drv_tft::writeData16(uint16_t d)
{
#if defined(TFT_DC)
    rt_pin_write(TFT_DC, PIN_HIGH);
#endif
    write8(d >> 8);
    write8(d);
}

uint8_t drv_tft ::readData()
{
    int8_t value = -1;
    _pin_mode_read();
#if defined(TFT_PARALLEL_8_BIT)
#if defined(TFT_RD)
    rt_pin_write(TFT_RD, PIN_LOW);
#endif
    value = rt_pin_read(TFT_D0) << 0 | rt_pin_read(TFT_D1) << 1 | rt_pin_read(TFT_D2) << 2 | rt_pin_read(TFT_D3) << 3 | rt_pin_read(TFT_D4) << 4 | rt_pin_read(TFT_D5) << 6 | rt_pin_read(TFT_D6) << 7 | rt_pin_read(TFT_D7) << 7;
#if defined(TFT_RD)
    rt_pin_write(TFT_RD, PIN_HIGH);
#endif
#endif
    return value;
}

void drv_tft::setRotation(uint8_t r)
{
    _rotation = r;
    uint8_t t;
    uint16_t w = tft_drive.mcu->tft_width, h = tft_drive.mcu->tft_height;
    switch (_rotation)
    {
    case 2:
        t = ILI9341_MADCTL_MX | ILI9341_MADCTL_BGR;
        tft_drive.mcu->tft_width = w;
        tft_drive.mcu->tft_height = h;
        break;
    case 3:
        t = ILI9341_MADCTL_MV | ILI9341_MADCTL_BGR;
        tft_drive.mcu->tft_width = h;
        tft_drive.mcu->tft_height = w;
        break;
    case 0:
        t = ILI9341_MADCTL_MY | ILI9341_MADCTL_BGR;
        tft_drive.mcu->tft_width = w;
        tft_drive.mcu->tft_height = h;
        break;
    case 1:
        t = ILI9341_MADCTL_MX | ILI9341_MADCTL_MY | ILI9341_MADCTL_MV | ILI9341_MADCTL_BGR;
        tft_drive.mcu->tft_width = h;
        tft_drive.mcu->tft_height = w;
        break;
    }
    writeCommand(ILI9341_MADCTL);
    writeData8(t);
    setAddrWindow(0, 0, tft_drive.mcu->tft_width - 1, tft_drive.mcu->tft_height - 1);
}

void drv_tft::begin()
{
    // register the device name to tft driver
    _init();
}

void drv_tft::setAddrWindow(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
    writeCommand(ILI9341_COLADDRSET);
    writeData16(x1);
    writeData16(x2);
    writeCommand(ILI9341_PAGEADDRSET);
    writeData16(y1);
    writeData16(y2);
    writeCommand(ILI9341_MEMORYWRITE);
}

void drv_tft::fillScreen(uint16_t color)
{
    setAddrWindow(0, 0, _width - 1, _height - 1);
    set_area_window(color, (uint32_t)_width * _height);
}

void drv_tft::drawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t width, uint16_t color)
{
    if (x0 == x1) // vertical line
    {
        _draw_fast_v_line(x0, y0, y1, width, color);
    }
    else if (y0 == y1) // horizontal line
    {
        _draw_fast_h_line(x0, y0, x1, width, color);
    }

    else
    {
        if (abs(y1 - y0) < abs(x1 - x0))
        {
            if (x0 > x1)
                _plot_line_low(x1, y1, x0, y0, width, color);
            else
                _plot_line_low(x0, y0, x1, y1, width, color);
        }

        else
        {
            if (y0 > y1)
                _plot_line_high(x1, y1, x0, y0, width, color);
            else
                _plot_line_high(x0, y0, x1, y1, width, color);
        }
    }
}

void drv_tft::drawPixel(uint16_t x, uint16_t y, uint16_t color)
{
    setAddrWindow(x, y, x, y);
    writeData16(color);
}

void drv_tft::fillRect(uint16_t x1, uint16_t y1, uint16_t w, uint16_t h, uint16_t fillcolor)
{
    uint16_t x2, y2;
    // Initial off-screen clipping
    if ((w <= 0) || (h <= 0) || (x1 >= _width) || (y1 >= _height) || ((x2 = x1 + w - 1) < 0) || ((y2 = y1 + h - 1) < 0))
        return;
    if (x1 < 0)
    { // Clip left
        w += x1;
        x1 = 0;
    }
    if (y1 < 0)
    { // Clip top
        h += y1;
        y1 = 0;
    }
    if (x2 >= _width)
    { // Clip right
        x2 = _width - 1;
        w = x2 - x1 + 1;
    }
    if (y2 >= _height)
    { // Clip bottom
        y2 = _height - 1;
        h = y2 - y1 + 1;
    }
    setAddrWindow(x1, y1, x2, y2);

    writeCommand(ILI9341_MEMORYWRITE);
    for (uint16_t x = 0; x < (x2 - x1); x++)
        for (uint16_t y = 0; y < (y2 - y1); y++)
            writeData16(fillcolor);
}

uint16_t drv_tft::readPixel(uint16_t x, uint16_t y)
{
    return 0;
}

uint16_t drv_tft::color565(uint8_t r, uint8_t g, uint8_t b)
{
    return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}

void drv_tft::_draw_fast_v_line(uint16_t x0, uint16_t y0, uint16_t y1, uint8_t width, uint16_t color)
{
    if (y0 < y1)
        setAddrWindow(x0, y0, x0 + width - 1, y1); // as it's vertical line, x1=x0.. must be.
    else
        setAddrWindow(x0, y1, x0 + width - 1, y0);

    set_area_window(color, (uint32_t)width * (uint32_t)abs(y1 - y0 + 1));
}
void drv_tft::_draw_fast_h_line(uint16_t x0, uint16_t y0, uint16_t x1, uint8_t width, uint16_t color)
{
    if (x0 < x1)
        setAddrWindow(x0, y0, x1, y0 + width - 1); // as it's horizontal line, y1=y0.. must be.
    else
        setAddrWindow(x1, y0, x0, y0 + width - 1);
    set_area_window(color, (uint32_t)width * (uint32_t)abs(x1 - x0 + 1));
}
void drv_tft::_plot_line_low(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t width, uint16_t color)
{
    int16_t dx = x1 - x0;
    int16_t dy = y1 - y0;
    int8_t yi = 1;
    uint8_t pixels_per_point = width * width; // no of pixels making a point. if line width is 1, this var is 1. if 2, this var is 4 and so on
    uint8_t color_high = (uint8_t)(color >> 8);
    uint8_t color_low = (uint8_t)color;
    if (dy < 0)
    {
        yi = -1;
        dy = -dy;
    }

    int16_t D = 2 * dy - dx;
    uint16_t y = y0;
    uint16_t x = x0;

    while (x <= x1)
    {
        setAddrWindow(x, y, x + width - 1, y + width - 1);
        // Drawing all the pixels of a single point
#if defined(TFT_DC)
        rt_pin_write(TFT_DC, PIN_HIGH);
#endif
        for (uint8_t pixel_cnt = 0; pixel_cnt < pixels_per_point; pixel_cnt++)
        {
            write8(color_high);
            write8(color_low);
        }
        if (D > 0)
        {
            y = y + yi;
            D = D - 2 * dx;
        }
        D = D + 2 * dy;
        x++;
    }
}
void drv_tft::_plot_line_high(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t width, uint16_t color)
{
    int16_t dx = x1 - x0;
    int16_t dy = y1 - y0;
    int8_t xi = 1;
    uint8_t pixels_per_point = width * width; // no of pixels making a point. if line width is 1, this var is 1. if 2, this var is 4 and so on
    uint8_t color_high = (uint8_t)(color >> 8);
    uint8_t color_low = (uint8_t)color;

    if (dx < 0)
    {
        xi = -1;
        dx = -dx;
    }

    int16_t D = 2 * dx - dy;
    uint16_t y = y0;
    uint16_t x = x0;

    while (y <= y1)
    {
        setAddrWindow(x, y, x + width - 1, y + width - 1);
        // Drawing all the pixels of a single point
#if defined(TFT_DC)
        rt_pin_write(TFT_DC, PIN_HIGH);
#endif
        for (uint8_t pixel_cnt = 0; pixel_cnt < pixels_per_point; pixel_cnt++)
        {
            write8(color_high);
            write8(color_low);
        }
        if (D > 0)
        {
            x = x + xi;
            D = D - 2 * dy;
        }
        D = D + 2 * dx;
        y++;
    }
}
void drv_tft::set_area_window(uint16_t color, uint32_t len)
{
    uint16_t blocks = (uint16_t)(len / 64); // 64 pixels/block
    uint8_t pass_count;
    uint8_t color_high = color >> 8;
    uint8_t color_low = color;
    writeData16(color);
    len--;
    if (color_high == color_low)
    {
        while (blocks--)
        {
            // pass count = number of blocks / pixels per pass = 64 / 4
            pass_count = 16;
            while (pass_count--)
            {
                for (uint8_t i = 0; i < 8; ++i)
                {
#if defined(TFT_WR)
                    rt_pin_write(TFT_WR, PIN_LOW);
                    rt_pin_write(TFT_WR, PIN_HIGH);
#endif
                }
            }
        }
        // Fill any remaining pixels (1 to 64)
        pass_count = len & 63;
        while (pass_count--)
        {
#if defined(TFT_WR)
            rt_pin_write(TFT_WR, PIN_LOW);
            rt_pin_write(TFT_WR, PIN_HIGH);
            rt_pin_write(TFT_WR, PIN_LOW);
            rt_pin_write(TFT_WR, PIN_HIGH);
#endif
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
                writeData16(color);
                writeData16(color);
                writeData16(color);
                writeData16(color);
            }
        }
        pass_count = len & 63;
        while (pass_count--)
        {
            // write here the remaining data
            writeData16(color);
        }
    }
}

void drv_tft::fillRectFast(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t c)
{
    setAddrWindow(x, y, x + w - 1, y + h - 1);
    set_area_window(c, (uint32_t)w * (uint32_t)h);
}

void drv_tft::drawRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color)
{
    // Perform bound checking
    if (x >= _width || y >= _height || w == 0 || h == 0)
        return;
    if (x + w - 1 >= _width)
        w = _width - x;
    if (y + h - 1 >= _height)
        h = _height - y;
    _draw_fast_h_line(x, y, x + w - 1, 1, color);
    _draw_fast_h_line(x, y + h, x + w - 1, 1, color);
    _draw_fast_v_line(x, y, y + h - 1, 1, color);
    _draw_fast_v_line(x + w, y, y + h - 1, 1, color);
}
