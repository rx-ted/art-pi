#include <rtdevice.h>
#include <rtdef.h>
class TFT1
{
private:
    rt_base_t _rd, _wr, _dc, _cs, _rst;
    rt_base_t _p8[8];

    void write(uint8_t d);
    uint8_t read8();
    void writeCommand(uint8_t c);
    void writeData(uint8_t d);
    void writeReg(uint8_t *reg);

public:
    TFT1();
    uint8_t getCurrentPinStatus();
    uint8_t getRstPinStatus(uint8_t d);
    uint16_t getDriverId();

    void fillScreen(uint16_t c);
    ~TFT1();
};

#define CONTROL_8080(val)   \
    {                       \
        pinMode(_cs, val);  \
        pinMode(_wr, val);  \
        pinMode(_rd, val);  \
        pinMode(_dc, val);  \
        pinMode(_rst, val); \
    }

#define SET_8P_MODE(val)      \
    {                         \
        pinMode(_p8[0], val); \
        pinMode(_p8[1], val); \
        pinMode(_p8[2], val); \
        pinMode(_p8[3], val); \
        pinMode(_p8[4], val); \
        pinMode(_p8[5], val); \
        pinMode(_p8[6], val); \
        pinMode(_p8[7], val); \
    }

#define DATA_P8_WRITE(val)                       \
    {                                            \
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
    {                                           \
        uint8_t result =                        \
            (digitalRead(_p8[0]) & 0x01) << 0 | \
            (digitalRead(_p8[1]) & 0x01) << 1 | \
            (digitalRead(_p8[2]) & 0x01) << 2 | \
            (digitalRead(_p8[3]) & 0x01) << 3 | \
            (digitalRead(_p8[4]) & 0x01) << 4 | \
            (digitalRead(_p8[5]) & 0x01) << 5 | \
            (digitalRead(_p8[6]) & 0x01) << 6 | \
            (digitalRead(_p8[7]) & 0x01) << 7;  \
        return result;                          \
    }

#define CS_ACTIVE digitalWrite(_cs, LOW)
#define CS_IDLE digitalWrite(_cs, HIGH)
#define DC_CMD digitalWrite(_dc, LOW)
#define DC_DAT digitalWrite(_dc, HIGH)
#define WR_ACTIVE digitalWrite(_wr, LOW)
#define WR_IDLE digitalWrite(_wr, HIGH)
#define RD_ACTIVE digitalWrite(_rd, LOW)
#define RD_IDLE digitalWrite(_rd, HIGH)
#define WR_STROBE  \
    {              \
        WR_ACTIVE; \
        WR_IDLE;   \
    }
#define RST_ACTIVE digitalWrite(_rst, LOW)
#define RST_IDLE digitalWrite(_rst, HIGH)

#define CONTROL_8080_INITIALIZE \
    {                           \
        CS_IDLE;                \
        DC_DAT;                 \
        WR_IDLE;                \
        RD_IDLE;                \
        RST_IDLE;               \
    }

#define SCREEN_XSIZE 320
#define SCREEN_YSIZE 480

#define R61581_VFP 0
#define R61581_VBP 0
#define R61581_DPL 0
#define R61581_EPL 0
#define R61581_HSPL 0
#define R61581_VSPL 0

#define WHITE 0xFFFF
#define BLACK 0x0000
#define GRAY 0X8430
#define LIGHTGREY 0xD69A
#define DARKGREY 0x7BEF
#define RED 0xF800
#define GREEN 0x07E0
#define DARKGREEN 0x03E0
#define BLUE 0x001F