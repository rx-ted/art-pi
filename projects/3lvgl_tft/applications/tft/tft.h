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
        int8_t _init();
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
        inline void writeCommand(uint8_t cmd);
        inline void writeCommand16(uint16_t cmd);
        inline void writeData(uint8_t data);
        inline void writeData16(uint16_t data);
        inline void writeReg(std::vector<std::vector<uint8_t>> reg); /*reg[0][i] -> i=0:command, i=1:length, i>1:null or data */

public:
        TFT(struct tft_mcu_t mcu);
        ~TFT();
        uint8_t getCurrentPinStatus();

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

/* pin  status*/
#define CONTROL_8080(val)           \
        {                           \
                pinMode(_cs, val);  \
                pinMode(_wr, val);  \
                pinMode(_rd, val);  \
                pinMode(_dc, val);  \
                pinMode(_rst, val); \
        }
#define SET_8P_MODE(val)              \
        {                             \
                pinMode(_p8[0], val); \
                pinMode(_p8[1], val); \
                pinMode(_p8[2], val); \
                pinMode(_p8[3], val); \
                pinMode(_p8[4], val); \
                pinMode(_p8[5], val); \
                pinMode(_p8[6], val); \
                pinMode(_p8[7], val); \
        }
#define DATA_P8_WRITE(val)                               \
        {                                                \
                digitalWrite(_p8[0], (val >> 0) & 0x01); \
                digitalWrite(_p8[1], (val >> 1) & 0x01); \
                digitalWrite(_p8[2], (val >> 2) & 0x01); \
                digitalWrite(_p8[3], (val >> 3) & 0x01); \
                digitalWrite(_p8[4], (val >> 4) & 0x01); \
                digitalWrite(_p8[5], (val >> 5) & 0x01); \
                digitalWrite(_p8[6], (val >> 6) & 0x01); \
                digitalWrite(_p8[7], (val >> 7) & 0x01); \
        }
#define DATA_P8_READ()                          \
        result =                                \
            (digitalRead(_p8[0]) & 0x01) << 0 | \
            (digitalRead(_p8[1]) & 0x01) << 1 | \
            (digitalRead(_p8[2]) & 0x01) << 2 | \
            (digitalRead(_p8[3]) & 0x01) << 3 | \
            (digitalRead(_p8[4]) & 0x01) << 4 | \
            (digitalRead(_p8[5]) & 0x01) << 5 | \
            (digitalRead(_p8[6]) & 0x01) << 6 | \
            (digitalRead(_p8[7]) & 0x01) << 7;

#define CS_ACTIVE() digitalWrite(_cs, LOW);
#define CS_IDLE() digitalWrite(_cs, HIGH);
#define DC_CMD() digitalWrite(_dc, LOW);
#define DC_DAT() digitalWrite(_dc, HIGH);
#define WR_ACTIVE() digitalWrite(_wr, LOW);
#define WR_IDLE() digitalWrite(_wr, HIGH);
#define RD_ACTIVE() digitalWrite(_rd, LOW);
#define RD_IDLE() digitalWrite(_rd, HIGH);
#define WR_STROBE()          \
        {                    \
                WR_ACTIVE(); \
                WR_IDLE();   \
        }
#define RST_ACTIVE() digitalWrite(_rst, LOW);
#define RST_IDLE() digitalWrite(_rst, HIGH);

#define CONTROL_8080_INITIALIZE \
        {                       \
                CS_IDLE();      \
                DC_DAT();       \
                WR_IDLE();      \
                RD_IDLE();      \
                RST_IDLE();     \
        }

#endif // TFT_LIBRARY
