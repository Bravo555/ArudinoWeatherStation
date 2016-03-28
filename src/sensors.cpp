#include <Arduino.h>
#include "sensors.hpp"

TemperatureSensor::TemperatureSensor(int sensorPin)
{
	this->sensorPin = sensorPin;
}

float TemperatureSensor::readTemperature()
{
	float temperatura = analogRead(sensorPin) / 1024.0 * 500;
	return temperatura - 277;
}

RainStatusSensor::RainStatusSensor(int sensorPin)
{
	this->sensorPin = sensorPin;
}

bool RainStatusSensor::readRainStatus() {
	return analogRead(sensorPin) < 400;
}
