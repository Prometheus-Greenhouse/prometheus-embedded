#include "type.h"
#include <ctime>

String splitString(String s, String deli) {
  int from = s.indexOf(deli);
  String result = "";
  String type = "";
  for (int i = 0; i < from; i++) {
    type += s[i];
  }
  for (int i = from + 1; i < s.length(); i++) {
    result += s[i];
  }
  return result;
}

String hex_print(int n, int mn, int mx) {
  String res = "";
  for (; n > 0; n--) {
    int X = random(mn, mx);
    String re = String(X, HEX);
    res += re;
  }
  return res;
}

String uuid4() {
  String res = "";
  res += hex_print(8, 0, 15);
  res += "-";
  res += hex_print(4, 0, 15);
  res += "-";
  res += "4";
  res += hex_print(3, 0, 15);
  res += "-";
  res += hex_print(1, 8, 11);
  res += hex_print(3, 0, 15);
  res += "-";
  res += hex_print(12, 0, 15);
  return res;
}