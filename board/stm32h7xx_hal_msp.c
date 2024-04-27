
#include "main.h"

void HAL_MspInit(void)
{
    __HAL_RCC_SYSCFG_CLK_ENABLE();
}

void HAL_QSPI_MspInit(QSPI_HandleTypeDef *hqspi)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    if (hqspi->Instance == QUADSPI)
    {
        __HAL_RCC_QSPI_CLK_ENABLE();

        __HAL_RCC_GPIOG_CLK_ENABLE();
        __HAL_RCC_GPIOF_CLK_ENABLE();
        /**QUADSPI GPIO Configuration
        PG6     ------> QUADSPI_BK1_NCS
        PF6     ------> QUADSPI_BK1_IO3
        PF7     ------> QUADSPI_BK1_IO2
        PF8     ------> QUADSPI_BK1_IO0
        PF10     ------> QUADSPI_CLK
        PF9     ------> QUADSPI_BK1_IO1
        */
        GPIO_InitStruct.Pin = GPIO_PIN_6;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF10_QUADSPI;
        HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_10;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF9_QUADSPI;
        HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_8 | GPIO_PIN_9;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF10_QUADSPI;
        HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);
    }
}

/**
 * @brief QSPI MSP De-Initialization
 * This function freeze the hardware resources used in this example
 * @param hqspi: QSPI handle pointer
 * @retval None
 */
void HAL_QSPI_MspDeInit(QSPI_HandleTypeDef *hqspi)
{
    if (hqspi->Instance == QUADSPI)
    {
        __HAL_RCC_QSPI_CLK_DISABLE();

        /**QUADSPI GPIO Configuration
        PG6     ------> QUADSPI_BK1_NCS
        PF6     ------> QUADSPI_BK1_IO3
        PF7     ------> QUADSPI_BK1_IO2
        PF8     ------> QUADSPI_BK1_IO0
        PF10     ------> QUADSPI_CLK
        PF9     ------> QUADSPI_BK1_IO1
        */
        HAL_GPIO_DeInit(GPIOG, GPIO_PIN_6);

        HAL_GPIO_DeInit(GPIOF, GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_10 | GPIO_PIN_9);
    }
}

/**
 * @brief UART MSP Initialization
 * This function configures the hardware resources used in this example
 * @param huart: UART handle pointer
 * @retval None
 */
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    if (huart->Instance == UART4)
    {
        /* Peripheral clock enable */
        __HAL_RCC_UART4_CLK_ENABLE();

        __HAL_RCC_GPIOI_CLK_ENABLE();
        __HAL_RCC_GPIOA_CLK_ENABLE();
        /**UART4 GPIO Configuration
        PI9     ------> UART4_RX
        PA0     ------> UART4_TX
        */
        GPIO_InitStruct.Pin = GPIO_PIN_9;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
        GPIO_InitStruct.Alternate = GPIO_AF8_UART4;
        HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_0;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
        GPIO_InitStruct.Alternate = GPIO_AF8_UART4;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    }
}

/**
 * @brief UART MSP De-Initialization
 * This function freeze the hardware resources used in this example
 * @param huart: UART handle pointer
 * @retval None
 */
void HAL_UART_MspDeInit(UART_HandleTypeDef *huart)
{
    if (huart->Instance == UART4)
    {
        __HAL_RCC_UART4_CLK_DISABLE();

        /**UART4 GPIO Configuration
        PI9     ------> UART4_RX
        PA0     ------> UART4_TX
        */
        HAL_GPIO_DeInit(GPIOI, GPIO_PIN_9);
        HAL_GPIO_DeInit(GPIOA, GPIO_PIN_0);
    }
}