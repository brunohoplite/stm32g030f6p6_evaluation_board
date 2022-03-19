//
// adxl345.c
//
// Author: Bruno Malli
// All rights reserved.
//
#include "adxl345.h"
#include "user_led.h"

#define I2C_ID_BIT_SHIFT    1
#define I2C_ID_READ_MASK    1
#define I2C_ID_WRITE_MASK   1

static uint16_t getReadAddress(Adxl345Context* ctx)
{
	return (uint16_t)((ctx->init.i2cId << I2C_ID_BIT_SHIFT) | I2C_ID_READ_MASK);
}

static uint16_t getWriteAddress(Adxl345Context* ctx)
{
	return (uint16_t)((ctx->init.i2cId << I2C_ID_BIT_SHIFT) | I2C_ID_WRITE_MASK);
}

void adxl345Init(void)
{
	for(unsigned i = 0; i < adxl345ModulesCount; i ++)
	{
		Adxl345Context* ctx = &adxl345Modules[i];
		uint8_t id = 44;
		uint8_t val;

		if(HAL_I2C_Master_Transmit(ctx->init.hi2c, ctx->init.i2cId << I2C_ID_BIT_SHIFT, &id, 1, 100) == HAL_OK)
		{
			if(HAL_I2C_Master_Receive(ctx->init.hi2c, ctx->init.i2cId << I2C_ID_BIT_SHIFT, &val, 1, 100) == HAL_OK)
			{
				userLedSetHeartBeatPeriod(&userLedModules[0], ALTERNATE_LED_PERIOD);
			}
			else
			{
				asm("nop");
			}
		}
	}
}
