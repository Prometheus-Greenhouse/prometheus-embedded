#ifndef ARDUINO_HANDLE.H
#define ARDUINO_HANDLE.H
#include <Arduino.h>
#include<DHT.h>
#define DHTPIN 4
class Water
{
  private:
         byte SensorIn;
         byte WaterSensor;
  public:
       Water(byte SensorIn,byte WaterSensor);
       int waterLevel();
       void waterTopic();
};

void temperatureTopic();

class Moisture
{
  private:
        byte MoistureSensor;
  public:
       Moisture(byte MoistureSensor);
       void moistureTopic();
};

class Light
{
  private:
         byte LightSensor;
  public:
        Light(byte LightSensor);
        void lightTopic();
};
class RGB
{private:
      byte R;
      byte G;
      byte B;
 public:
      RGB(byte R,byte G,byte B);
      void rgbColor(int r,int g,int b);
};
String splitString(String s,String deli);
#endif
