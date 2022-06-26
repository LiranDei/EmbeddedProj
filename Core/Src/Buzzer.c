#include "Buzzer.h"

#define SIZE 12
#define MUSIC_SIZE 49
static int press = 0;
int freq[SIZE] ={381,361,341,321,301,281,261,241,221,201,181,161};

Byte music[MUSIC_SIZE] = { {Re*2, 2500}, {Si, 2500}, {Si, 5000}, {DO *2, 2500},
							{La, 2500}, {La, 5000}, {Sol, 2500}, {La, 2500},
							{Si, 2500}, {DO*2, 2500}, {Re*2, 2500}, {Re*2, 2500},
							{Re*2, 5000}, {Re*2, 2500}, {Si, 2500}, {Si, 5000},
							{DO*2, 2500}, {La, 2500}, {La,5000}, {Sol,2500},
							{Si, 2500}, {Re*2, 2500}, {Re*2,2500}, {Sol, 5000},
							{La, 2500}, {La, 2500}, {La, 2500}, {La, 2500},
							{La, 2500}, {Si, 2500}, {DO*2, 5000},{Si, 2500},
							{Si, 2500}, {Si, 2500}, {Si, 2500}, {Si, 2500},
							{DO*2, 2500}, {Re*2, 5000}, {Re*2, 2500}, {Si,2500},
							{Si, 5000}, {DO*2, 2500}, {La, 2500}, {La, 5000},
							{Sol, 2500},{Si, 2500}, {Re*2, 2500}, {Re*2, 2500},
							{Sol, 5000}};

static int index = 0;

void changeFreq (TIM_HandleTypeDef * htim3, TIM_HandleTypeDef * htim6)
{

	index = (index+1) % MUSIC_SIZE;
	__HAL_TIM_SET_COUNTER(htim3, 0);
	__HAL_TIM_SET_AUTORELOAD(htim3, music[index].note);
	__HAL_TIM_SET_COMPARE(htim3, TIM_CHANNEL_1, (music[index].note)/2 );
	__HAL_TIM_SET_AUTORELOAD(htim6, music[index].period);

}

void onOffMusic(TIM_HandleTypeDef * htim3)
{
	if(!press)
		{
			HAL_TIM_Base_Start(htim3);
			HAL_TIM_PWM_Start(htim3, TIM_CHANNEL_1);
			HAL_NVIC_EnableIRQ(TIM3_IRQn);
		}
		else
		{
			HAL_TIM_Base_Stop(htim3);
			HAL_TIM_PWM_Stop(htim3, TIM_CHANNEL_1);
		}
	press = (press+1)%2;

}



