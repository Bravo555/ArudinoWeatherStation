class RainStatusSensor {
public:
	RainStatusSensor(int sensorPin);
	bool readRainStatus();

private:
	int sensorPin;
};
