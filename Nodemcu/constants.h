#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <Arduino.h>

extern const char *SENSOR1;
extern const char *SENSOR2;
extern const char *SENSOR3;

namespace consts {
constexpr char *WIFI_SID{ "long 2.4G" };
constexpr char *WIFI_PASSWORD{ "Ld201199" };
constexpr char *MQTT_SERVER{ "192.168.1.3" };
constexpr char *AVAILABLE{ "available" };
constexpr char *ARDUINO_A0{ "14" };
constexpr char *ARDUINO_A1{ "15" };
constexpr char *ARDUINO_A2{ "16" };
constexpr char *ARDUINO_A3{ "17" };
constexpr char *ARDUINO_A4{ "18" };
constexpr char *ARDUINO_A5{ "19" };
}

#endif