// STM32G030F6 evaluation board
// file name: user_led.c
// Author: BM

#include "user_led.h"

#define DEFAULT_PERIOD    1000

typedef struct{
	GPIO_TypeDef* ledPort;
	uint16_t ledPin;
	uint32_t heartBeatTicks;
	unsigned heartBeatPeriod;
}UserLedContext;

UserLedContext ctx = {
		.heartBeatPeriod = DEFAULT_USER_LED_PERIOD
};

void userLedInit(GPIO_TypeDef* ledPort, uint16_t ledPin)
{
	ctx.ledPort = ledPort;
	ctx.ledPin = ledPin;
	ctx.heartBeatTicks = HAL_GetTick();
}

void userLedHeartBeat(void)
{
	if((HAL_GetTick() - ctx.heartBeatTicks) >= ctx.heartBeatPeriod)
	{
		HAL_GPIO_TogglePin(ctx.ledPort, ctx.ledPin);
		ctx.heartBeatTicks = HAL_GetTick();
	}
}

void userLedSetHeartBeatPeriod(unsigned period)
{
	ctx.heartBeatPeriod = period;
}

unsigned userLedGetHeartBeatPeriod(void)
{
	return ctx.heartBeatPeriod;
}
