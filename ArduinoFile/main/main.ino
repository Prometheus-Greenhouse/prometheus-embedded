#include "arduino_handle.h"
#define WaterSensor 2
#define SensorIn A0
#define MoistureSensor A1
#define LightSensor A2
#include<DHT.h>
#define DHTPIN 7
#define motionPin 9
DHT dht(DHTPIN,DHT11);
#define R 13
#define G 12
#define B 11
Water water(SensorIn,WaterSensor);
Moisture moisture(MoistureSensor);
Light light_object(LightSensor);
int c;
String dataIn;
RGB rgb(R,G,B);
void setup() {
  Serial.begin(9600);
  Wire.begin(8);
  dht.begin();
  Wire.onRequest(requestEvent);
  pinMode(motionPin,INPUT);
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
{ String temp=water.waterTopic()+moisture.moistureTopic()+ligh_object.lightTopic()+"\n";
  if(temp_humidTopic()=="")
{ Wire.write(temp.c_str());
  return; 
}
  String res=water.waterTopic()+moisture.moistureTopic()+temp_humidTopic()+light_object.lightTopic()+"\n";
  Wire.write(res.c_str());
}  
void loop() {
 if(!Serial)
{
 Serial.end();
 delay(100);
 Serial.begin(9600);
}
int value=digitalRead(motionPin);
if(value==1)
{
  Serial.println("There's people here.");
}
else
{
  Serial.println("There's no people here.");
}
String res=water.waterTopic()+moisture.moistureTopic()+light_object.lightTopic()+temp_humidTopic()+"\n";
Serial.println(res);
delay(1000);
}   
