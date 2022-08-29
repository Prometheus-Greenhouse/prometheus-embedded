#include "sensor_functions.h"
#include "constants.h"

int getWaterLevel() {
  digitalWrite(consts::WATER_SENSOR, HIGH);
  delay(1000);
  int value = analogRead(consts::SENSOR_IN);
  digitalWrite(consts::WATER_SENSOR, LOW);
  delay(1000);
  return value;
}

int getSoilMoisture(){
  digitalWrite(consts::SOIL_MOISTURE_SENSOR_LED, HIGH);
  delay(1000);
  int mvalue= analogRead(consts::SOIL_MOISTURE_SENSOR);
  digitalWrite(consts::SOIL_MOISTURE_SENSOR_LED, LOW);
  delay(1000);
  return mvalue;
}

// void handleTopic() {
//   int water = waterLevel();
//   res = "";
//   res += String(water) + "\n";
//   Serial3.println(res);
// }


// void DHT11handle() {
//   float h = dht.readHumidity();
//   float t = dht.readTemperature();
//   Serial.print("Humidity:");
//   Serial.println(h);
//   Serial.print("Temperature:");
//   Serial.println(t);
//   res = "";
//   res += String(h) + " " + String(t) + " \n";
// }


// void RGB(int r, int g, int b) {
//   analogWrite(R, r);
//   analogWrite(G, g);
//   analogWrite(B, b);
// }

// void lightHandle() {
//   light = analogRead(A1);
//   if (light < 100) {
//     res += ("Very bright");
//     RGB(255, 0, 0);
//   } else if (light < 200) {
//     res += ("Bright");
//     RGB(0, 0, 255);
//   } else if (light < 500) {
//     res += ("Light");
//     RGB(60, 179, 113);
//   } else if (light < 800) {
//     res += ("Dim");
//     RGB(255, 165, 0);
//   } else {
//     res += ("Dark");
//     RGB(106, 90, 205);
//   }
//   res += "\n";
//   Serial.println(res);
// }
