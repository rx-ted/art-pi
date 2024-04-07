#ifndef _TFT_LIBRARY_H_
#define _TFT_LIBRARY_H_

#include "config.h"

#define TFT_NAME "TFT"

// global tft device
static struct tft_device_t tft_device;
/* Basic operations */
template <typename T>
static inline void
swap_coord(T &a, T &b)
{
        T t = a;
        a = b;
        b = t;
}

class TFT
{
private:
        int8_t init();
        boolean active = false;
        uint8_t _mode = 0xff;
        uint8_t _rotation = 0;
        uint16_t _width;
        uint16_t _height;

        rt_base_t _cs, _rd, _wr, _dc, _rst, _d0, _d1, _d2, _d3, _d4, _d5, _d6, _d7;
        rt_base_t _p8[8];

        uint8_t _findDeviceName(char *name);
        void activeDrive(uint8_t id);
        inline uint8_t read8();
        inline void write8(uint8_t data);
        inline void set8pMode(uint8_t mode);
        inline void writeCommand(uint8_t cmd);
        inline void writeCommand16(uint16_t cmd);
        inline void writeData(uint8_t data);
        inline void writeData(uint8_t *data, uint32_t len);
        inline void writeData16(uint16_t data);

public:
        TFT(struct tft_mcu_t mcu);
        ~TFT();
        /* pin  status*/
        void CS_ACTIVE() { digitalWrite(_cs, LOW); }
        void CS_IDLE() { digitalWrite(_cs, HIGH); }
        void DC_CMD() { digitalWrite(_dc, LOW); }
        void DC_DAT() { digitalWrite(_dc, HIGH); }
        void WR_ACTIVE() { digitalWrite(_wr, LOW); }
        void WR_IDLE() { digitalWrite(_wr, HIGH); }
        void RD_ACTIVE() { digitalWrite(_rd, LOW); }
        void RD_IDLE() { digitalWrite(_rd, HIGH); }
        void RST_ACTIVE() { digitalWrite(_rst, LOW); }
        void RST_IDLE() { digitalWrite(_rst, HIGH); }
        void WR_STROBE()
        {
                WR_ACTIVE();
                WR_IDLE();
        }
        void DATA_P8_STATUS(uint8_t val)
        {
                digitalWrite(_d0, val);
                digitalWrite(_d1, val);
                digitalWrite(_d2, val);
                digitalWrite(_d3, val);
                digitalWrite(_d4, val);
                digitalWrite(_d5, val);
                digitalWrite(_d6, val);
                digitalWrite(_d7, val);
        }

        uint8_t pinInitialize();
        uint8_t pinReadALl();

        int8_t begin();
        int8_t destory();

        uint8_t findDriverId();

        char *getDriverName();
        uint16_t getHeight();
        uint16_t getWidth();
        uint16_t getDriverId();

        void setRotation(uint8_t rotation);
        // void setAddrWindow(uint16_t x, uint16_t y, uint16_t w, uint16_t h);
        void setAddrWindow(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
        void setAreaWindow(uint16_t color, uint32_t len);

        void fillScreen(uint16_t color);

        // void pushBlock16(uint16_t color, uint32_t len);

        void drawPixel(int16_t x, int16_t y, uint16_t color);
        void drawFastVLine(int16_t x, int16_t y, uint16_t h, uint16_t color);
        void drawFastHLine(int16_t x, int16_t y, uint16_t w, uint16_t color);
        void drawFastVLine(uint16_t x0, uint16_t y0, uint16_t y1, uint16_t width, uint16_t color);
        void drawFastHLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t width, uint16_t color);
        void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);
        void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
        void drawEllipse(int16_t x0, int16_t y0, int16_t rx, int16_t ry, uint16_t color);
        void drawRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color);
        void drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
        void drawCircleHelper(int16_t x0, int16_t y0, int16_t rr, uint8_t cornername, uint16_t color);

        void drawRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);

        void plot_line_low(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t width, uint16_t color);
        void plot_line_high(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t width, uint16_t color);
};

#endif // TFT_LIBRARY
