#include<ESP8266WiFi.h>
#define motorAGo D6
#define motorABack D4
#define motorBGo D1
#define motorBBack D2
void setup() {
  pinMode(motorAGo, OUTPUT);
  pinMode(motorABack, OUTPUT);
  pinMode(motorBGo, OUTPUT);
  pinMode(motorBBack, OUTPUT);
}
void loop() {
  digitalWrite(motorAGo, HIGH);
  digitalWrite(motorBGo, HIGH);
}
