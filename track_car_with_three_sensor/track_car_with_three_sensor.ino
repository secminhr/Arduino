//馬達設定依照講義 改pin腳請改後方數字
#define leftMotorForward 10 
#define leftMotorBackward 11
#define rightMotorForward 6
#define rightMotorBackward 5
//循跡感測器 不按照講義(講義作法不是最佳) 改pin腳請改後方數字
#define leftSensor 2
#define middleSensor 3
#define rightSensor 4

void setup() {
  pinMode(leftMotorForward, OUTPUT);
  pinMode(leftMotorBackward, OUTPUT);
  pinMode(rightMotorForward, OUTPUT);
  pinMode(rightMotorBackward, OUTPUT);
  pinMode(leftSensor, INPUT);
  pinMode(middleSensor, INPUT);
  pinMode(rightSensor, INPUT);
}

void loop() {
  if(isOnTrack(middleSensor)) {
    moveForward();
  } else {
    if(isOnTrack(leftSensor)) {
      turnLeft();
    } else if (isOnTrack(rightSensor)) {
      turnRight();
    } else {
      moveBackward();
    }
  }
}

bool isOnTrack(int pin) {
  return digitalRead(pin) == LOW;
}

void moveForward() {
  digitalWrite(rightMotorForward, HIGH);
  digitalWrite(rightMotorBackward, LOW);
  digitalWrite(leftMotorForward, HIGH);
  digitalWrite(leftMotorBackward, LOW);
}
void turnRight() {
  digitalWrite(rightMotorForward, LOW);
  digitalWrite(rightMotorBackward, HIGH);
  digitalWrite(leftMotorForward, HIGH);
  digitalWrite(leftMotorBackward, LOW);
}
void turnLeft() {
  digitalWrite(rightMotorForward, HIGH);
  digitalWrite(rightMotorBackward, LOW);
  digitalWrite(leftMotorForward, LOW);
  digitalWrite(leftMotorBackward, HIGH);
}
void moveBackward() {
  digitalWrite(rightMotorForward, LOW);
  digitalWrite(rightMotorBackward, HIGH);
  digitalWrite(leftMotorForward, LOW);
  digitalWrite(leftMotorBackward, HIGH);
}
void stopMove() {
  digitalWrite(rightMotorForward, LOW);
  digitalWrite(rightMotorBackward, LOW);
  digitalWrite(leftMotorForward, LOW);
  digitalWrite(leftMotorBackward, LOW);
}

