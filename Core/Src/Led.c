/*
 * Led.c
 *
 *  Created on: Jun 14, 2022
 *      Author: student
 */

#include "Led.h"
#include "Sensor.h"

LED* ledRed;
LED* ledBlue;
uint8_t ch;
uint8_t cmdbuffer[MAX_BUFFER_LENGTH];
int cmdcount = 0;
TIM_HandleTypeDef* htimFour;
LIGHT_SENSOR* lightSensor;

void htimInit(TIM_HandleTypeDef* htim4)
{
	htimFour = htim4;
}


void ledInit(LED* led, GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	led->state = STATE_OFF;
	led->GPIOx = GPIOx;
	led->GPIO_Pin = GPIO_Pin;
	led->counter = 0;
	led->period = START_PERIOD;
	if(led->GPIO_Pin == RedLed_Pin)
	{
		ledRed = led;
	}
	else
	{
		ledBlue = led;
	}
}


void ledOn(LED* led)
{
	led->state = STATE_ON;
	HAL_GPIO_WritePin(led->GPIOx, led->GPIO_Pin, 1);
}

void ledOff(LED* led)
{
	led->state = STATE_OFF;
	HAL_GPIO_WritePin(led->GPIOx, led->GPIO_Pin, 0);
}

void ledBlink(LED* led, int period)
{
	led->state = STATE_BLINKING;
	led->period = period;
	led->counter = 0;
}

void ledOnTimerInterrupt(LED* led)
{
	if(led->state == STATE_BLINKING && led->counter == led->period)
	{
		HAL_GPIO_TogglePin(led->GPIOx, led->GPIO_Pin);
		led->counter = 0;
	}

	else
	{
		led ->counter++;

	}

}

void setBrightness (LED* led, int brightness)
{
	led->state = STATE_BRIGHTNESS;
	HAL_TIM_Base_Start_IT(htimFour);
	HAL_TIM_PWM_Start_IT(htimFour,TIM_CHANNEL_1);
	__HAL_TIM_SET_COMPARE(htimFour,TIM_CHANNEL_1, brightness);
}

void ledOnPeriodicTask(LED* led)
{

}

int commTask(UART_HandleTypeDef* huart2)
{
	HAL_StatusTypeDef Status = HAL_UART_Receive(huart2, &ch, 1, 0);
	if (Status != HAL_OK) {
		return 0;
	}
	if (ch != '\r' && ch != '\n')
	{
		HAL_UART_Transmit(huart2, &ch, 1, 0xFFFF);

		if (cmdcount >= MAX_BUFFER_LENGTH)
		{
			cmdcount = 0;
		}

		cmdbuffer[cmdcount++] = ch;
		return 0;
	}
	HAL_UART_Transmit(huart2, (uint8_t*)"\r\n", 2, 0xFFFF);

	cmdbuffer[cmdcount] = 0;
	cmdcount = 0;
	return 1;
}

void handleCommand()
{
	char cmd[20];
	//sscanf((const char*)cmdbuffer, "%s", cmd);
	char* tokens;
	tokens = strtok(cmdbuffer,"  \r");
	strcpy(cmd,tokens);
	HAL_TIM_Base_Stop_IT(htimFour);
	HAL_TIM_PWM_Stop_IT(htimFour,TIM_CHANNEL_1);

	if (strcmp(cmd, "full") == 0)
	{
		ledOn(ledRed);
		ledOn(ledBlue);
	}
	else if (strcmp(cmd, "half") == 0)
	{
		tokens = strtok(NULL, "  \r");
		strcpy(cmd,tokens);
		int value;
		strcpy(cmd,tokens);
		value = (int)atoi((const)cmd);
		setBrightness(ledBlue, value);
	}
	else if (strcmp(cmd, "blink") == 0)
	{
		ledBlink(ledRed, 700);
		ledBlink(ledBlue, 300);
	}
	else if(strcmp(cmd, "off") == 0)
	{
		ledOff(ledRed);
		ledOff(ledBlue);
	}
	else if(strcmp(cmd, "set") == 0)
	{
		tokens = strtok(NULL, "  \r");
	    strcpy(cmd,tokens);

		int value;
		strcpy(cmd,tokens);
		value = (int)atoi((const)cmd);
		ledBlink(ledBlue, value);
		ledBlink(ledRed, value);
	}
	else
	{
		printf("Invalid command\r\n");
	}
}
void myMain(UART_HandleTypeDef* huart2)
{
	if (commTask(huart2))
	{
		handleCommand();
	}
}


