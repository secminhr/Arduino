#include <SoftwareSerial.h>
#define RX 10
#define TX 11
#define motorRightGo 2
#define motorRightBack 3
#define motorLeftGo 5
#define motorLeftBack 4

SoftwareSerial myWifi(RX, TX);


void setup() {
  myWifi.begin(115200);
  Serial.begin(115200);
  pinMode(motorRightGo, OUTPUT);
  pinMode(motorRightBack, OUTPUT);
  pinMode(motorLeftGo, OUTPUT);
  pinMode(motorLeftBack, OUTPUT);
}

void loop() {
  if (myWifi.available()) {
    while(myWifi.available()) {
      Serial.println(myWifi.read());
    }
  }
  if (Serial.available()) {
    myWifi.write(Serial.read());
  }
  if (myWifi.find("+IPD,")) { //接到連線要求
    int idToConnect = myWifi.read() - 48;
    String webCode = "<!DOCTYPE html><html><head><title>arduino_website</title>";
    webCode += "<script type=text/javascript>function moveGo(){alert(1)}function moveLeft(){alert(2)}";
    webCode += "function moveRight(){alert(3)}function moveBack(){alert(4)}</script>";
    webCode += "</head><body><Button onClick = moveGo()>Go</Button><Button onClick = moveLeft()>Turn Left</Button>";
    webCode += "<Button onClick = moveRight()>Turn Right</Button><Button onClick = moveBack()>Back</Button></body></html>";
    String cipSend = "AT+CIPSEND=";
    cipSend += idToConnect;
    cipSend += ",";
    cipSend += webCode.length();
    cipSend += "\r\n";
    sendData(webCode);
    sendData(cipSend);
  }
}

String sendData(String command) {
  myWifi.print(command);
  while(myWifi.available()) {
    Serial.println(myWifi.read());
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
