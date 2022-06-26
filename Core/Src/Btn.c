/*
 * CommTask.c
 *
 *  Created on: Jun 21, 2022
 *      Author: student
 */
#include <Btn.h>
#include <stdio.h>

BTN_CLICK* btn;


void initBtnClicks(BTN_CLICK* btnClick, GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	btnClick->GPIOx = GPIOx;
	btnClick->GPIO_Pin = GPIO_Pin;
	btnClick->noiseWait = OFF;
	btnClick->status = WAITING_FIRST_CLICK;
	btnClick->counter = 0;
	btnClick->bounceCounter = 0;
	btn = btnClick;
}

void onClickInterrupt(uint16_t GPIO_Pin)
{
	if(!(HAL_GPIO_ReadPin(btn->GPIOx, btn->GPIO_Pin)))
	{
		if(btn->status == WAITING_FIRST_CLICK || btn->status == WAITING_FOR_LONG_PRESS)
		{
			btn->firstClick = HAL_GetTick();
			btn->status = WAITING_FOR_RELEASE;
			btn->counter = 0;
		}
		else if(btn->status == WAITING_FOR_DOUBLE)
		{
			btn->counter = 0;
			printf("was double click\n\r");
			btn->status = WAITING_FOR_LONG_PRESS;
		}
	}
	else
	{
		if(btn->status == WAITING_FOR_RELEASE)
		{
			btn->secondClick = HAL_GetTick();
			btn->counter = 0;
			btn->status = WAITING_FOR_DOUBLE;
		}
		else if(btn->status == WAITING_FOR_LONG_PRESS)
		{
			btn->status = WAITING_FIRST_CLICK;
		}

	}

}

void handleClicks()
{
	if(btn->noiseWait == ON)
	{
		btn->bounceCounter++;
		if(btn->bounceCounter >= BOUNCE_TIME_WAIT)
		{
			btn->noiseWait = OFF;
			btn->bounceCounter = 0;
			onClickInterrupt(btn->GPIO_Pin);
		}

	}
	else
	{
		if(btn->status != WAITING_FIRST_CLICK)
		{
			btn->counter++;
		}
		switch(btn->status)
		{

		case WAITING_FOR_RELEASE:
			if(btn->counter > 1000)
			{
			btn->status = WAITING_FOR_LONG_PRESS;
			}
			break;

		case WAITING_FOR_DOUBLE:
			if(btn->counter > 200)//wasnt double click
			{
				btn->status = WAITING_FIRST_CLICK;
				btn->counter = 0;
				if(btn->secondClick - btn->firstClick < 500)
				{
					printf("Thats was short<%d>\n\r", btn->secondClick - btn->firstClick);
				}
				else
				{
					printf("Thats was long<%d>\n\r", btn->secondClick - btn->firstClick);
				}
			}
			break;

		case WAITING_FOR_LONG_PRESS:
			if(btn->status == WAITING_FOR_LONG_PRESS)
			{
				if(btn->counter > 1000)
				{
					printf("long\n\r");
				}
			}
			break;

		}
	}
}


