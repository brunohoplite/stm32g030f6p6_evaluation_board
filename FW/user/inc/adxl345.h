//
// adxl345.h
//
// Author: Bruno Malli
// All rights reserved.
//


#pragma once

#include "common.h"

// Constants
#define DEFAULT_USER_LED_PERIOD    1000

// Macros
#define ADXL_345_START Adxl345Context adxl345Modules[] = {
#define ADXL_345( ... ) { { __VA_ARGS__ } }
#define ADXL_345_END }; const unsigned adxl345ModulesCount = ARRAY_SIZE(adxl345Modules);

// Types


typedef struct{
	I2C_HandleTypeDef* hi2c;
	uint16_t i2cId;
	uint8_t deviceId;
	uint16_t intPin;
}Adxl345Init;

typedef struct{
	const Adxl345Init init;
}Adxl345Context;


// API
void adxl345Init(void);
void adxl345OnInterrupt(Adxl345Context* ctx);

extern Adxl345Context adxl345Modules[];
extern const unsigned adxl345ModulesCount;
