#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "stm32h7xx_hal.h"

  void Error_Handler(void);
  void HAL_MspInit(void)
  {
    __HAL_RCC_SYSCFG_CLK_ENABLE();
  }

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */