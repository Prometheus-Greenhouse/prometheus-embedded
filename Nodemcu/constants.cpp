#include "constants.h"
#include <ESP8266WiFi.h>

// String hex_print(int n, int mn, int mx) {
//   String res = "";
//   for (; n > 0; n--) {
//     int X = random(mn, mx);
//     String re = String(X, HEX);
//     res += re;
//   }
//   return res;
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
String macAddress = String(WiFi.macAddress());

String s1 = macAddress + "/1";
String s2 = macAddress + "/2";
String s3 = macAddress + "/3";
const char *SENSOR1 = s1.c_str();
const char *SENSOR2= s2.c_str();
const char *SENSOR3 = s3.c_str();