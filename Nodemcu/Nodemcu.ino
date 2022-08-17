#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <iostream>
#include <algorithm>
const char* ssid = "long 2.4G";
const char* password = "Ld201199";
const char* mqtt_server = "192.168.1.3";
WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE  (50)
#define EspSerial Serial3
char msg[MSG_BUFFER_SIZE];
int value = 0;
#define WaterSensor 4
const int ledGPIO5=5;
#define sensorIn A0
const char *Topic="sensor/0";
String message;
String _topic;
String mess_setup="fuck off.";
const char *Toopic="available";
const char *sensor1="sensor/1";
int counter=0;
int counter1=0;
String split_str[5];
char c;
String dataIn;
void setup() {
  pinMode(ledGPIO5,OUTPUT);
  pinMode(WaterSensor,OUTPUT);
  Serial.begin(57600);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}
void setup_wifi() {

  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  client.subscribe("ESP8266/4");
  client.subscribe("ESP8266/5");
  client.subscribe("allow");
}
int WaterLevel()
{
  digitalWrite(WaterSensor,HIGH);
  delay(10);
  value=analogRead(sensorIn);
  digitalWrite(WaterSensor,LOW);
  return value;
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  _topic="";
  message="";
  for (int i = 0; i < length; i++) {
    message+=(char)payload[i];
  }
  message+="\n";
  _topic+=topic;
  _topic+="\n";
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      client.subscribe("ESP8266/4");
      client.subscribe("ESP8266/5");
      client.subscribe("allow");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");      
    }
  }
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

 void read_data(const char* data)
{
   while(Serial.available()>0)
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
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
 if(counter<1)
 {
 client.publish(Toopic,mess_setup.c_str());
 counter++;
 }
  String result=splitString(message,":");
  result.trim();
  int lenght=result.length();
  char topic_sensor[lenght+1];
  strcpy(topic_sensor,result.c_str());
  unsigned long now = millis();
  if (now - lastMsg > 1000) {
      lastMsg=now;
     read_data(topic_sensor);
     result+="\n";
     Serial.println(result);
    String res=""+_topic+message;
    
  }
}
