#include<SoftwareSerial.h>
SoftwareSerial uno(0,1);
void setup() {
  Serial.begin(57600);
  uno.begin(9600);
}

void loop() {
uno.println("Hello friend");
String t=uno.readStringUntil('\r');
Serial.println(t);
delay(1000);
}
