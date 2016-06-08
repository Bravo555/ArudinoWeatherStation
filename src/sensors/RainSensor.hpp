class RainSensor {
public:
	RainSensor(short sensorPin);

	float readRainHeight();

private:
	short sensorPin;
};
