#ifndef DISPLAY_H
#define DISPLAY_H

#include "config.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class OLED
{
private:
    int sdaPin;
    int sclPin;
    Adafruit_SSD1306 display;

public:
    OLED(int sdaPin, int sclPin);
    void init();
    void showWatering();
    void showWater(float water);
    void showHumidity(float humidity);
    void showTemperature(float temperature);
};
#endif
