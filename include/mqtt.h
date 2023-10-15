#ifndef MQTT_H
#define MQTT_H

#include <PubSubClient.h>
#include <WiFiClient.h>

class MQTT
{
public:
    MQTT();
    void setup(const char *mqtt_server, const int mqtt_port, const char *mqtt_username, const char *mqtt_password, const char *device_id);
    void connecte();
    void publish(const char *topic, const uint8_t *message, unsigned int length);
    void publish(const char *topic, const char *message);
    void subscribe(const char *topic);
    void loop();
    void setCallback(void (*callback)(char *, byte *, unsigned int));

private:
    const char *mqtt_server_;
    int mqtt_port_;
    const char *mqtt_username_;
    const char *mqtt_password_;
    const char *device_id_;
    WiFiClient espClient_;
    PubSubClient mqtt_client_;
};

#endif
