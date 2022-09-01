#include <ESP8266WiFi.h>
#include <PubSubClient.h>
// #include <iostream>
// #include <algorithm>
// #include <string.h>
#include "wifi.h"
#include "constants.h"
#include "type.h"

WiFiClient espClient;
PubSubClient client(espClient);

String SENSOR1_TOPIC;
String SENSOR2_TOPIC;
String SENSOR3_TOPIC;

void setup() {
  Serial.begin(115200);
  Serial1.begin(115200);
  setupWifi();

  client.setServer(consts::MQTT_SERVER, 1883);
  client.setCallback(setup_callback);

  // Connect borker
  if (!client.connected()) {
    String clientId = "esp8266-client-";
    String macAddress = String(WiFi.macAddress());
    clientId += macAddress;


    if (client.connect(clientId.c_str())) {
      Serial.println(String("Mqtt broker connected clientId: ") + clientId);
    } else {
      Serial.println(String("failed with state ") + client.state());
      delay(2000);
    }
  }

  // Run sensor detect
  Serial.println(SENSOR1);
  Serial.println(SENSOR2);
  Serial.println(SENSOR3);

  client.subscribe(SENSOR1, 1);
  client.subscribe(SENSOR2, 1);
  client.subscribe(SENSOR3, 1);

  client.publish(consts::AVAILABLE, SENSOR1);
  client.publish(consts::AVAILABLE, SENSOR2);
  client.publish(consts::AVAILABLE, SENSOR3);

  while (SENSOR1_TOPIC == NULL || SENSOR2_TOPIC == NULL || SENSOR3_TOPIC == NULL) {
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
    SENSOR1_TOPIC = message;
    Serial.print(SENSOR1_TOPIC);
  } else if (strcmp(topic, SENSOR2) == 0) {
    client.unsubscribe(SENSOR2);
    SENSOR2_TOPIC = message;
    Serial.print(SENSOR2_TOPIC);
  } else if (strcmp(topic, SENSOR3) == 0) {
    client.unsubscribe(SENSOR3);
    SENSOR3_TOPIC = message;
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
  if (Serial.available() > 0) {
    Serial.println("Recevied");
    for (int i = 0; i < 3; i++) {
      String sensorId = Serial.readStringUntil('/');
      if (sensorId == "")
        break;
      String data = Serial.readStringUntil('|');

      if (sensorId == consts::ARDUINO_A1) {
        client.publish(SENSOR1_TOPIC.c_str(), data.c_str());
        Serial.println(String("|") + SENSOR1_TOPIC.c_str() + "|");

      } else if (sensorId == consts::ARDUINO_A5) {
        client.publish(SENSOR2_TOPIC.c_str(), data.c_str());
        Serial.println(String("|") + SENSOR2_TOPIC.c_str() + "|");


      } else if (sensorId == "3") {
        client.publish(SENSOR3_TOPIC.c_str(), data.c_str());
        Serial.println(String("|") + SENSOR3_TOPIC.c_str() + "|");
      }
      Serial.println(String("|") +sensorId + "/" + data + "|");
    }
  }


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

// void serialEvent() {
//   while (Serial.available()) {
//     String data = Serial.readString();
//     client.publish("zzz", "sensor ev0");
//     client.publish(SENSOR1_TOPIC, data.c_str());
//   }
// }

// void serialEvent3() {
//   client.publish("zzz", "sensor ev3");
//   client.publish(SENSOR1_TOPIC, "sensor 1, ev3");
//   client.publish(SENSOR2_TOPIC, "sensor 2, ev3");
//   client.publish(SENSOR3_TOPIC, "sensor 3, ev3");
//   while (Serial1.available()) {
//     Serial.println("------>");
//     char rs = Serial1.read();
//     Serial.write(rs);
//   }
// }
// void serialEvent1() {
//   client.publish("zzz", "sensor ev1");
//   client.publish(SENSOR1_TOPIC, "sensor 1, ev1");
//   client.publish(SENSOR2_TOPIC, "sensor 2, ev1");
//   client.publish(SENSOR3_TOPIC, "sensor 3, ev1");
//   while (Serial1.available()) {
//     Serial.println("------>");
//     char rs = Serial1.read();
//     Serial.write(rs);
//   }
// }