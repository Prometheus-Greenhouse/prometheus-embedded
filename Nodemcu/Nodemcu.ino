#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <iostream>
#include <algorithm>
#include <ArduinoJson.h>
#include <string.h>
#include "wifi.h"
#include "constants.h"


WiFiClient espClient;
PubSubClient client(espClient);

// unsigned long lastMsg = 0;
// #define MSG_BUFFER_SIZE  (50)
// #define EspSerial Serial3
// char msg[MSG_BUFFER_SIZE];
// int value = 0;
// #define WaterSensor 4
// const int ledGPIO5=5;
// #define sensorIn A0
// const char *Topic="sensor/0";
// String message;
// String _topic;
// String mess_setup;
// const char *Toopic="available";
// const char *sensor1="sensor/1";
// int counter=0;
// int counter1=0;
// String split_str[5];
// char c;
// String dataIn;
// #define num_seed 5
// String uuid[num_seed];
const char *SENSOR1_TOPIC;
const char *SENSOR2_TOPIC;
const char *SENSOR3_TOPIC;
void setup() {
  // pinMode(ledGPIO5, OUTPUT);
  // pinMode(WaterSensor, OUTPUT);

  Serial.begin(115200);

  Serial.println(SENSOR2);
  Serial.println(SENSOR3);
  setupWifi();
  client.setServer(consts::MQTT_SERVER, 1883);
  client.setCallback(setup_callback);
  // Connect borker
  if (!client.connected()) {
    String clientId = "esp8266-client-";
    clientId += String(WiFi.macAddress());
    if (client.connect(clientId.c_str())) {
      Serial.println("Mqtt broker connected");
    } else {
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }

  // Run sensor detect
  client.subscribe(SENSOR1, 1);
  client.subscribe(SENSOR2, 1);
  client.subscribe(SENSOR3, 1);

  client.publish(consts::AVAILABLE, SENSOR1);
  client.publish(consts::AVAILABLE, SENSOR2);
  client.publish(consts::AVAILABLE, SENSOR3);

  while(!SENSOR1_TOPIC || !SENSOR2_TOPIC || !SENSOR3_TOPIC){
    client.loop();
    Serial.println("Waiting regists sensors...");
    delay(1000);
  }
  Serial.println("Setup done");
}

// int WaterLevel()
// {
//   digitalWrite(WaterSensor,HIGH);
//   delay(10);
//   value=analogRead(sensorIn);
//   digitalWrite(WaterSensor,LOW);
//   return value;
// }

void setup_callback(char *topic, byte *payload, unsigned int length) {
  Serial.println(String("Message arrived ") + topic);
  String message = "";
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  Serial.println(message);

  if (strcmp(topic, SENSOR1) == 0) {
    client.unsubscribe(SENSOR1);
    SENSOR1_TOPIC = message.c_str();
    Serial.print(SENSOR1_TOPIC);
  } else if (strcmp(topic, SENSOR2) == 0) {
    client.unsubscribe(SENSOR2);
    SENSOR2_TOPIC = message.c_str();
    Serial.print(SENSOR2_TOPIC);
  } else if (strcmp(topic, SENSOR3) == 0) {
    client.unsubscribe(SENSOR3);
    SENSOR3_TOPIC = message.c_str();
    Serial.print(SENSOR3_TOPIC);
  }
}

// void reconnect() {
//   // Loop until we're reconnected
//   while (!client.connected()) {
//     Serial.print("Attempting MQTT connection...");
//     // Create a random client ID
//     String clientId = "ESP8266Client-";
//     clientId += String(random(0xffff), HEX);
//     // Attempt to connect
//     if (client.connect("ESP8266Client")) {
//       Serial.println("connected");
//       client.subscribe("ESP8266/4");
//       client.subscribe("ESP8266/5");
//       for (int i = 0; i < num_seed; i++) {
//         client.subscribe(uuid[i].c_str());
//       }

//     } else {
//       Serial.print("failed, rc=");
//       Serial.print(client.state());
//       Serial.println(" try again in 5 seconds");
//     }
//   }
// }

// String uuid4() {
//   String res = "";
//   res += hex_print(8, 0, 15);
//   res += "-";
//   res += hex_print(4, 0, 15);
//   res += "-";
//   res += "4";
//   res += hex_print(3, 0, 15);
//   res += "-";
//   res += hex_print(1, 8, 11);
//   res += hex_print(3, 0, 15);
//   res += "-";
//   res += hex_print(12, 0, 15);
//   return res;
// }

// String hex_print(int n, int mn, int mx) {
//   String res = "";
//   for (; n > 0; n--) {
//     int X = random(mn, mx);
//     String re = String(X, HEX);
//     res += re;
//   }
//   return res;
// }

// void read_data(const char* data) {
//   while (Serial.available() > 0) {
//     c = Serial.read();
//     if (c == '\n') {
//       break;
//     } else {
//       dataIn += c;
//     }
//   }
//   if (c == '\n') {
//     dataIn.trim();
//     if (dataIn == "") {
//       return;
//     } else {
//       client.publish(data, dataIn.c_str());
//       c = 0;
//       dataIn = "";
//     }
//   }
// }

void loop() {
  client.loop();
  // if (counter < 1) {

  //   for (int i = 0; i < 5; i++) {
  //     mess_setup = "text:";
  //     mess_setup += uuid[i];
  //     client.publish(Toopic, mess_setup.c_str());
  //     mess_setup = "";
  //   }

  //   counter++;
  // }
  // String result = splitString(message, ":");
  // result.trim();
  // int lenght = result.length();
  // char topic_sensor[lenght + 1];
  // strcpy(topic_sensor, result.c_str());
  // unsigned long now = millis();
  // if (now - lastMsg > 1000) {
  //   lastMsg = now;
  //   read_data(topic_sensor);
  //   result += "\n";
  //   Serial.println(result);
  //   String res = "" + _topic + message;
  // }
}