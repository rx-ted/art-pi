#include "lcd.h"
#include "registers.h"

TFTLCD::TFTLCD(uint8_t cs, uint8_t cd, uint8_t wr, uint8_t rd, uint8_t reset, uint16_t width, uint16_t height,
               uint8_t d8[])
{
    // Convert pin numbers to registers and bitmasks
    _width = width;
    _height = height;
    for (uint8_t i = 0; i < 8; i++)
    {
        _d8[i] = d8[i];
    }
    _reset = reset;
    _cs = cs;
    _cd = cd;
    _wr = wr;
    _rd = rd;
    pinMode(cs, OUTPUT); // Enable outputs
    pinMode(cd, OUTPUT);
    pinMode(wr, OUTPUT);
    pinMode(rd, OUTPUT);
    if (_reset)
    {
        RST_IDLE;
        pinMode(reset, OUTPUT);
    }
    init();
}

void TFTLCD::d8_wr_or_rd(uint8_t mode)
{
    if (pin_status != mode)
    {
        for (uint8_t i = 0; i < 8; i++)
        {
            pinMode(_d8[i], mode);
        }
        pin_status = mode;
    }
}

void TFTLCD::init(void)
{
    d8_wr_or_rd(OUTPUT);
}

void TFTLCD::begin(uint8_t rotation)
{
    _rotation = rotation;
    reset();
    delay(200);
    CS_ACTIVE;
    write_command(ILI9341_SOFTRESET);
    write_data8(0);
    delay(50);
    write_command(ILI9341_DISPLAYOFF);
    write_data8(0);
    write_command(ILI9341_POWERCONTROL1);
    write_data8(0x23);
    write_command(ILI9341_POWERCONTROL2);
    write_data8(0x12);
    write_command(ILI9341_VCOMCONTROL1);
    write_data16(0x2B2B);
    write_command(ILI9341_VCOMCONTROL2);
    write_data8(0xC0);
    write_command(ILI9341_MEMCONTROL);
    write_data8(ILI9341_MADCTL_MY | ILI9341_MADCTL_BGR);
    write_command(ILI9341_PIXELFORMAT);
    write_data8(0x55);
    write_command(ILI9341_FRAMECONTROL);
    write_data16(0x001B);
    write_command(ILI9341_ENTRYMODE);
    write_data8(0x07);
    write_command(ILI9341_SLEEPOUT);
    write_data8(0);
    delay(150);
    write_command(ILI9341_DISPLAYON);
    write_data8(0);
    delay(500);
    setRotation(_rotation);
}

void TFTLCD::reset(void)
{

    DC_DAT;
    CS_IDLE;
    WR_IDLE;
    RD_IDLE;
    if (_reset)
    {
        RST_ACTIVE;
        delay(2); // 2ms
        RST_IDLE;
    }
    DC_CMD;
    write_command(0x00);
    WR_STROBE;
    CS_ACTIVE;
}

uint16_t TFTLCD::width()
{
    return _width;
}

uint16_t TFTLCD::height()
{
    return _height;
}

void TFTLCD::write8(uint8_t data)
{
    // PORTD = (PORTD & B00000011) | ((data)&B11111100);
    // PORTB = (PORTB & B11111100) | ((data)&B00000011);
    d8_wr_or_rd(OUTPUT);
    // #if defined(USE_8_PERALLEL)
    for (uint8_t i = 0; i < 8; i++)
    {
        digitalWrite(_d8[i], (data >> i) & 0x01);
        // digitalWrite(_d8[0], (data >> i) & 0x01);
    }
    // #elif defined(USE_1_PERALLEL)
    // for (uint8_t i = 0; i < 8; i++)
    // {
    // digitalWrite(_d8[0], (data >> i) & 0x01);
    // }
    // #endif
    WR_STROBE;
}

uint16_t TFTLCD::get_driver_id(void)
{
    uint8_t hi, lo;
    uint16_t id;

    write_command(0x00);
    WR_STROBE;
    // d8_wr_or_rd(INPUT);
    DC_DAT;
    hi = read();
    lo = read();

    // read8(hi);
    // read8(lo);
    // d8_wr_or_rd(OUTPUT);
    id = hi;
    id <<= 8;
    id |= lo;
    return id;
}

void TFTLCD::write_command(uint8_t cmd)
{
    DC_CMD;
    write8(cmd);
}

void TFTLCD::write_data8(uint8_t data)
{
    DC_DAT;
    write8(data);
}

void TFTLCD::write_data16(uint16_t data)
{
    write_data8(data >> 8);
    write_data8(data);
}

void TFTLCD::write_data32(uint32_t data)
{

    write_data16(data >> 16);
    write_data16(data);
}

