#ifndef MCU_HANDLE.H
#define MCU_HANDLE.H
#include <Arduino.h>
void readData(const char* data);
void splitString(String s,String deli);
String uuid4();
String hex_print(int n,int mn ,int mx);
void handleData();
void void object_setup(String object[]);
#endif
