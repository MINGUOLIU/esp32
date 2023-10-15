#include "MQTT.h"

MQTT::MQTT() : mqtt_client_(espClient_)
{
}

void MQTT::setup(const char *mqtt_server, const int mqtt_port, const char *mqtt_username, const char *mqtt_password, const char *device_id)
{
    mqtt_server_ = mqtt_server;
    mqtt_port_ = mqtt_port;
    mqtt_username_ = mqtt_username;
    mqtt_password_ = mqtt_password;
    device_id_ = device_id;

    mqtt_client_.setServer(mqtt_server_, mqtt_port_);
    // mqtt_client_.setMaxTries(0);
}

void MQTT::connecte()
{
    while (!mqtt_client_.connected())
    {
        if (mqtt_client_.connect(device_id_, mqtt_username_, mqtt_password_))
        {
            Serial.println("MQTT connected successfully");
        }
        else
        {
            // 连接失败，等待一秒钟重试
            delay(1000);
        }
    }
}

void MQTT::publish(const char *topic, const uint8_t *message, unsigned int length)
{
    mqtt_client_.publish(topic, message, length);
}

void MQTT::publish(const char *topic, const char *message)
{
    mqtt_client_.publish(topic, message);
}
void MQTT::subscribe(const char *topic)
{
    mqtt_client_.subscribe(topic);
}

void MQTT::loop()
{
    mqtt_client_.loop();
}

void MQTT::setCallback(void (*callback)(char *, byte *, unsigned int))
{
    mqtt_client_.setCallback(callback);
}