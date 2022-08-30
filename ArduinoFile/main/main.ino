#include "arduino_handle.h"
#define WaterSensor 2
#define SensorIn A0
#define MoistureSensor A5
#define LightSensor A1
#define LED 8
#define R 13
#define G 12
#define B 11
Water water(SensorIn,WaterSensor);
Light light_handle(LightSensor);
Moisture moisture(MoistureSensor);
char c;
String dataIn;
RGB rgb(R,G,B);
void setup() {
  Serial.begin(57600);
  Serial3.begin(57600);
  pinMode(WaterSensor,OUTPUT);
  pinMode(LED,OUTPUT);
  pinMode(R,OUTPUT);
  pinMode(G,OUTPUT);
  pinMode(B,OUTPUT);
   } 


void loop() {
 while(Serial3.available()>0)
{
 c=Serial3.read();
  if(c=='\n')
  {
    break;
  }
  else
  {
    dataIn+=c;
  }
}
if(c=='\n')
{
String result=splitString(dataIn,":");
result.trim();
if(dataIn=="Light")
{ light_handle.lightTopic();
  delay(2000);
}
else if(dataIn=="Water")
{ water.waterTopic();
  delay(2000);
}
else if(dataIn=="Moisture")
{
  moisture.moistureTopic();
  delay(2000);
}
   c=0;
   dataIn="";
}
else
{
Serial.println(dataIn);
}
for(int i=0;i<255;i++)
{
  rgb.rgbColor(i,i,i);
  }
}
