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
void Water::waterTopic()
{
   int water=Water::waterLevel();
    res="";
    res+=String(water)+"\n";
    Serial3.println(res);
}

 void temperatureTopic()
{ DHT dht(DHTPIN,DHT11); 
  dht.begin();
  float h=dht.readHumidity();
    float t=dht.readTemperature();
    Serial.print("Humidity:");
    Serial.println(h);
    Serial.print("Temperature:");
    Serial.println(t);
    res="";
    res+=String(h)+" "+String(t)+"\n";
    Serial3.println(res);
}

Moisture::Moisture(byte MoistureSensor)
{
  this->MoistureSensor=MoistureSensor;
}
void Moisture::moistureTopic()
{
   int limit=300;
  MoistureValue=analogRead(MoistureSensor);
  if(MoistureValue<limit)
  {
    Serial3.println("No need water");
  }
  else
  {
    Serial3.println("Need Water");
  }
}


Light::Light(byte LightSensor)
{
  this->LightSensor=LightSensor;
}
void Light::lightTopic()

{
   light=analogRead(LightSensor);
   if(light<100)
   {
    res+=("Very bright");
    RGB(255,0,0);
   }
   else if(light<200)
   {
    res+=("Bright");
    RGB(0,0,255);
   }
   else if(light<500)
   {
    res+=("Light");
    RGB(60,179,113);
   }
   else if(light<800)
   {
    res+=("Dim");
    RGB(255,165,0);
   }
   else
   {
    res+=("Dark");
    RGB(106,90,205);
   }
   res+="\n";
   Serial3.println(res);
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