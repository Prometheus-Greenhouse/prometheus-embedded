#ifndef SENSOR_FUNCTIONS_H
#define SENSOR_FUNCTIONS_H
#include <Arduino.h>

int getWaterLevel();
void handleTopic();
void DHT11handle();
void RGB(int r, int g, int b);
void lightHandle();
int getSoilMoisture();

#endif
