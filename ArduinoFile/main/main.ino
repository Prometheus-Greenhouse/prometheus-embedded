#include "arduino_handle.h"
#define WaterSensor 2
#define SensorIn A0
#define MoistureSensor A1
#define LED 7
#define R 13
#define G 12
#define B 11
Water water(SensorIn,WaterSensor);
Moisture moisture(MoistureSensor);
char c;
String dataIn;
RGB rgb(R,G,B);
void setup() {
  Serial.begin(9600);
    Wire.begin(8);
  Wire.onRequest(requestEvent);
  pinMode(WaterSensor,OUTPUT);
  pinMode(LED,OUTPUT);
  pinMode(R,OUTPUT);
  pinMode(G,OUTPUT);
  pinMode(B,OUTPUT);
  pinMode(LED,OUTPUT);
  }
 void requestEvent()
{String res=water.waterTopic()+moisture.moistureTopic()+"\n";
  Wire.write(res.c_str());
}
   
void loop() {
 if(!Serial)
{
 Serial.end();
 delay(100);
 Serial.begin(9600);
}

String res=water.waterTopic()+moisture.moistureTopic()+"\n";
Serial.println(res);
delay(1000);
}   
