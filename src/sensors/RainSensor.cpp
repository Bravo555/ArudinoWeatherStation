#include <Arduino.h>
#include "RainSensor.hpp"

RainSensor::RainSensor(short sensorPin)
{
	this->sensorPin = sensorPin;
}

float RainSensor::readRainHeight()
{
	float height = map(analogRead(sensorPin), 266, 385, 5, 48);
	if(height > 0)
		return height;
	else
		return 0;
}
