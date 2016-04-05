class TemperatureSensor {
public:
	TemperatureSensor(int sensorPin);
	float readTemperature();

private:
	int sensorPin;
};
