/*
 * Sensor.c
 *
 *  Created on: Jun 28, 2022
 *      Author: student
 */
#include "Sensor.h"


void lightSensorInit(LIGHT_SENSOR* lightSensor,ADC_HandleTypeDef* light)
{
	lightSensor->light = light;
	lightSensor->maxLightValue = MAX_LIGHT_VAlUE;
	lightSensor->maxLedValue = MAX_LED_VALUE;
}

void calcLedValue(LIGHT_SENSOR* lightSensor)
{
	int lightValue = HAL_ADC_GetValue(lightSensor->light);
	lightSensor->ledValue = (MAX_LED_VALUE * lightValue + (MAX_LIGHT_VAlUE/2))/MAX_LIGHT_VAlUE;

}
