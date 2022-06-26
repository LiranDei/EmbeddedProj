/*
 * CommTask.h
 *
 *  Created on: Jun 21, 2022
 *      Author: student
 */

#include <stdint.h>
#include <string.h>
#include "main.h"

#define BOUNCE_TIME_WAIT 20

typedef enum _bouncing_wait
{
	OFF,
	ON
}BOUNCING_WAIT;

typedef enum _btn_state
{
	WAITING_FIRST_CLICK,
	WAITING_FOR_RELEASE,
	WAITING_FOR_DOUBLE,
	WAITING_FOR_LONG_PRESS
}BTN_STATE;

typedef struct BTN_CLICK
{
	GPIO_TypeDef* GPIOx;
	uint16_t GPIO_Pin;
	BTN_STATE status;
	BOUNCING_WAIT noiseWait;
	int firstClick;
	int secondClick;
	int bounceCounter;
	int counter;
}BTN_CLICK;

void myMain(UART_HandleTypeDef*);
void onClickInterrupt(uint16_t GPIO_Pin);
void handleClicks();
void initBtnClicks(BTN_CLICK*, GPIO_TypeDef*, uint16_t);
