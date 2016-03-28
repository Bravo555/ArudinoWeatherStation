class TemperatureSensor {
public:
	TemperatureSensor(int sensorPin);
	float readTemperature();

private:
	int sensorPin;
};

class RainStatusSensor {
public:
	RainStatusSensor(int sensorPin);
	bool readRainStatus();

private:
	int sensorPin;
};
