#include <Arduino.h>
#include "pages.hpp"

void setup() {
	initSensors();
	pinMode(rightButtonPin, INPUT_PULLUP);
	pinMode(leftButtonPin, INPUT_PULLUP);
}

void loop() {
	getSensorData();
	screenPrinting();

	delay(1000);
}
