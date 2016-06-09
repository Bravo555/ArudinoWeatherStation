#include "SensorManager.hpp"

void SensorManager::init()
{
	barometer.begin();
	lightMeter.begin();
}

double SensorManager::getTemperature()
{
	double T;
    int pause;
    pause = barometer.startTemperature();
    delay(pause);
    barometer.getTemperature(T);
    return T;
}

bool SensorManager::getRainStatus()
{
	return rainStatusSensor.readRainStatus();
}

unsigned long SensorManager::getLightLevel()
{
	return lightMeter.readLightLevel();
}

double SensorManager::getPressure(float altitude)
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
