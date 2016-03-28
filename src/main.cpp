#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <BH1750.h>
#include <Adafruit_MPL115A2.h>
#include "sensors.hpp"

void printWeatherData();
bool isRaining(const int sensorPin);
float readTemperature(const int sensorPin);

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
BH1750 lightMeter;
Adafruit_MPL115A2 barometer;
TemperatureSensor temperatureSensor(0);
RainStatusSensor rainStatusSensor(2);

float temperature;
bool rainStatus;
int lightLevel;
float pressure;

void setup() {
	Serial.begin(9600);
	lcd.begin(20, 4);
	lightMeter.begin();
}

void loop() {
	temperature = temperatureSensor.readTemperature();
	rainStatus = rainStatusSensor.readRainStatus();
	lightLevel = lightMeter.readLightLevel();
	pressure = barometer.getPressure();

	printWeatherData();

	Serial.println(temperature);
	Serial.println(rainStatus);
	delay(1000);
}

void printWeatherData()
{
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
}