void TFTLCD::set_address_window(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
    write_command(ILI9341_COLADDRSET);
    DC_DAT;
    write8(x1 >> 8);
    write8(x1);
    write8(x2 >> 8);
    write8(x2);

    write_command(ILI9341_PAGEADDRSET);
    DC_DAT;
    write8(y1 >> 8);
    write8(y1);
    write8(y2 >> 8);
    write8(y2);
    write_command(ILI9341_MEMORYWRITE);
}

void TFTLCD::setRotation(uint8_t rotation)
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
    write_command(ILI9341_MADCTL);
    write_data8(t);
    set_address_window(0, 0, _width - 1, _height - 1);
}

void TFTLCD::fillScreen(uint16_t color)
{
    set_address_window(0, 0, _width - 1, _height - 1);
    set_area_window(color, (uint32_t)_width * _height);
}
void TFTLCD::drawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t width, uint16_t color)
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

void TFTLCD::drawPixel(uint16_t x, uint16_t y, uint16_t color)
{
    set_address_window(x, y, x, y);
    DC_DAT;
    write8(color >> 8);
    write8(color);
}

void TFTLCD::fillRect(uint16_t x1, uint16_t y1, uint16_t w, uint16_t h, uint16_t fillcolor)
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
    set_address_window(x1, y1, x2, y2);

    write_command(ILI9341_MEMORYWRITE);
    for (uint16_t x = 0; x < (x2 - x1); x++)
        for (uint16_t y = 0; y < (y2 - y1); y++)
            write_data16(fillcolor);
}

uint16_t TFTLCD::readPixel(uint16_t x, uint16_t y)
{

    if ((x < 0) || (y < 0) || (x >= _width) || (y >= _height))
        return 0;

    return 0;
}

uint32_t TFTLCD::readReg(uint8_t r)
{
    uint32_t id;
    uint8_t x;

    // try reading register #4

    DC_CMD;
    write8(r);
    d8_wr_or_rd(INPUT); // Set up LCD data port(s) for READ operations
    DC_DAT;
    // delayMicroseconds(50);
    read8(x);
    id = x;   // Do not merge or otherwise simplify
    id <<= 8; // these lines.  It's an unfortunate
    read8(x);
    id |= x;  // shenanigans that are going on.
    id <<= 8; // these lines.  It's an unfortunate
    read8(x);
    id |= x;  // shenanigans that are going on.
    id <<= 8; // these lines.  It's an unfortunate
    read8(x);
    id |= x; // shenanigans that are going on.

    d8_wr_or_rd(OUTPUT); // Restore LCD data port(s) to WRITE configuration

    return id;
}

uint16_t TFTLCD::color565(uint8_t r, uint8_t g, uint8_t b)
{
    return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}

uint8_t TFTLCD::read8fn(void)
{
    uint8_t result = 0;
    RD_ACTIVE;
    // Serial.print("read 8bit is ");
    // Serial.println(result);
    RD_IDLE;
    return result;
}

int8_t TFTLCD::read()
{
    int8_t value = 0;
    RD_ACTIVE;
    d8_wr_or_rd(INPUT);
    for (uint8_t i = 0; i < 8; i++)
    {
        value |= (digitalRead(_d8[i]) << i);
    }
    RD_IDLE;
    return value;
}

void TFTLCD::_draw_fast_v_line(uint16_t x0, uint16_t y0, uint16_t y1, uint8_t width, uint16_t color)
{
    if (y0 < y1)
        set_address_window(x0, y0, x0 + width - 1, y1); // as it's vertical line, x1=x0.. must be.
    else
        set_address_window(x0, y1, x0 + width - 1, y0);

    set_area_window(color, (uint32_t)width * (uint32_t)abs(y1 - y0 + 1));
}
void TFTLCD::_draw_fast_h_line(uint16_t x0, uint16_t y0, uint16_t x1, uint8_t width, uint16_t color)
{
    if (x0 < x1)
        set_address_window(x0, y0, x1, y0 + width - 1); // as it's horizontal line, y1=y0.. must be.
    else
        set_address_window(x1, y0, x0, y0 + width - 1);
    set_area_window(color, (uint32_t)width * (uint32_t)abs(x1 - x0 + 1));
}
void TFTLCD::_plot_line_low(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t width, uint16_t color)
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
        set_address_window(x, y, x + width - 1, y + width - 1);
        // Drawing all the pixels of a single point

        DC_DAT;
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
void TFTLCD::_plot_line_high(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t width, uint16_t color)
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
        set_address_window(x, y, x + width - 1, y + width - 1);
        // Drawing all the pixels of a single point

        DC_DAT;
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
void TFTLCD::set_area_window(uint16_t color, uint32_t len)
{
    uint16_t blocks = (uint16_t)(len / 64); // 64 pixels/block
    uint8_t pass_count;
    uint8_t color_high = color >> 8;
    uint8_t color_low = color;
    DC_DAT;
    write8(color_high);
    write8(color_low);
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
                    WR_STROBE;
            }
        }
        // Fill any remaining pixels (1 to 64)
        pass_count = len & 63;
        while (pass_count--)
        {
            WR_STROBE;
            WR_STROBE;
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

void TFTLCD::fillRectFast(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t c)
{
    set_address_window(x, y, x + w - 1, y + h - 1);
    set_area_window(c, (uint32_t)w * (uint32_t)h);
}

void TFTLCD::drawRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color)
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
void TFTLCD::_render_glyph(uint16_t x, uint16_t y, uint16_t fore_color, uint16_t back_color, const tImage *glyph, uint8_t is_bg)
{

    uint16_t width = 0, height = 0;

    width = glyph->width;
    height = glyph->height;

    uint16_t temp_x = x;
    uint16_t temp_y = y;

    uint8_t mask = 0x80;
    uint8_t bit_counter = 0;

    const uint8_t *glyph_data_ptr = (const uint8_t *)(glyph->data);
    uint8_t glyph_data = 0;

    // font bitmaps are stored in column major order (scanned from left-to-right, not the conventional top-to-bottom)
    // as font glyphs have heigher height than width, this scanning saves some storage.
    // So, we also render in left-to-right manner.

    // Along x axis (width)
    for (int i = 0; i < width; i++)
    {
        // Along y axis (height)
        for (int j = 0; j < height; j++)
        {

            // load new data only when previous byte (or word, depends on glyph->dataSize) is completely traversed by the mask
            // bit_counter = 0 means glyph_data is completely traversed by the mask
            if (bit_counter == 0)
            {
                glyph_data = *glyph_data_ptr++;
                bit_counter = glyph->dataSize;
            }
            // Decrement bit counter
            bit_counter--;

            // If pixel is blank
            if (glyph_data & mask)
            {
                // Has background color (not transparent bg)
                if (is_bg)
                {
                    drawPixel(temp_x, temp_y, back_color);
                }
            }

            // if pixel is not blank
            else
            {
                drawPixel(temp_x, temp_y, fore_color);
            }

            glyph_data <<= 1;
            temp_y++;
        }

        // New col starts. So, row is set to initial value and col is increased by one
        temp_y = y;
        temp_x++;

        // Reset the bit counter cause we're moving to next column, so we start with a new byte
        bit_counter = 0;
    }
}

void TFTLCD::drawChar(uint16_t x, uint16_t y, char character, uint16_t fore_color, uint16_t back_color, const tFont *font, uint8_t is_bg)
{
    const tImage *img = NULL;
    for (uint8_t i = 0; i < font->length; i++)
    {
        if (font->chars[i].code == character)
        {
            img = font->chars[i].image;
            break;
        }
    }
    // No glyph (img) found, so return from this function
    if (img == NULL)
    {
        return;
    }
    if (is_bg)
        _render_glyph(x, y, fore_color, back_color, img, 1);
    else
        _render_glyph(x, y, fore_color, back_color, img, 0);
}

void TFTLCD::drawString(uint16_t x, uint16_t y, char *str, uint16_t fore_color, const tFont *font, uint16_t back_color, uint8_t is_bg)
{
    uint16_t x_temp = x;
    uint16_t y_temp = y;

    uint8_t x_padding = 0;
    uint8_t y_padding = 0;
    const tImage *img = {0};
    uint16_t width = 0, height = 0;

    while (*str)
    {
        if (*str == '\n')
        {
            x_temp = x;                                           // go to first col
            y_temp += (font->chars[0].image->height + y_padding); // go to next row (row height = height of space)
        }

        else if (*str == '\t')
        {
            x_temp += 4 * (font->chars[0].image->height + y_padding); // Skip 4 spaces (width = width of space)
        }
        else
        {
            for (uint8_t i = 0; i < font->length; i++)
            {
                if (font->chars[i].code == *str)
                {
                    img = font->chars[i].image;
                    break;
                }
            }
            // No glyph (img) found, so return from this function
            if (img == NULL)
            {
                return;
            }

            width = img->width;
            height = img->height;

            if (y_temp + (height + y_padding) > _height - 1) // not enough space available at the bottom
                return;
            if (x_temp + (width + x_padding) > _width - 1) // not enough space available at the right side
            {
                x_temp = x;                     // go to first col
                y_temp += (height + y_padding); // go to next row
            }

            if (is_bg)
                _render_glyph(x_temp, y_temp, fore_color, back_color, img, 1);
            else
                _render_glyph(x_temp, y_temp, fore_color, back_color, img, 0);
            x_temp += (width + x_padding); // next char position
        }

        str++;
    }
}
