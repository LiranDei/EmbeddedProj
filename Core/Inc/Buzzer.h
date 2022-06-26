/*
 * Buzzer.h
 *
 *  Created on: Jun 19, 2022
 *      Author: student
 */
#include "main.h"

typedef enum frequency_
{
	DO = 381,
	DOs = 361,
	Re = 341,
	Rs = 321,
	Mi = 301,
	Fa = 281,
	Fs = 261,
	Sol = 241,
	Sols = 221,
	La = 201,
	Las = 181,
	Si = 161
}frequency;

typedef struct byte
{
	frequency note;
	int period;

}Byte;

void changeFreq (TIM_HandleTypeDef *, TIM_HandleTypeDef *);
void onOffMusic(TIM_HandleTypeDef * );
