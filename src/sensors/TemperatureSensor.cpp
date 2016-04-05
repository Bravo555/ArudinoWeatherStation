#include <Arduino.h>
#include "TemperatureSensor.hpp"

TemperatureSensor::TemperatureSensor(int sensorPin)
{
	this->sensorPin = sensorPin;
}

float TemperatureSensor::readTemperature()
{
	float temperatura = analogRead(sensorPin) / 1024.0 * 500;
	return temperatura - 277;
}
