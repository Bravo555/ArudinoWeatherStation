#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <BH1750.h>
#include "sensors/RainStatusSensor.hpp"
#include "sensors/RainSensor.hpp"
#include <Time.h>
#include <DS1307RTC.h>
#include <SFE_BMP180.h>

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
BH1750 lightMeter;
SFE_BMP180 barometer;
RainStatusSensor rainStatusSensor(0);
RainSensor rainSensor(2);

float temperature, altitude = 405;
bool rainStatus;
unsigned long lightLevel;
tmElements_t tm;
double pressure;
short rainHeight;

double getPressure(float altitude);
double getTemperature();

void getSensorData()
{
	temperature = getTemperature();
	rainStatus = rainStatusSensor.readRainStatus();
	lightLevel = lightMeter.readLightLevel();
	pressure = getPressure(altitude);
	rainHeight = rainSensor.readRainHeight();
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

double getTemperature()
{
	double T;
    int pause;
    pause = barometer.startTemperature();
    delay(pause);
    barometer.getTemperature(T);
    return T;
}
