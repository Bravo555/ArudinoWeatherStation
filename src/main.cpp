#include <Arduino.h>

bool isRaining(const int sensorPin);
float readTemperature(const int sensorPin);

const int temperatureSensorPin = 0;
const int rainSensorPin = 2;

void setup() {
	Serial.begin(9600);
}

void loop() {
	Serial.println(readTemperature(temperatureSensorPin));
	Serial.println(isRaining(rainSensorPin));
	delay(1000);
}

bool isRaining(const int sensorPin) {
	return analogRead(sensorPin) < 400;
}

float readTemperature(const int sensorPin) {
	float temperatura = analogRead(sensorPin) / 1024.0 * 500;
	return temperatura - 277;
}
