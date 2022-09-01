#include <ESP8266WiFi.h>
#include "wifi.h"
#include "constants.h"

void setupWifi() {
  Serial.println("Connecting to ");
  // WiFi.mode(WIFI_STA);
  WiFi.begin(consts::WIFI_SID, consts::WIFI_PASSWORD);
  Serial.println();
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");

  // randomSeed(micros());

  // Serial.println("");
  // Serial.println("WiFi connected");
  // Serial.println("IP address: ");
  // Serial.println(WiFi.localIP());
  // client.subscribe("ESP8266/4");
  // client.subscribe("ESP8266/5");
  // client.subscribe("allow");
  // for(int i=0;i<num_seed;i++)
  // {
  //   client.subscribe(uuid[i].c_str());
  // }
}