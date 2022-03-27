//
// temp_sensor.h
//
// Author: Bruno Malli
// All rights reserved.
//


#pragma once

#include "common.h"
#include "ds18b20.h"

// Macros
#define TEMP_SENSORS_START  TempSensorContext tempSensorModules[] = {
#define TEMP_SENSOR( ... )  { { __VA_ARGS__ } }
#define TEMP_SENSORS_END }; const unsigned tempSensorModulesCount = ARRAY_SIZE(tempSensorModules);

// Constants
#define READ_TIMEOUT    5000

// Types

typedef struct {
	OneWire_t* oneWire;
	uint8_t* rom;
}TempSensorInit;

typedef struct {
	const TempSensorInit init;
	bool polled;
	bool inError;
	uint32_t startTicks;
	float temperature;
}TempSensorContext;

// API

void tempSensorInit(void);
void tempSensorPollingTask(void);
float getTemperature(TempSensorContext* ctx);

extern TempSensorContext tempSensorModules[];
extern const unsigned tempSensorModulesCount;

