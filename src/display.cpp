#include "display.h"
#include "config.h"

OLED::OLED(int sdaPin, int sclPin) : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1)
{
    this->sdaPin = sdaPin;
    this->sclPin = sclPin;
}

void OLED::init()
{
    Wire.begin(sdaPin, sclPin);

    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;)
            ;
    }

    display.clearDisplay();
    display.display();
    display.setTextSize(1, 2);
    display.setTextColor(WHITE);
}

void OLED::showWatering()
{
    // display.clearDisplay();
    display.setCursor(20, 20);
    display.print("Watering...");
    display.display();
}

void OLED::showHumidity(float humidity)
{
    // display.clearDisplay();
    display.setCursor(10, 20);
    display.print("Humidity:");
    display.print(humidity);
    display.print("%");
    display.display();
}

void OLED::showWater(float water)
{
    // display.clearDisplay();
    display.setCursor(10, 40);
    display.print("Water:");
    display.print(water);
    display.print("%");
    display.display();
}

void OLED::showTemperature(float temperature)
{
    display.clearDisplay();
    display.setCursor(10, 0);
    display.print("Temperature:");
    // display.setCursor(80, 20);
    display.print(temperature);
    display.print("C");
    display.display();
}
