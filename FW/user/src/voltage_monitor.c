//
// voltage_monitor.c
//
// Author: Bruno Malli
// All rights reserved.
//
#include "voltage_monitor.h"


typedef struct {
	uint32_t* buff;
	unsigned buffLen;
	unsigned average;
}VoltageMonitor;

VoltageMonitor ctx;

void voltageMoniorInit(uint32_t* buff, unsigned buffLen)
{
	ctx.buff = buff;
	ctx.buffLen = buffLen;
}

void voltageMonitorOnNewVal(void)
{
	unsigned sum = 0;

	for(unsigned i = 0; i < ctx.buffLen; i++)
		sum += ctx.buff[i];

	ctx.average = sum / ctx.buffLen;

}

unsigned getVoltage(void)
{
	return (ctx.average * 660) / (4095);
}
