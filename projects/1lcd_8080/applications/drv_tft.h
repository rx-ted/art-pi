#include <rttypes.h>
#include <rtdevice.h>
#include "registers.h"
#include "config.h"
#define __BSP_USING_TFT_8080__

#ifdef __BSP_USING_TFT_8080__
#define __BSP_USING_TFT_8080__

#define DRV_TFT_VERSION "1.0.0"
#define USER_SETUP_INFO "User_Setup"

struct rt_tft_8080__mcu_t
{
    char *version = DRV_TFT_VERSION;
    char *info = USER_SETUP_INFO;

    rt_base_t cs;

    rt_base_t rd;
    rt_base_t wr;
    rt_base_t dc;

    rt_base_t rst;

    uint32_t setup_id; // ID available to use in a user setup

    uint16_t tft_driver; // Hexadecimal code
    uint16_t tft_width;  // Rotation 0 width and height
    uint16_t tft_height;
    uint8_t rotation = 0;

    rt_base_t mosi; // SPI pins
    rt_base_t miso;
    rt_base_t clk;

    rt_base_t d0; // Parallel port pins
    rt_base_t d1;
    rt_base_t d2;
    rt_base_t d3;
    rt_base_t d4;
    rt_base_t d5;
    rt_base_t d6;
    rt_base_t d7;
};

struct rt_tft_drive_t
{
    rt_device *parent;
    rt_tft_8080__mcu_t *mcu;
};

static struct rt_tft_drive_t tft_drive;

class drv_tft
{
private:
    uint8_t readData();
    void writeCommand(uint16_t c);
    void writeData8(uint8_t d);
    void writeData16(uint16_t d);
    void write8(uint8_t d);
    void _init();
    void _initBus();
    void _pin_mode_write();
    void _pin_mode_read();
    rt_bool_t _locked = false;
    void _draw_fast_v_line(uint16_t x0, uint16_t y0, uint16_t y1, uint8_t width, uint16_t color);
    void _draw_fast_h_line(uint16_t x0, uint16_t y0, uint16_t x1, uint8_t width, uint16_t color);
    void _plot_line_low(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t width, uint16_t color);
    void _plot_line_high(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t width, uint16_t color);

    uint8_t _pin_mode_status = 0; // 0:None, 1:Write, 2:Read -1:Error
    uint8_t _rotation = 0, _width, _height;

public:
    drv_tft();
    ~drv_tft();
    void begin();
    void reset();
    void drawChar(int32_t x, int32_t y, uint16_t c, uint32_t color, uint32_t bg, uint8_t size);
    void drawFastVLine(int32_t x, int32_t y, int32_t h, uint32_t color);
    void drawFastHLine(int32_t x, int32_t y, int32_t w, uint32_t color);
    void fillRect(int32_t x, int32_t y, int32_t w, int32_t h, uint32_t color);
    int16_t drawChar(uint16_t uniCode, int32_t x, int32_t y, uint8_t font),
        height(void),
        width(void);

    void setAddrWindow(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);

    void fillScreen(uint16_t color);

    void drawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t width, uint16_t color);

    void drawPixel(uint16_t x, uint16_t y, uint16_t color);

    void fillRect(uint16_t x1, uint16_t y1, uint16_t w, uint16_t h, uint16_t fillcolor);

    uint16_t readPixel(uint16_t x, uint16_t y);
    uint16_t color565(uint8_t r, uint8_t g, uint8_t b);

    void setRotation(uint8_t r);
    uint8_t getRotation(void);
    void set_area_window(uint16_t color, uint32_t len);
    void drawRect(int32_t x, int32_t y, int32_t w, int32_t h, uint32_t color),
        drawRoundRect(int32_t x, int32_t y, int32_t w, int32_t h, int32_t radius, uint32_t color),
        fillRoundRect(int32_t x, int32_t y, int32_t w, int32_t h, int32_t radius, uint32_t color);

    void fillRectVGradient(int16_t x, int16_t y, int16_t w, int16_t h, uint32_t color1, uint32_t color2);
    void fillRectHGradient(int16_t x, int16_t y, int16_t w, int16_t h, uint32_t color1, uint32_t color2);

    void drawCircle(int32_t x, int32_t y, int32_t r, uint32_t color),
        drawCircleHelper(int32_t x, int32_t y, int32_t r, uint8_t cornername, uint32_t color),
        fillCircle(int32_t x, int32_t y, int32_t r, uint32_t color),
        fillCircleHelper(int32_t x, int32_t y, int32_t r, uint8_t cornername, int32_t delta, uint32_t color),
        drawEllipse(int16_t x, int16_t y, int32_t rx, int32_t ry, uint16_t color),
        fillEllipse(int16_t x, int16_t y, int32_t rx, int32_t ry, uint16_t color),
        drawTriangle(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, uint32_t color),
        fillTriangle(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, uint32_t color);
    uint16_t drawPixel(int32_t x, int32_t y, uint32_t color, uint8_t alpha, uint32_t bg_color = 0x00FFFFFF);
    void fillRectFast(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t c);
    void drawRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);
};

#endif // __BSP_USING_TFT_8080__