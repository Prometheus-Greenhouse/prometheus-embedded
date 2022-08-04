
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
const char* ssid = "Thuy Tang 2";
const char* password = "0903802281";
const char* mqtt_server = "192.168.0.115";
WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE	(50)
char msg[MSG_BUFFER_SIZE];
int value = 0;
const int ledGPIO4=4;
const int ledGPIO5=5;
void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
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
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  String message="";
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    message+=(char)payload[i];
  }
  Serial.println(topic=="ESP8266/4");
  int t=strcmp(topic,"ESP8266/4");
   int t1=strcmp(topic,"ESP8266/5");
  if(t==0)
  {
    Serial.print("Changing to GPIO4");
    if(message=="1")
    {
      digitalWrite(ledGPIO4,HIGH);
      Serial.print("Led 4 is lighting...");
    }
    else if(message=="0")

    {
      digitalWrite(ledGPIO4,LOW);
      Serial.print("Led 4 is turning off...");
    }
  }
 else if(t1==0)
   {
    Serial.print("Changing to GPIO5");
    if(message=="1")
    {
      digitalWrite(ledGPIO5,HIGH);
      Serial.print("Led 5 is turning on....");
    }
    else if(message=="0")
    {
      digitalWrite(ledGPIO5,LOW);
      Serial.print("Led 5 is turning off...");
    }
   }
  Serial.println();
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
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  pinMode(ledGPIO4,OUTPUT);
  pinMode(ledGPIO5,OUTPUT);
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  unsigned long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
    ++value;
    snprintf (msg, MSG_BUFFER_SIZE, "hello world #%ld", value);
    Serial.print("Publish message: ");
    Serial.println(msg);
  }
}
void loop() {
int level=waterLevel();
Serial.print("Water level is:");
Serial.println(level);
delay(1000);
}
int waterLevel()
{
  digitalWrite(sensorPower,HIGH);
  delay(10);
  value=analogRead(sensorIn);
  digitalWrite(sensorPower,LOW);
  return value;
}
