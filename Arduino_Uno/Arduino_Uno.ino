#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include "sensor_functions.h"
#include "constants.h"

DHT dht(consts::DHPIN, DHT11);
// char c;
// String dataIn;
// String res;
// int light = 0;


void setup() {
  Serial.begin(57600);
  Serial3.begin(57600);
  pinMode(consts::WATER_SENSOR, OUTPUT);
  pinMode(consts::SOIL_MOISTURE_SENSOR_LED, OUTPUT);
  pinMode(consts::LED, OUTPUT);
  pinMode(consts::R, OUTPUT);
  pinMode(consts::G, OUTPUT);
  pinMode(consts::B, OUTPUT);
  // dht.begin();
}


void loop() {
  delay(2000);
  int waterLv = getWaterLevel();
  Serial.println(String("Water level: ") + waterLv);
  int soilMoisture = getSoilMoisture();
  Serial.println(String("Soil moisture: ") + soilMoisture);
  Serial.println();

  // while (Serial3.available() > 0) {
  //   c = Serial3.read();
  //   if (c == '\n') {
  //     break;
  //   } else {
  //     dataIn += c;
  //   }
  // }
  // if (c == '\n') {

  //   if (dataIn == "sensor/1") {
  //     lightHandle();
  //     delay(2000);
  //   } else if (dataIn == "sensor/2") {
  //     handleTopic();
  //     delay(2000);
  //   }
  //   c = 0;
  //   dataIn = "";
  // }
}