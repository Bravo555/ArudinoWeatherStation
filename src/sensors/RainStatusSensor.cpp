#include <Arduino.h>
#include "RainStatusSensor.hpp"

RainStatusSensor::RainStatusSensor(int sensorPin)
{
	this->sensorPin = sensorPin;
}

bool RainStatusSensor::readRainStatus() {
	return analogRead(sensorPin) < 400;
}
