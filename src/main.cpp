#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include "config.h"
#include "sensors.h"
#include "pump.h"
#include "display.h"
#include "mqtt.h"
// #define MQTT_PORT 1883

// WiFi credentials
// const char *ssid = "liliyuanshangpu";
// const char *password = "4561518zxc";

const char *ssid = "Redmi";
const char *password = "12345689";

// MQTT credentials
// const char *mqtt_clientId = "i8hcFausTAJ.flower1|securemode=2,signmethod=hmacsha256,timestamp=1680423719388|";
// const char *mqtt_username = "flower1&i8hcFausTAJ";
// const char *mqtt_password = "6b4c2324886d4788f34e305588e1d46e1cfdb8c5434e05958cdeb7db0f76a45d";
const char *mqtt_server = "iot-06z00gn950f64ah.mqtt.iothub.aliyuncs.com";

const char *mqtt_clientId = "i8hcFausTAJ.flower2|securemode=2,signmethod=hmacsha256,timestamp=1681626793739|";
const char *mqtt_username = "flower2&i8hcFausTAJ";
const char *mqtt_password = "bce24d579a5e3fb66c58836dba673107d4eefb26cdb2828c1807c841f5fe18c1";

// MQTT topics

// const char *message_topic = "flowers/message";
const char *post_topic = "/sys/i8hcFausTAJ/flower2/thing/event/property/post";
const char *set_topic = "/i8hcFausTAJ/flower2/user/switch4";
const char *_server = "/sys/i8hcFausTAJ/flower2/thing/service/switch2";

// Sensors
Sensors sensors;

// Pump
Pump pump;

// MQTT
MQTT mqtt;

// Display
OLED display(OLED_SDA, OLED_SCL);

// Timer variables
unsigned long previous_temp_humidity_millis = 0;
unsigned long previous_moisture_millis = 0;

// Functions
void setup_wifi();
void handle_mqtt_message(char *topic, byte *payload, unsigned int length);
void update_temp_humidity();
void update_moisture();

String Thing_Set(float currentHumidity, float currentTemperature, float soilHumidity, bool switch_);
void setup()
{
  Serial.begin(115200);
  setup_wifi();
  mqtt.setup(mqtt_server, 1883, mqtt_username, mqtt_password, mqtt_clientId);
  mqtt.connecte();
  mqtt.setCallback(handle_mqtt_message);
  mqtt.subscribe(set_topic);
  mqtt.subscribe(_server);
  sensors.begin();
  pump.begin();
  display.init();
  Serial.println("当前行号：" + String(__LINE__));
}

void loop()
{
  float humidity = sensors.readHumidity();
  float temperature = sensors.readTemperature();
  float soil = sensors.readSoilMoisture();

  bool _sw = pump._isOn;
  String jsonData = Thing_Set(humidity, temperature, soil, _sw);
  char *jsonDataChar = strdup(jsonData.c_str());

  delay(5500);
  Serial.print("temperature:");
  Serial.println(temperature);
  Serial.print("humidity:");
  Serial.println(humidity);
  Serial.print("soilmoisture:");
  Serial.println(soil);
  Serial.println(WiFi.localIP());
  // mqtt.setCallback(NULL);
  mqtt.publish(post_topic, jsonDataChar);
  // mqtt.subscribe(set_topic);
  mqtt.loop();

  display.showTemperature(temperature);
  // delay(2500);
  display.showHumidity(humidity);
  // delay(2500);
  display.showWater(soil);
  delay(5500);
}

void setup_wifi()
{
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  Serial.setTimeout(5000); // 设置串口超时时间为5秒
  WiFi.begin((char *)ssid, password);

  if (WiFi.waitForConnectResult() != WL_CONNECTED)
  {
    Serial.println("WiFi connection failed");
    return;
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void handle_mqtt_message(char *topic, byte *payload, unsigned int length)
{
  String message = "";
  message.concat((char *)payload, length);
  Serial.println(message);
  Serial.println("当前行号：" + String(__LINE__));

  if (strcmp(topic, set_topic) == 0)
  {
    if (message != "0")
    {
      pump.on();
      Serial.println("当前行号：" + String(__LINE__));
    }
    // else if (message == "0")
    else
    {
      pump.off();
    }
  }
}

String Thing_Set(float currentHumidity, float currentTemperature, float soilHumidity, bool switch_)
{
  // 创建一个JsonObject对象
  // 使用ArduinoJson库创建JSON对象
  DynamicJsonDocument doc(1024);
  doc["method"] = "thing.service.property.set";
  JsonObject params = doc.createNestedObject("params");
  params["CurrentHumidity"] = currentHumidity;
  params["CurrentTemperature"] = currentTemperature;
  params["soilHumidity"] = soilHumidity;
  params["switch1"] = (int)switch_;
  doc["id"] = random(100000000, 999999999);
  doc["version"] = "1.0.0";

  String data;
  serializeJson(doc, data); // 将JsonObject对象序列化为JSON字符串
  return data;
}