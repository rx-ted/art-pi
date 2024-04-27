#ifndef __BOARD_H__
#define __BOARD_H__

#include <rtthread.h>
#include <stm32h7xx.h>
#include <drv_common.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define CHIP_FAMILY_STM32
#define CHIP_SERIES_STM32H7
#define CHIP_NAME_STM32H750XBHX

#define ROM_START ((uint32_t)0x90000000)
#define ROM_SIZE (0x4000)
#define ROM_END ((uint32_t)(ROM_START + ROM_SIZE * 1024))

#define RAM_START (0x24000000)
#define RAM_SIZE (512)
#define RAM_END (RAM_START + RAM_SIZE * 1024)

#define BSP_CLOCK_SOURCE ("HSE")
#define BSP_CLOCK_SOURCE_FREQ_MHZ ((int32_t)0)
#define BSP_CLOCK_SYSTEM_FREQ_MHZ ((int32_t)480)

#ifdef BSP_USING_UART1
#define BSP_UART1_TX_PIN "PA9"
#define BSP_UART1_RX_PIN "PA10"
#endif

#ifdef BSP_USING_UART4
#define BSP_UART4_TX_PIN "PA0"
#define BSP_UART4_RX_PIN "PI9"
#endif

#ifdef BSP_USING_UART6
#define BSP_UART6_TX_PIN "PC6"
#define BSP_UART6_RX_PIN "PC7"
#endif

    void SystemClock_Config(void);
    void SystemClock_ReConfig(uint8_t mode);

#define RT_WEAK rt_weak

#ifdef __cplusplus
}
#endif

#endif /* __BOARD_H__ */
