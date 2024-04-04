#ifndef _TFTLCD_H_
#define _TFTLCD_H_

#include "Arduino.h"
#include "bitmap_typedefs.h"
#include "font_microsoft_16.h"

class TFTLCD
{
public:
        TFTLCD(uint8_t cs, uint8_t cd, uint8_t wr, uint8_t rd, uint8_t reset, uint16_t width, uint16_t height,
               uint8_t d8[]);
        uint16_t width();
        uint16_t height();
        uint16_t get_driver_id();
        void reset(void);
        void begin(uint8_t rotation = 0);

        void setRotation(uint8_t x);
        void set_address_window(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
        void set_area_window(uint16_t color, uint32_t len);

        void drawPixel(uint16_t x, uint16_t y, uint16_t color);
        void drawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t width, uint16_t color);
        void drawRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);
        void drawChar(uint16_t x, uint16_t y, char character, uint16_t fore_color, uint16_t back_color, const tFont *font,
                      uint8_t is_bg);
        void drawString(uint16_t x, uint16_t y, char *str, uint16_t fore_color, const tFont *font = &font_microsoft_16, uint16_t back_color = 0, uint8_t is_bg = 0);

        void fillRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t c);
        void fillScreen(uint16_t color);
        void fillRectFast(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t c);
        // void setScrollMargins(uint16_t top, uint16_t bottom);
        // void scrollTo(uint16_t y);

        uint16_t color565(uint8_t r, uint8_t g, uint8_t b);
        uint16_t readPixel(uint16_t x, uint16_t y);
        uint32_t readReg(uint8_t r);
        void lcd_demo();

private:
        int8_t pin_status = -1;
        uint8_t _cs, _cd, _wr, _rd, _reset;
        uint8_t _d8[8];
        uint8_t _rotation = 0, _testsize = 1;
        uint8_t _cursor_y, _cursor_x;
        uint16_t _width = 0, _height = 0;

        void init();
        void write_command(uint8_t cmd);
        void write_data8(uint8_t data);
        int8_t read();
        void write_data16(uint16_t data);
        void write_data32(uint32_t data);
        void d8_wr_or_rd(uint8_t mode);
        void write8(uint8_t value);
        void writeRegister8(uint8_t a, uint8_t d);
        void writeRegister16(uint8_t a, uint16_t d);
        void writeRegisterPair(uint8_t aH, uint8_t aL, uint16_t d);
        uint8_t read8fn(void);

        void _draw_fast_v_line(uint16_t x0, uint16_t y0, uint16_t y1, uint8_t width, uint16_t color);
        void _draw_fast_h_line(uint16_t x0, uint16_t y0, uint16_t x1, uint8_t width, uint16_t color);
        void _plot_line_low(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t width, uint16_t color);
        void _plot_line_high(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t width, uint16_t color);
        void _render_glyph(uint16_t x, uint16_t y, uint16_t fore_color, uint16_t back_color, const tImage *glyph,
                           uint8_t is_bg);
};

#define CS_ACTIVE digitalWrite(_cs, LOW)
#define CS_IDLE digitalWrite(_cs, HIGH)
#define DC_CMD digitalWrite(_cd, LOW)
#define DC_DAT digitalWrite(_cd, HIGH)
#define WR_ACTIVE digitalWrite(_wr, LOW)
#define WR_IDLE digitalWrite(_wr, HIGH)
#define RD_ACTIVE digitalWrite(_rd, LOW)
#define RD_IDLE digitalWrite(_rd, HIGH)
#define WR_STROBE          \
        {                  \
                WR_ACTIVE; \
                WR_IDLE;   \
        }
#define RST_ACTIVE digitalWrite(_reset, LOW)
#define RST_IDLE digitalWrite(_reset, HIGH)

#define read8(x) x = read8fn()
#define Color565 color565
#define abs(x) x < 0 ? -x : x

#endif
