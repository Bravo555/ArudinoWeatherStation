#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Time.h>
#include <DS1307RTC.h>
#include "SensorManager.hpp"

void screenPrinting();
void overviewPage();
void altitudeSet();
String getTime(tmElements_t);
void initButtons();
void getSensorData();

const int rightButtonPin = 4, leftButtonPin = 5, upButtonPin = 6, downButtonPin = 7, selectButtonPin = 8;
short int screenPage = 0;

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
SensorManager sensorManager;

float temperature, altitude = 405;
bool rainStatus;
unsigned long lightLevel;
tmElements_t tm;
double pressure;

void setup() {
	lcd.print("LOADING");

	lcd.begin(20, 4);
	sensorManager.init();
	initButtons();
}

void loop() {
	getSensorData();
	screenPrinting();

	delay(250);
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

void altitudeSet()
{
	if(digitalRead(upButtonPin)==LOW)
		altitude += 10;
	if(digitalRead(downButtonPin)==LOW)
		altitude -= 10;

	lcd.setCursor(0,0);
	lcd.print("Ustaw wysokosc");
	lcd.setCursor(0,1);
	lcd.print("nad poziomem morza");
	lcd.setCursor(0,2);
	lcd.print(altitude);
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
	temperature = sensorManager.getTemperature();
	rainStatus = sensorManager.getRainStatus();
	lightLevel = sensorManager.getLightLevel();
	pressure = sensorManager.getPressure(altitude);
}

void initButtons()
{
	pinMode(rightButtonPin, INPUT_PULLUP);
	pinMode(leftButtonPin, INPUT_PULLUP);
	pinMode(upButtonPin, INPUT_PULLUP);
	pinMode(downButtonPin, INPUT_PULLUP);
	pinMode(selectButtonPin, INPUT_PULLUP);
}
