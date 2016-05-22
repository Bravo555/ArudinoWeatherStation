#include <Arduino.h>
#include "pages.hpp"

void setup() {
	lcd.setCursor(0,0);
	lcd.print("LOADING");
	initSensors();
	pinMode(rightButtonPin, INPUT_PULLUP);
	pinMode(leftButtonPin, INPUT_PULLUP);
	pinMode(upButtonPin, INPUT_PULLUP);
	pinMode(downButtonPin, INPUT_PULLUP);
	pinMode(selectButtonPin, INPUT_PULLUP);
}

void loop() {
	getSensorData();
	screenPrinting();

	delay(1000);
}
