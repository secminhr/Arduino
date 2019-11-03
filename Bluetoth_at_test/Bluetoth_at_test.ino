#include<SoftwareSerial.h>
#define RX 10
#define TX 11

SoftwareSerial BT(RX,TX);

void setup() {
  BT.begin(115200);
  Serial.begin(115200);
}

void loop() {
  if (BT.available()) {
    Serial.write(BT.read());
  }
  if (Serial.available()) {
    BT.write(Serial.read());
  }
}

