#include <Arduino.h>
#include "pages.hpp"

void setup() {
	Serial.begin(9600);
	lcd.begin(20, 4);
	lightMeter.begin();
}

void loop() {
	getSensorData();
	overviewPage();

	Serial.println(temperature);
	Serial.println(rainStatus);
	delay(1000);
}
