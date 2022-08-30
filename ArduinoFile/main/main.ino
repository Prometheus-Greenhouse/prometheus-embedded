#include<SoftwareSerial.h>
#include<Wire.h>
#include<LiquidCrystal_I2C.h>
#include<DHT.h>
#include "arduino_handle.h"
#define DHTPIN 4
#define WaterSensor 2
#define SensorIn A0
#define MoistureSensor A5
#define LightSensor A1
#define LED 8
#define R 13
#define G 12
#define B 11
Water water(SensorIn,WaterSensor);
Temparature temp(DHTPIN);
Light light(LightSensor);
Moisture moisture(MoistureSensor);
RGB rgb(R,G,B);
void setup() {
  Serial.begin(57600);
  Serial3.begin(57600);
  pinMode(WaterSensor,OUTPUT);
  pinMode(LED,OUTPUT);
  pinMode(R,OUTPUT);
  pinMode(G,OUTPUT);
  pinMode(B,OUTPUT);
  temp.init();
} 
void loop() {
readData();
for(int i=0;i<255;i++)
{
  rgb.rgbColor(i,i,i);
  }
}
