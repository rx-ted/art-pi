
#include <WString.h>
#include "Print.h"
#include <rtdef.h>
#include "status.h"
#include <board.h>
#include <rtthread.h>
#include <rtdevice.h>
#include "sys.h"
#include "rtdbg.h"
#include <vector>


// 8 parallel
struct tft_8_parallel_t
{
    rt_base_t p0 = -1;
    rt_base_t p1 = -1;
    rt_base_t p2 = -1;
    rt_base_t p3 = -1;
    rt_base_t p4 = -1;
    rt_base_t p5 = -1;
    rt_base_t p6 = -1;
    rt_base_t p7 = -1;
};

// mcu info
struct tft_mcu_t
{
    char *name;
    uint16_t width = 0xffff;
    uint16_t height = 0xffff;
    rt_base_t rd = -1;
    rt_base_t wr = -1;
    rt_base_t dc = -1;
    rt_base_t cs = -1;
    rt_base_t rst = -1;
    struct tft_8_parallel_t p8;
};

// register tft device
struct tft_device_t
{
    uint8_t driver_id;
    struct tft_mcu_t mcu;
};

enum LCD_DRIVER
{
    ILI9341_PARALLEL = 0x01,
    R61581_PARALLEL = 0x02,
};

enum COLORS
{
    WHITE = 0xFFFF,
    BLACK = 0x0000,
    GRAY = 0X8430,
    LIGHTGREY = 0xD69A,
    DARKGREY = 0x7BEF,
    RED = 0xF800,
    GREEN = 0x07E0,
    DARKGREEN = 0x03E0,
    BLUE = 0x001F,
    LIGHTBLUE = 0X7D7C,
    DARKBLUE = 0X01CF,
    SKYBLUE = 0x867D,
    YELLOW = 0xFFE0,
    PURPLE = 0x780F,
    MAGENTA = 0xF81F,
    VIOLET = 0x915C,
    CYAN = 0x7FFF,
    DARKCYAN = 0x03EF,
    ORANGE = 0xFB20,
    PINK = 0xFE19,
    BROWN = 0x9A60,
    GOLD = 0xFEA0,
    SILVER = 0xC618,
    BRED = 0XF81F,
    GRED = 0XFFE0,
    GBLUE = 0X07FF,
    BRRED = 0XFC07,
    GRAYBLUE = 0X5458,
    LGRAY = 0XC618,
    LGRAYBLUE = 0XA651,
    LBBLUE = 0X2B12,
    NAVY = 0x000F,
    MAROON = 0x7800,
    OLIVE = 0x7BE0,
    GREENYELLOW = 0xB7E0,
    DKBLUE = 0x000D,
    DKTEAL = 0x020C,
    DKGREEN = 0x03E0,
    DKCYAN = 0x03EF,
    DKRED = 0x6000,
    DKMAGENTA = 0x8008,
    DKYELLOW = 0x8400,
    DKORANGE = 0x8200,
    DKPINK = 0x9009,
    DKPURPLE = 0x4010,
    DKGREY = 0x4A49,
};
