#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <BH1750.h>
#include "sensors/TemperatureSensor.hpp"
#include "sensors/RainStatusSensor.hpp"
#include <Time.h>
#include <DS1307RTC.h>
#include <SFE_BMP180.h>

void screenPrinting();
void overviewPage();
int altitudeSet();
String getTime(tmElements_t);
void initSensors();
void initButtons();
void getSensorData();

const int rightButtonPin = 4, leftButtonPin = 5, upButtonPin = 6, downButtonPin = 7, selectButtonPin = 8;
short int screenPage = 0;

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
BH1750 lightMeter;
SFE_BMP180 barometer;
TemperatureSensor temperatureSensor(1);
RainStatusSensor rainStatusSensor(2);

float temperature, altitude = 200;
bool rainStatus;
unsigned long lightLevel;
tmElements_t tm;
double pressure;

void setup() {
	lcd.print("LOADING");

	lcd.begin(20, 4);
	initSensors();
	initButtons();
}

void loop() {
	getSensorData();
	screenPrinting();

	delay(1000);
}

void screenPrinting()
{
	lcd.clear();

	if(digitalRead(rightButtonPin)==LOW)
		screenPage++;
	if(digitalRead(leftButtonPin)==LOW)
		screenPage--;

	switch(screenPage)
	{
		case 0:
			overviewPage();
		break;
		case 1:

		break;
		case 2:
			altitudeSet();
		break;
	}
}

void overviewPage()
{
	lcd.home();

	lcd.print(getTime(tm));

	lcd.setCursor(0,1);
	lcd.print(temperature);

	lcd.setCursor(0, 2);
	lcd.print("Swiatlo: ");
	lcd.print(lightLevel);
	lcd.print(" lx");

	lcd.setCursor(0, 3);
	lcd.print("Cisn: ");
	lcd.print(pressure);
	lcd.print("hPa");
}

int altitudeSet()
{
	lcd.setCursor(0,0);
	lcd.print("USTAW WYSOKOSC");
	lcd.setCursor(0, 1);
	lcd.print("BEZWZGLEDNA:");
	lcd.print(altitude);

	if(digitalRead(selectButtonPin) == LOW)
	{
		while(digitalRead(selectButtonPin) != LOW)
		{
			if(digitalRead(upButtonPin) == LOW)
				altitude += 10;
			if(digitalRead(downButtonPin) == LOW)
				altitude -= 10;
		}
	}
}

String getTime(tmElements_t tm)
{
	String hour, min, sec;

	RTC.read(tm);
	if(tm.Hour < 10)
		hour = "0" + String(tm.Hour);
	else
		hour = String(tm.Hour);

	if(tm.Minute < 10)
		min = "0" + String(tm.Minute);
	else
		min = String(tm.Minute);

	if(tm.Second < 10)
		sec = "0" + String(tm.Second);
	else
		sec = String(tm.Second);

	return hour + ":" + min + ":" + sec;
}

double getPressure(float altitude);

void getSensorData()
{
	temperature = temperatureSensor.readTemperature();
	rainStatus = rainStatusSensor.readRainStatus();
	lightLevel = lightMeter.readLightLevel();
	pressure = getPressure(altitude);	// wysokość zhardcode'owana dla Nowej Rudy, DO ZMIANY!
}

void initSensors()
{
	barometer.begin();
	lightMeter.begin();
}

double getPressure(float altitude)
{
	char status;
	double temperature, pressure;

	status = barometer.startTemperature();
	if (status != 0)
    {
    	delay(status);

		status = barometer.getTemperature(temperature);
		if(status != 0)
		{
			delay(status);

			status = barometer.startPressure(3);
			if(status != 0)
			{
				delay(status);

				status = barometer.getPressure(pressure, temperature);
				if(status != 0)
					return barometer.sealevel(pressure, altitude);
			}
		}
	}
	return 0;
}

void initButtons()
{
	pinMode(rightButtonPin, INPUT_PULLUP);
	pinMode(leftButtonPin, INPUT_PULLUP);
	pinMode(upButtonPin, INPUT_PULLUP);
	pinMode(downButtonPin, INPUT_PULLUP);
	pinMode(selectButtonPin, INPUT_PULLUP);
}
