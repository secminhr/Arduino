#include <SoftwareSerial.h>
#define RX 10
#define TX 11
#define motorRightGo 2
#define motorRightBack 3
#define motorLeftGo 5
#define motorLeftBack 4

SoftwareSerial mySerial(RX, TX);

void setup() {
  mySerial.begin(115200);
  mySerial.println("WIFI Ready!");
  Serial.begin(115200);
  Serial.println("Serial Ready!");
  pinMode(motorRightGo, OUTPUT);
  pinMode(motorRightBack, OUTPUT);
  pinMode(motorLeftGo, OUTPUT);
  pinMode(motorLeftBack, OUTPUT);
}

void loop() {
  if (Serial.available()) {
    mySerial.write(Serial.read());
  }
  while(mySerial.available()) {
    switch (mySerial.read()) {
      case 103: //get "g" command, it stand for "go forward"
        goForward();
        Serial.println("go");
        break;
      case 108: //get "l" command, it stand for "turn left"
        turnLeft();
        Serial.println("left");
        break;
      case 114: //get "r" command, it stand for "turn right"
        turnRight();
        Serial.println("right");
        break;
      case 98: //get "b" command, it stand for "go back"
        goBack();
        Serial.println("back");
        break;
      case 115: //get "s" command, it stand for "stop"
        stopEveryMotor();
        Serial.println("stop");
        break;
      case 13:
        Serial.println("NL");
        break;
      case 10:
        Serial.println("CR");
        break;
      default: //command that can't recognize
        stopEveryMotor();
        break;
    }
  }
}

void goForward() {
  digitalWrite(motorRightGo, HIGH);
  digitalWrite(motorRightBack, LOW);
  digitalWrite(motorLeftGo, HIGH);
  digitalWrite(motorLeftBack, LOW);
}

void turnLeft() {
  digitalWrite(motorRightGo, HIGH);
  digitalWrite(motorRightBack, LOW);
  digitalWrite(motorLeftGo, LOW);
  digitalWrite(motorLeftBack, HIGH);
}

void turnRight() {
  digitalWrite(motorRightGo, LOW);
  digitalWrite(motorRightBack, HIGH);
  digitalWrite(motorLeftGo, HIGH);
  digitalWrite(motorLeftBack, LOW);
}

void goBack() {
  digitalWrite(motorRightGo, LOW);
  digitalWrite(motorRightBack, HIGH);
  digitalWrite(motorLeftGo, LOW);
  digitalWrite(motorLeftBack, HIGH);
}

void stopEveryMotor() {
  digitalWrite(motorRightGo, LOW);
  digitalWrite(motorRightBack, LOW);
  digitalWrite(motorLeftGo, LOW);
  digitalWrite(motorLeftBack, LOW);
}

