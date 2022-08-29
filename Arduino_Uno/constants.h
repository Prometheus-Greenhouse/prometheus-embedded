#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <Arduino.h>

namespace consts {
constexpr int DHPIN{ 4 };
constexpr int WATER_SENSOR { 2 };
constexpr int SOIL_MOISTURE_SENSOR {A5};
constexpr int SOIL_MOISTURE_SENSOR_LED { 13 };
constexpr int SENSOR_IN{ A1 };
constexpr int LED{ 8 };
constexpr int R{ 13 };
constexpr int G{ 12 };
constexpr int B{ 11 };
}
#endif;