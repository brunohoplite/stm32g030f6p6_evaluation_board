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

#define THRESH_TAP    0x1D
#define DUR           0x21
#define LATENT        0x22
#define WINDOW        0x23
#define INT_ENABLE    0x2E
#define TAP_AXES      0x2A
#define POWER_CTL     0x2D
#define INT_SOURCE    0x30

static uint16_t getReadAddress(Adxl345Context* ctx)
{
	return (uint16_t)((ctx->init.i2cId << I2C_ID_BIT_SHIFT) | I2C_ID_READ_MASK);
}

static uint16_t getWriteAddress(Adxl345Context* ctx)
{
	return (uint16_t)((ctx->init.i2cId << I2C_ID_BIT_SHIFT) | I2C_ID_WRITE_MASK);
}

static HalStatus readRegister(Adxl345Context* ctx, uint8_t registerAddress, uint8_t* value)
{
	HalStatus ret = HAL_OK;
	uint16_t readAddress = getReadAddress(ctx);

	if(HAL_I2C_Mem_Read(ctx->init.hi2c, readAddress, registerAddress, 1, value, 1, 100) != HAL_OK)
		ret = HAL_ERROR;

	return ret;
}

static HalStatus writeRegister(Adxl345Context* ctx, uint8_t registerAddress, uint8_t value)
{
	HalStatus ret = HAL_OK;
	uint16_t devWriteAddress = getWriteAddress(ctx);

	if(HAL_I2C_Mem_Write(ctx->init.hi2c, devWriteAddress, registerAddress, 1, &value, 1, 100) != HAL_OK)
		ret = HAL_ERROR;

	return ret;
}

void adxl345OnInterrupt(Adxl345Context* ctx)
{
	// Read interrupt source register to clear pending interrupts
	uint8_t val;
	readRegister(ctx, INT_SOURCE, &val);
}

void adxl345Init(void)
{
	for(unsigned i = 0; i < adxl345ModulesCount; i ++)
	{
		Adxl345Context* ctx = &adxl345Modules[i];
		uint8_t val;

		// TODO: f HAL fails log via com port
		if(writeRegister(ctx, THRESH_TAP, 0x30) != HAL_OK)
			continue;

		if(writeRegister(ctx, DUR, 0xFF) != HAL_OK)
			continue;

		if(writeRegister(ctx, LATENT, 0x20) != HAL_OK)
			continue;

		if(writeRegister(ctx, WINDOW, 0xF0) != HAL_OK)
			continue;

		if(writeRegister(ctx, TAP_AXES, 7) != HAL_OK) // Enable the tap detection on all axis
			continue;

		if(writeRegister(ctx, INT_ENABLE, (1 << 5) ) != HAL_OK) // Enable INT1
			continue;

		if(writeRegister(ctx, POWER_CTL, (1 << 3) ) != HAL_OK)
			continue;
	}
}
