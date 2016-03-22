#include <Arduino.h>

bool isRaining();
float readTemperature();

const int temperatureSensorPin = 0;
const int rainSensorPin = 2;

void setup() {
	Serial.begin(9600);
}

void loop() {
	Serial.println(readTemperature());
	Serial.println(isRaining());
	delay(1000);
}

bool isRaining() {
	return analogRead(rainSensorPin) < 400;
}

float readTemperature() {
	float temperatura = analogRead(temperatureSensorPin) / 1024.0 * 500;
	return temperatura - 277;
}
