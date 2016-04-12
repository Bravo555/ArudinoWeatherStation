#include <Arduino.h>
#include "pages.hpp"

void setup() {
	Serial.begin(9600);
	lcd.begin(20, 4);
	lightMeter.begin();
	pinMode(rightButtonPin, INPUT_PULLUP);
	pinMode(leftButtonPin, INPUT_PULLUP);
}

void loop() {
	getSensorData();
	screenPrinting();

	Serial.println(temperature);
	Serial.println(rainStatus);
	delay(1000);
}
