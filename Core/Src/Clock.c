/*
 * Qlock.c
 *
 *  Created on: Jun 21, 2022
 *      Author: student
 */

#include <Clock.h>

void clockInit (CLOCK* clock)
{
	clock->ms = 0;
	clock->sec = 0;
	clock->min = 0;
	clock->hour = 0;
}

void increaseQlock(CLOCK* clock)
{
	if(clock->ms >= MSECS_TO_SEC)
	{
		clock->ms = 0;
		clock->sec++;
	}
	if(clock->sec >= SECS_IN_MIN)
	{
		clock->sec = 0;
		clock->min++;
	}
	if(clock->min >= MINS_IN_HOUR)
	{
		clock->min = 0;
		clock->hour++;
	}

}

void clockOnInterrupt(CLOCK* clock)
{
	clock->ms++;
	increaseQlock(clock);

}

void printTime(CLOCK* clock)
{
	printf("%d:%d:%d\n\r",clock->hour,clock->min, clock->sec);
}
