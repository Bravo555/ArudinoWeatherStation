#include <BH1750.h>
#include <SFE_BMP180.h>
#include "sensors/RainStatusSensor.hpp"

class SensorManager {
public:
    void init();

    double getTemperature();
    bool getRainStatus();
    unsigned long getLightLevel();
    double getPressure(float altitude);

private:
    BH1750 lightMeter;
    SFE_BMP180 barometer;
    RainStatusSensor rainStatusSensor = RainStatusSensor(2);
};
