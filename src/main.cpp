#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <BH1750.h>
#include <Adafruit_MPL115A2.h>

bool isRaining(const int sensorPin);
float readTemperature(const int sensorPin);

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
BH1750 lightMeter;
Adafruit_MPL115A2 barometer;
const int temperatureSensorPin = 0;
const int rainSensorPin = 2;

void setup() {
	Serial.begin(9600);
	lcd.begin(20, 4);
	lightMeter.begin();
}

void loop() {
	float temperature = readTemperature(temperatureSensorPin);
	bool rainStatus = isRaining(rainSensorPin);
	int lightLevel = lightMeter.readLightLevel();
	float pressure = barometer.getPressure();

	lcd.home();

	lcd.print("Temperature: ");
	lcd.print(temperature);

	lcd.setCursor(0, 1);
	lcd.print("Is raining: ");
	lcd.print(rainStatus ? "yes" : "no");

	lcd.setCursor(0, 2);
	lcd.print("Light: ");
	lcd.print(lightLevel);
	lcd.print("lx");

	lcd.setCursor(0, 3);
	lcd.print("Pressure: ");
	lcd.print(pressure);
	lcd.print("kPa");

	Serial.println(temperature);
	Serial.println(rainStatus);
	delay(1000);
}

bool isRaining(const int sensorPin) {
	return analogRead(sensorPin) < 400;
}

float readTemperature(const int sensorPin) {
	float temperatura = analogRead(sensorPin) / 1024.0 * 500;
	return temperatura - 277;
}
