/*
 * Sensor.h
 *
 *  Created on: Jun 28, 2022
 *      Author: student
 */
#include "main.h"

#define MAX_LIGHT_VAlUE 4095
#define MAX_LED_VALUE 10


typedef struct _sensor
{
	ADC_HandleTypeDef* light;
	int maxLightValue;
	int lightValue;
	int maxLedValue;
	int ledValue;
}LIGHT_SENSOR;

void lightSensorInit(LIGHT_SENSOR* ,ADC_HandleTypeDef*);
void calcLedValue(LIGHT_SENSOR*);
