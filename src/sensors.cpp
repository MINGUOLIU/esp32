#include "sensors.h"
#include "config.h"
#include <Wire.h>

Sensors::Sensors() : dht(DHT_PIN, DHT11) {}

void Sensors::begin()
{
    dht.begin();
}

float Sensors::readTemperature()
{
    return dht.readTemperature();
}

float Sensors::readHumidity()
{
    return dht.readHumidity();
}

int Sensors::readSoilMoisture()
{
    int value = analogRead(SOIL_PIN);
    Serial.println(value);
    int moisture = map(value, SOIL_DRY_VALUE, SOIL_WET_VALUE, 100, 0);
    moisture = constrain(moisture, 0, 100);
    return moisture;
}
