//
// voltage_monitor.c
//
// Author: Bruno Malli
// All rights reserved.
//
#pragma once

#include "common.h"

void voltageMoniorInit(uint32_t* buff, unsigned buffLen);
void voltageMonitorOnNewVal(void);
unsigned getVoltage(void);
