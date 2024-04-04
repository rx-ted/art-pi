/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-02-19     rx-ted       the first version
 */
#ifndef APPLICATIONS_SYS_ARDUINO_H_
#define APPLICATIONS_SYS_ARDUINO_H_

#include "pins.h"

typedef bool boolean;
typedef uint8_t byte;

#define LOW PIN_LOW
#define HIGH PIN_HIGH

#define INPUT PIN_MODE_INPUT
#define OUTPUT PIN_MODE_OUTPUT

void pinMode(uint8_t pin, uint8_t mode);
void digitalWrite(uint8_t pin, uint8_t val);
int8_t digitalRead(uint8_t pin);
// int analogRead(uint8_t pin);
// void analogWrite(uint8_t pin, int val);
// void analogReference(uint8_t mode);
// void analogReadResolution(uint8_t bits);
// void analogWriteResolution(uint8_t bits);
// void analogWriteFrequency(uint32_t frequency);

void delay(unsigned long ms);
void delayMicroseconds(unsigned int us);
#endif /* APPLICATIONS_SYS_ARDUINO_H_ */
