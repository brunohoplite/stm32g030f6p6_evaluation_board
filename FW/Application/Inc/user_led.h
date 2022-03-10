// STM32G030F6 evaluation board
// file name: user_led.c
// Author: BM

#pragma once

#include "stm32g0xx_hal.h"

#define DEFAULT_USER_LED_PERIOD    1000


void userLedInit(GPIO_TypeDef* ledPort, uint16_t ledPin);
void userLedHeartBeat(void);
void userLedSetHeartBeatPeriod(unsigned period);
unsigned userLedGetHeartBeatPeriod(void);
