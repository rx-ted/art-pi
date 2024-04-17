# usage

## config.h

|     name     |    desc    |
| :----------: | :--------: |
| TFT_ROTATION |   0 or 1   |
|  TFT_WIDTH   | tft width  |
|  TFT_HEIGHT  | tft height |

### drive select

| driver               | name    | desc |
| -------------------- | ------- | ---- |
| DRIVER_USING_R61581  | r61581  | bool |
| DRIVER_USING_ILI9341 | ili9341 | bool |

### tft_driver

- static rt_tft_driver_t tft_driver

## use tft

```cpp
#include<tft.h>
extern TFT tft;
void function_name(arg,...){
    tft.begin("r61581"); // initialize to drive
    tft.fillScreen(0x0000); // 16 bit color
}

```
