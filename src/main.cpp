#include <Arduino.h>
#include "pages.hpp"

void setup() {
	Serial.begin(9600);
	lcd.begin(20, 4);
	barometer.begin();
	lightMeter.begin();
	pinMode(rightButtonPin, INPUT_PULLUP);
	pinMode(leftButtonPin, INPUT_PULLUP);
}

void loop() {
	getSensorData();
	screenPrinting();

	delay(1000);
}
