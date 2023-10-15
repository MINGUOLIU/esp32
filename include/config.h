#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
// WiFi配置
#define WIFI_SSID "Redmi"        // WiFi名称
#define WIFI_PASSWORD "12345689" // WiFi密码


// 温度和湿度传感器配置
#define DHT_PIN D5 // DHT传感器数据线连接的引脚  d1

// 土壤湿度传感器配置
#define SOIL_PIN A0         // 土壤湿度传感器数据线连接的引脚 a0
#define SOIL_DRY_VALUE 0    // 土壤干燥时的ADC值
#define SOIL_WET_VALUE 1023 // 土壤湿润时的ADC值
#define SOIL_THRESHOLD 500  // 土壤湿度阈值

// 水泵配置
#define PUMP_PIN D7       // 水泵电机控制引脚      D3
#define PUMP_ON_TIME 5000 // 水泵开启的时间，单位为毫秒

// OLED屏幕配置
#define OLED_ADDR 0x3c // OLED屏幕I2C地址
#define OLED_SDA D2    // OLED屏幕I2C数据线连接的引脚
#define OLED_SCL D1    // OLED屏幕I2C时钟线连接的引脚   d1
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_I2C_ADDRESS 0x3C
#define OLED_RESET_PIN -1

// 程序配置
#define TEMP_THRESHOLD 30.0 // 温度阈值
#define HUMI_THRESHOLD 60.0 // 湿度阈值

#endif
