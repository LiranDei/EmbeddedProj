/*
 * Led.h
 *
 *  Created on: Jun 14, 2022
 *      Author: student
 */
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "main.h"

#define MAX_BUFFER_LENGTH 100
#define START_PERIOD 10
typedef enum _led_STATE
{
	STATE_OFF,
	STATE_ON,
	STATE_BRIGHTNESS,
	STATE_BLINKING
}LED_STATE;

typedef struct _led
{
	LED_STATE state;
	GPIO_TypeDef* GPIOx;
	uint16_t GPIO_Pin;
	int counter;
	int period;

}LED;

typedef struct _btn
{
	GPIO_TypeDef* GPIOx;
	uint16_t GPIO_Pin;
	int firstTick;
	int secondTick;
}BTN;

void ledInit(LED*, GPIO_TypeDef*, uint16_t);
void ledOn(LED* );
void ledOff(LED* );
void ledBlink(LED*, int );
void ledOnTimerInterrupt(LED*);
void ledOnPeriodicTask(LED*);
void handleCommand();
int commTask(UART_HandleTypeDef*);
void myMain(UART_HandleTypeDef* );


