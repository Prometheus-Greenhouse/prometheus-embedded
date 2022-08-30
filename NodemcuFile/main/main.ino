#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <iostream>
#include <algorithm>
#include "mcu_handle.h"
#include<ArduinoJson.h>
const char* ssid = "long 2.4G";
const char* password = "Ld201199";
const char* mqtt_server = "192.168.1.4";
WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE  (50)
char msg[MSG_BUFFER_SIZE];
int value = 0;
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
#define num_seed 5
String uuid[num_seed];
String all_mess[num_seed];
int counter_all=0; 
String object[num_seed];
void setup() {
  pinMode(ledGPIO5,OUTPUT);
  pinMode(WaterSensor,OUTPUT);
  Serial.begin(57600);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  for (int i=0;i<num_seed;i++)
  {
    uuid[i]=uuid4();
  }
  object_setup(object);

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
  for(int i=0;i<num_seed;i++)
  {
    client.subscribe(uuid[i].c_str());
  }
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
  all_mess[counter_all]=message;
  _topic+=topic;
  _topic+="\n";
  counter_all+=1;
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
    for(int i=0;i<num_seed;i++)
  {
    client.subscribe(uuid[i].c_str());
  }

  } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");      
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
  for(int i=0;i<num_seed;i++)
  {
    mess_setup="text:"+uuid[i];
 client.publish(Toopic,mess_setup.c_str());
 mess_setup="";
  }
 counter++;
 }
handleData();
}
