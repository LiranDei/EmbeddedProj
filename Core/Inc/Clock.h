/*
 * Qlock.h
 *
 *  Created on: Jun 21, 2022
 *      Author: student
 */
#include <stdint.h>
#include <stdio.h>
#include "main.h"
#define MSECS_TO_SEC 1000
#define SECS_IN_MIN 60
#define MINS_IN_HOUR 60
#define HOURS_IN_DAY 24

typedef struct _qlock
{
	int ms;
	uint8_t sec;
	uint8_t min;
	uint8_t hour;

}CLOCK;

void clockInit (CLOCK*);
void increaseQlock(CLOCK*);
void clockOnInterrupt(CLOCK*);
void printTime(CLOCK*);

