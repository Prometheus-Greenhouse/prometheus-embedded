#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
// #include <MemoryFree.h>
// #include <EEPROM.h>
#include "sensor_functions.h"
#include "constants.h"


DHT dht(consts::DHPIN, DHT11);
// char c;
// String dataIn;
// String res;
// int light = 0;

SoftwareSerial espSerial(5, 6);

void setup() {
  Serial.begin(115200);
  espSerial.begin(115200);
  // Serial3.begin(115200);

  pinMode(consts::WATER_SENSOR_LED, OUTPUT);
  pinMode(consts::SOIL_MOISTURE_SENSOR_LED, OUTPUT);

  pinMode(consts::LED, OUTPUT);
  pinMode(consts::R, OUTPUT);
  pinMode(consts::G, OUTPUT);
  pinMode(consts::B, OUTPUT);
  // dht.begin();
}


void loop() {

  int waterLv = getWaterLevel();
  int soilMoisture = getSoilMoisture();
  Serial.println(waterLv);
  Serial.println(soilMoisture);
  espSerial.write((String(consts::WATER_SENSOR) + "/" + waterLv + "|").c_str());
  espSerial.write((String(consts::SOIL_MOISTURE_SENSOR) + "/" + soilMoisture + "|").c_str());
  delay(3000);

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

// void serialEvent3(){
//   while(Serial3.available()){
//     Serial.println("Recive from esp ->");
//     char rs = Serial3.read();
//     Serial.write(rs);
//     Serial.println(rs);
//   }
// }