#include <BH1750.h>
#include <SFE_BMP180.h>
#include "sensors/TemperatureSensor.hpp"
#include "sensors/RainStatusSensor.hpp"

class SensorManager {
public:
    void init();

    float getTemperature();
    bool getRainStatus();
    unsigned long getLightLevel();
    double getPressure(float altitude);

private:
    BH1750 lightMeter;
    SFE_BMP180 barometer;
    TemperatureSensor temperatureSensor = TemperatureSensor(1);
    RainStatusSensor rainStatusSensor = RainStatusSensor(2);
};
