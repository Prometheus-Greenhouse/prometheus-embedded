#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <Arduino.h>

extern const char *SENSOR1;
extern const char *SENSOR2;
extern const char *SENSOR3;

namespace consts {
constexpr char *WIFI_SID{ "long 2.4G" };
constexpr char *WIFI_PASSWORD{ "Ld201199" };
constexpr char *MQTT_SERVER{ "192.168.1.4" };
constexpr char *AVAILABLE{ "available" };
}

#endif