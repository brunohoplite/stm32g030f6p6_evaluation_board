//
// user_menu.c
//
// Author: Bruno Malli
// All rights reserved.
//
#include "user_menu.h"
#include "ssd1306.h"
#include "voltage_monitor.h"
#include "temp_sensor.h"

#include <stdio.h>

#define VERTICAL_SEPARATION    15
#define MENU_REFRESH_PERIOD    50

uint32_t tickStart;

// Take a decimal number multiplied by 100
// and return the decimal part as integer
static unsigned getTwoDecimals(unsigned val)
{
	if(val > 100)
	{
		unsigned temp = val / 100;
		temp *= 100;

		return val % temp;
	}

	return val;
}

static void fillMenu(unsigned voltage, unsigned xAngle, unsigned yAngle, unsigned temp)
{
	unsigned yPos = 0;
	char usbStr[35];
	char xStr[35];
	char tempStr[35];
	unsigned whole = voltage / 100;
	unsigned decimal = getTwoDecimals(voltage);
	unsigned tempWhole = temp / 100;
	unsigned tempDec = getTwoDecimals(temp);

	sprintf(usbStr, "USB voltage: %u.%u V", whole, decimal);
	sprintf(xStr, "X angle %u deg", xAngle);
	sprintf(tempStr, "Temperature: %u.%u", tempWhole, tempDec);

	ssd1306_Fill(Black);
	ssd1306_SetCursor(2, yPos);
	ssd1306_WriteString(usbStr, Font_7x10, White);
	yPos += VERTICAL_SEPARATION;
	ssd1306_SetCursor(2, yPos);
	ssd1306_WriteString(tempStr, Font_7x10, White);
	yPos += VERTICAL_SEPARATION;
	ssd1306_SetCursor(2, yPos);
	ssd1306_WriteString(xStr, Font_7x10, White);
	yPos += VERTICAL_SEPARATION;
	ssd1306_SetCursor(2, yPos);
	ssd1306_WriteString("Y angle -- deg", Font_7x10, White);
}

void userMenuInit(void)
{
	fillMenu(0, 0, 0, 0);
	ssd1306_UpdateScreen();

	tickStart = HAL_GetTick();
}

void userMenuTask(void)
{
	if( (HAL_GetTick() - tickStart) >= MENU_REFRESH_PERIOD )
	{
		unsigned volts = getVoltage();
		unsigned degC = getTemperature(&tempSensorModules[0]);
		static unsigned temp = 0;

		fillMenu(volts, temp++, 0, degC);
		ssd1306_UpdateScreen();
		tickStart = HAL_GetTick();
	}
}
