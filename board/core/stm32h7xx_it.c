#include "main.h"
#include "stm32h7xx_it.h"

extern DMA2D_HandleTypeDef hdma2d;
extern ETH_HandleTypeDef heth;
extern SD_HandleTypeDef hsd1;
extern SD_HandleTypeDef hsd2;
extern SPI_HandleTypeDef hspi2;
extern PCD_HandleTypeDef hpcd_USB_OTG_FS;

void NMI_Handler(void)
{
}

void HardFault_Handler(void)
{
  while (1)
  {
  }
}

void MemManage_Handler(void)
{
  while (1)
  {
  }
}

void BusFault_Handler(void)
{
  while (1)
  {
  }
}

void UsageFault_Handler(void)
{

  while (1)
  {
  }
}

void SVC_Handler(void)
{
}

void DebugMon_Handler(void)
{
}

void PendSV_Handler(void)
{
}

void SysTick_Handler(void)
{

  HAL_IncTick();
}

void SPI2_IRQHandler(void)
{

  HAL_SPI_IRQHandler(&hspi2);
}

void SDMMC1_IRQHandler(void)
{

  HAL_SD_IRQHandler(&hsd1);
}

void ETH_IRQHandler(void)
{

  HAL_ETH_IRQHandler(&heth);
}

void DMA2D_IRQHandler(void)
{

  HAL_DMA2D_IRQHandler(&hdma2d);
}

void OTG_FS_IRQHandler(void)
{

  HAL_PCD_IRQHandler(&hpcd_USB_OTG_FS);
}

void SDMMC2_IRQHandler(void)
{

  HAL_SD_IRQHandler(&hsd2);
}
