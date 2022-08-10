#include<SoftwareSerial.h>
SoftwareSerial uno(1,2);
void setup() {
 Serial.begin(115200);
 uno.begin(9600);

}

void loop() {
String msg=uno.readStringUntil('\r');
Serial.print(msg);
 delay(2000);
}
