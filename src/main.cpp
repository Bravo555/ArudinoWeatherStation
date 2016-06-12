#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Time.h>
#include <DS1307RTC.h>
#include "SensorManager.hpp"
#include "NetworkManager.hpp"
#include "EEPROM_BigData.hpp"

void screenPrinting();
void overviewPage();
void altitudeSet();
String getTime(tmElements_t);
void initButtons();
void getSensorData();

const int rightButtonPin = 4, leftButtonPin = 5, upButtonPin = 6, downButtonPin = 7, selectButtonPin = 8;
short int screenPage = 0;
short int screenPages = 3;
unsigned short updateFeedInterval = 5000;

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
SensorManager sensorManager;
NetworkManager networkManager;

float temperature;
unsigned short altitude;
bool rainStatus;
unsigned long lightLevel;
tmElements_t tm;
double pressure;

// timing
unsigned long prievous = 0;

void setup() {
	lcd.print("LOADING");

	lcd.begin(20, 4);
	sensorManager.init();
	initButtons();
	Serial.begin(9600);

	EEPROM_readAnything(0, altitude);
}

void loop() {
	getSensorData();
	screenPrinting();

	if(networkManager.isConnected())
	{
		unsigned long currentMillis = millis();
		if(currentMillis > prievous + updateFeedInterval) {
			networkManager.updateFeed("field1", String(temperature));
			networkManager.updateFeed("field3", String(pressure));
			networkManager.updateFeed("field4", String(lightLevel));

			prievous = currentMillis;
		}
	}

	delay(500);
}

void screenPrinting()
{
	lcd.clear();

	if(screenPage < screenPages - 1)
		if(digitalRead(rightButtonPin)==LOW)
			screenPage++;
	if(screenPage > 0)
		if(digitalRead(leftButtonPin)==LOW)
			screenPage--;

	switch(screenPage)
	{
		case 0:
			overviewPage();
		break;
		case 1:
			lcd.print("Status Wi-Fi:");
			lcd.setCursor(0, 1);
			if(!networkManager.isConnected()) {
				if(digitalRead(selectButtonPin) == LOW) {
					lcd.print("Laczenie...");
					lcd.print(networkManager.wifiConnect("Livebox-C28B", "lubieplacki11"));
					delay(10000);
				}
				else
					lcd.print("Brak polaczenia.");
			}
			else
				lcd.print("Polaczono z siecia!");

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
	lcd.print("Temp: ");
	lcd.print(temperature);
	lcd.print("C");

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

	if(digitalRead(selectButtonPin) == LOW)
		EEPROM_writeAnything(0, altitude);

	lcd.setCursor(0,0);
	lcd.print("Ustaw wysokosc");
	lcd.setCursor(0,1);
	lcd.print("nad poziomem morza");
	lcd.setCursor(0,2);
	lcd.print(altitude);
	lcd.setCursor(0, 3);
	lcd.print("SELECT - zapisz");
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
