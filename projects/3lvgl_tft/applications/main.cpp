/**
 * @file main.cpp
 * @author rx-ted (gjy.18sui@gmail.com)
 * @brief main
 * @version 0.1
 * @date 2024-04-17
 * @copyright Copyright (c) 2024
 */

#include <rtthread.h>
#include <driver/color.h>

int main(void)
{
}

#include "stm32h7xx.h"
#include <stm32h750xx.h>
static int vtor_config(void)
{
    /* Vector Table Relocation in Internal QSPI_FLASH */
    SCB->VTOR = QSPI_BASE;
    return 0;
}
INIT_BOARD_EXPORT(vtor_config);
