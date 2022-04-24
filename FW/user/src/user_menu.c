//
// user_menu.c
//
// Author: Bruno Malli
// All rights reserved.
//
#include "user_menu.h"
#include "ssd1306.h"

#include <stdio.h>

#define VERTICAL_SEPARATION    20
#define MENU_REFRESH_PERIOD    50

uint32_t tickStart;

static void fillMenu(unsigned voltage, unsigned xAngle, unsigned yAngle)
{
	unsigned yPos = 0;

	char usbStr[32];
	sprintf(usbStr, "USB voltage: %u V", voltage);

	ssd1306_Fill(Black);
	ssd1306_SetCursor(2, yPos);
	ssd1306_WriteString(usbStr, Font_7x10, White);
	yPos += VERTICAL_SEPARATION;
	ssd1306_SetCursor(2, yPos);
	ssd1306_WriteString("X angle -- deg", Font_7x10, White);
	yPos += VERTICAL_SEPARATION;
	ssd1306_SetCursor(2, yPos);
	ssd1306_WriteString("Y angle -- deg", Font_7x10, White);
}

void userMenuInit(void)
{
	fillMenu(4, 0, 0);
	ssd1306_UpdateScreen();

	tickStart = HAL_GetTick();
}

void userMenuTask(void)
{
	if( (HAL_GetTick() - tickStart) >= MENU_REFRESH_PERIOD )
	{

		ssd1306_UpdateScreen();
		tickStart = HAL_GetTick();
	}
}
