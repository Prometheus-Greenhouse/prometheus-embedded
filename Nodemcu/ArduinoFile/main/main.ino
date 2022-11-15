#include "arduino_handle.h"
#define WaterSensor 2
#define SensorIn A0
#define MoistureSensor A1
#include<DHT.h>
#define DHTPIN 7
DHT dht(DHTPIN,DHT11);
#define R 13
#define G 12
#define B 11
Water water(SensorIn,WaterSensor);
Moisture moisture(MoistureSensor);
int c;
String dataIn;
RGB rgb(R,G,B);
void setup() {
  Serial.begin(9600);
    Wire.begin(8);
     dht.begin();
  Wire.onRequest(requestEvent);
  }
  String temp_humidTopic()
{ String res="";
  float h=dht.readHumidity();
  float t=dht.readTemperature();
  if(isnan(h)||isnan(t))
  {
   return res;
  }
  res+=String(h)+":"+String(t)+"+";
  return res;
}
 void requestEvent()
{ if(temp_humidTopic()=="")
{
  return;
}
  String res=water.waterTopic()+moisture.moistureTopic()+temp_humidTopic()+"\n";
  Wire.write(res.c_str());
}
   
void loop() {
 if(!Serial)
{
 Serial.end();
 delay(100);
 Serial.begin(9600);
}

String res=water.waterTopic()+moisture.moistureTopic()+temp_humidTopic()+"\n";
Serial.println(res);
delay(1000);
}   
