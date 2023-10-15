#ifndef SENSORS_H
#define SENSORS_H

#include "config.h"
#include <DHT.h>

class Sensors
{
public:
    Sensors();
    void begin();
    float readTemperature();
    float readHumidity();
    int readSoilMoisture();

private:
    DHT dht;
};

#endif
