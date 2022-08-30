#include "mcu_handle.h"
#define WaterSensor 4
const int ledGPIO5=5;
#define sensorIn A0
const char *Topic="sensor/0";
String message;
String _topic;
String mess_setup="";
const char *Toopic="available";
const char *sensor1="sensor/1";
int counter=0;
int counter1=0;
String split_str[5];
char c;
String dataIn;
#define num_seed 5
String uuid[num_seed];
String all_mess[num_seed];
int counter_all=0; 
String object[num_seed];
void readData(const char* data)
{  while(Serial.available()>0)
  {
    c=Serial.read();
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
    dataIn.trim();
    if(dataIn=="")
    {
     return;
    }
    else
    {
    client.publish(data,dataIn.c_str());
    c=0;
    dataIn="";
    }
  }
}

void splitString(String s,String deli)
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

String uuid4()
{
  String res="";
  res+=hex_print(8,0,15);
  res+="-";
  res+=hex_print(4,0,15);
  res+="-";
  res+="4";
  res+=hex_print(3,0,15);
  res+="-";
  res+=hex_print(1,8,11);
  res+=hex_print(3,0,15);
  res+="-";
  res+=hex_print(12,0,15);
  return res;
}

String hex_print(int n,int mn ,int mx)
{
  String res="";
for(;n>0;n--){
int X = random(mn,mx);
String re=String( X ,HEX );
res+=re;
}
return res;
}

void handleData()
{
    unsigned long now = millis();
  if (now - lastMsg > 1000) {
   for(int i=0;i<num_seed;i++)
   {
    String result=splitString(all_mess[i],":");
    result.trim();
    result+=":"+object[i];
  int lenght=result.length();
  char topic_sensor[lenght+1];
  strcpy(topic_sensor,result.c_str());
      lastMsg=now;
     readData(topic_sensor);
     result+="\n";
     Serial.println(result);
   }
    
  }
}

void object_setup(String object[])
{
  object[0]="Light";
  object[1]="Water";
  object[2]="Moisture";
  object[3]="";
  object[4]="";
}
