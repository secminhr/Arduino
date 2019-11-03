#define motorRightGo 6
#define motorRightBack 5
#define motorLeftGo 10
#define motorLeftBack 11

void setup() {
  pinMode(motorRightGo, OUTPUT);
  pinMode(motorRightBack, OUTPUT);
  pinMode(motorLeftGo, OUTPUT);
  pinMode(motorLeftBack, OUTPUT);
}

void loop() {
  goForward();
  delay(1000);
  turnLeft();
  delay(1000);
  turnRight();
  delay(1000);
  goBack();
  delay(1000);
}

void goForward() {
  digitalWrite(motorRightGo, HIGH);
  digitalWrite(motorRightBack, LOW);
  digitalWrite(motorLeftGo, HIGH);
  digitalWrite(motorLeftBack, LOW);
  delay(1000);
}

void turnLeft() {
  digitalWrite(motorRightGo, HIGH);
  digitalWrite(motorRightBack, LOW);
  digitalWrite(motorLeftGo, LOW);
  digitalWrite(motorLeftBack, HIGH);
  delay(1000);
}

void turnRight() {
  digitalWrite(motorRightGo, LOW);
  digitalWrite(motorRightBack, HIGH);
  digitalWrite(motorLeftGo, HIGH);
  digitalWrite(motorLeftBack, LOW);
  delay(1000);
}

void goBack() {
  digitalWrite(motorRightGo, LOW);
  digitalWrite(motorRightBack, HIGH);
  digitalWrite(motorLeftGo, LOW);
  digitalWrite(motorLeftBack, HIGH);
  delay(1000);
}

