#ifndef __DRIVER_H__
#define __DRIVER_H__

#include <rtdef.h>

#ifdef DRIVER_USING_ILI9341
#include <ili9341.h>
#endif

#ifdef DRIVER_USING_R61581
#include <r61581.h>
#endif

void writeRegs();
uint8_t getRotation(uint8_t rotation, uint16_t &width, uint16_t height);
uint8_t findDriverName(char *name);

#endif // __DRIVER_H__