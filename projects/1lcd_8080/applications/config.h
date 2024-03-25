
#define USER_SETUP_INFO "User_Setup"
#include "drv_gpio.h"

#define ILI9341_DRIVER
// #define ILI9341_2_DRIVER
// #define ST7735_DRIVER
// #define R61581_DRIVER

#define TFT_RGB_ORDER TFT_RGB // Colour order Red-Green-Blue
//  #define TFT_RGB_ORDER TFT_BGR  // Colour order Blue-Green-Red

// #define M5STACK
// #define TFT_WIDTH  80
// #define TFT_WIDTH  128
// #define TFT_WIDTH  172 // ST7789 172 x 320
// #define TFT_WIDTH  170 // ST7789 170 x 320
#define TFT_WIDTH 240 // ST7789 240 x 240 and 240 x 320
// #define TFT_HEIGHT 160
// #define TFT_HEIGHT 128
// #define TFT_HEIGHT 240 // ST7789 240 x 240
#define TFT_HEIGHT 320 // ST7789 240 x 320
// #define TFT_HEIGHT 240 // GC9A01 240 x 240

#define CONFIG_TFT_PARALLEL_8_BIT
#define TFT_PARALLEL_8_BIT
#define TFT_CS GET_PIN(A, 15)
#define TFT_DC GET_PIN(A, 8)
#define TFT_RST GET_PIN(H ,15)
#define TFT_WR GET_PIN(H, 11)
#define TFT_RD GET_PIN(H, 12)
#define TFT_D0 GET_PIN(A, 9)
#define TFT_D1 GET_PIN(A, 10)
#define TFT_D2 GET_PIN(I, 5)
#define TFT_D3 GET_PIN(H, 14)
#define TFT_D4 GET_PIN(C, 7)
#define TFT_D5 GET_PIN(C, 6)
#define TFT_D6 GET_PIN(I, 0)
#define TFT_D7 GET_PIN(G, 7)

// #define TFT_CS 1
// #define TFT_DC 1
// #define TFT_RST 1
// #define TFT_WR 1
// #define TFT_RD 1
// #define TFT_D0 1
// #define TFT_D1 1
// #define TFT_D2 1
// #define TFT_D3 1
// #define TFT_D4 1
// #define TFT_D5 1
// #define TFT_D6 1
// #define TFT_D7 1
