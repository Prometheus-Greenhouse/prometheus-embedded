#include "arduino_handle.h"

int light;
int MoistureValue;
String res;
Water::Water(byte SensorIn,byte WaterSensor)
{
  this->SensorIn=SensorIn;
  this->WaterSensor=WaterSensor;
}
int Water::waterLevel()
{
   digitalWrite(WaterSensor,HIGH);
  delay(20);
  int value=analogRead(SensorIn);
  digitalWrite(WaterSensor,LOW);
  return value;
}
String Water::waterTopic()
{
   int water=Water::waterLevel();
    res="";
    res+=String(water)+":W+";
    return res;
}


Moisture::Moisture(byte MoistureSensor)
{
  this->MoistureSensor=MoistureSensor;
}
String Moisture::moistureTopic()
{
   int limit=300;
  MoistureValue=analogRead(MoistureSensor);
  String mois_res="";
 mois_res=String(MoistureValue)+":M+";
 return mois_res;
}





Light::Light(byte LightSensor)
{
  this->LightSensor=LightSensor;
}
String Light::lightTopic()
{ String light_res="";
   light=analogRead(LightSensor);
   if(light<100)
   {
    res+=("Very bright");
   }
   else if(light<200)
   {
    res+=("Bright");
   }
   else if(light<500)
   {
    res+=("Light");
   }
   else if(light<800)
   {
    res+=("Dim");
   }
   else
   {
    res+=("Dark");
   }
   light_res=String(light)+":L+";
   return light_res;
}



String splitString(String s,String deli)
{
 int from=s.indexOf(deli);
 String result="";
 String type="";
 for(int i=0;i<from;i++)
 {
  type+=s[i];
 }
 for(int i=from+1;i<s.length();i++)
 {
  result+=s[i];
 }
 return result;
}


RGB::RGB(byte R,byte G,byte B)
{
  this->R=R;
  this->G=G;
  this->B=B;
}


void RGB::rgbColor(int r,int g,int b)
{
  analogWrite(R,r);
  analogWrite(G,g);
  analogWrite(B,b);
}
