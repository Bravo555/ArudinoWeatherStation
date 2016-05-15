#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <BH1750.h>
#include "sensors/TemperatureSensor.hpp"
#include "sensors/RainStatusSensor.hpp"
#include <Time.h>
#include <DS1307RTC.h>
#include <SFE_BMP180.h>

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
BH1750 lightMeter;
SFE_BMP180 barometer;
TemperatureSensor temperatureSensor(0);
RainStatusSensor rainStatusSensor(2);

float temperature;
bool rainStatus;
unsigned long lightLevel;
tmElements_t tm;
double pressure;

double getPressure(float altitude);

void getSensorData()
{
	temperature = temperatureSensor.readTemperature();
	rainStatus = rainStatusSensor.readRainStatus();
	lightLevel = lightMeter.readLightLevel();
	pressure = getPressure(406.776);	// wysokość zhardcode'owana dla Nowej Rudy, DO ZMIANY!
}

void initSensors()
{
	Serial.begin(9600);
	lcd.begin(20, 4);
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
