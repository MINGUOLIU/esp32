#include "pump.h"
#include "config.h"

Pump::Pump() {}

void Pump::begin()
{
    pinMode(PUMP_PIN, OUTPUT);
    digitalWrite(PUMP_PIN, LOW);
    _isOn = false;
}

void Pump::on()
{

    digitalWrite(PUMP_PIN, HIGH);
    Serial.print("switch_on");
    _isOn = true;
}

void Pump::off()
{
    digitalWrite(PUMP_PIN, LOW);
    Serial.print("switch_off");
    _isOn = false;
}
