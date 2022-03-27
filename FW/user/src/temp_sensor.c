//
// temp_sensor.c
//
// Author: Bruno Malli
// All rights reserved.
//

#include "temp_sensor.h"


void tempSensorInit(void)
{
	if(!Ds18b20_Init())
		asm("nop"); // TODO: log via com port
}

void tempSensorPollingTask(void)
{
	for(unsigned i = 0; i < tempSensorModulesCount; i++)
	{
		TempSensorContext* ctx = &tempSensorModules[i];

		if(!ctx->polled)
		{
			DS18B20_StartAll(ctx->init.oneWire);
			ctx->polled = true;
			ctx->startTicks = HAL_GetTick();
		}
		else if(DS18B20_AllDone(ctx->init.oneWire))
		{
			DS18B20_Read(ctx->init.oneWire, ctx->init.rom, &ctx->temperature);
			ctx->polled = false;
		}
		else if( ((HAL_GetTick() - ctx->startTicks) >= READ_TIMEOUT) && !ctx->inError)
		{
			// TODO: log via com port
			ctx->inError = true;
		}
	}
}
