#include<ESP8266WiFi.h>
#define motorAGo D6
#define motorABack D4
#define motorBGo D1
#define motorBBack D2

const char* ssid = "";
const char* password = "";
WiFiServer server(80);
void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (!WiFi.isConnected()) {
    Serial.println("Not connected yet");
    delay(500);
  }
  Serial.println("connected");
  server.begin();
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
  pinMode(motorAGo, OUTPUT);
  pinMode(motorABack, OUTPUT);
  pinMode(motorBGo, OUTPUT);
  pinMode(motorBBack, OUTPUT);
}

void loop() {
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  while(!client.available()) {
    delay(1);
  }
  String request = client.readStringUntil('\r');
  client.flush();
  if (request.indexOf("FORWARD") != -1) {
    moveForward();
  } else if (request.indexOf("RIGHT") != -1) {
    turnRight();
  } else if (request.indexOf("LEFT") != -1) {
    turnLeft();
  } else if (request.indexOf("BACKWARD") != -1) {
    moveBackward();
  } else if (request.indexOf("STOP") != -1) {
    stopMove();
  }
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<!DOCTYPE HTML>");
  client.println("<head>");
  client.println("<title>Nodemcu</title>");
  client.println("</head>");
  client.println("<body>");
  client.println("<a href=\"FORWARD\"><button>Move Forward</button></a>");
  client.println("<br>");
  client.println("<a href=\"RIGHT\"><button>Turn Right</button></a>");
  client.println("<br>");
  client.println("<a href=\"LEFT\"><button>Turn Left</button></a>");
  client.println("<br>");
  client.println("<a href=\"BACKWARD\"><button>Move Backward</button></a>");
  client.println("<br>");
  client.println("<a href=\"STOP\"><button>Stop</button></a>");
  client.println("</body>");
  client.println("</html>");
}

void moveForward() {
  digitalWrite(motorAGo, HIGH);
  digitalWrite(motorABack, LOW);
  digitalWrite(motorBGo, HIGH);
  digitalWrite(motorBBack, LOW);
  delay(1000);
}
void turnRight() {
  digitalWrite(motorAGo, LOW);
  digitalWrite(motorABack, HIGH);
  digitalWrite(motorBGo, HIGH);
  digitalWrite(motorBBack, LOW);
  delay(1000);
}
void turnLeft() {
  digitalWrite(motorAGo, HIGH);
  digitalWrite(motorABack, LOW);
  digitalWrite(motorBGo, LOW);
  digitalWrite(motorBBack, HIGH);
  delay(1000);
}
void moveBackward() {
  digitalWrite(motorAGo, LOW);
  digitalWrite(motorABack, HIGH);
  digitalWrite(motorBGo, LOW);
  digitalWrite(motorBBack, HIGH);
  delay(1000);
}
void stopMove() {
  digitalWrite(motorAGo, LOW);
  digitalWrite(motorABack, LOW);
  digitalWrite(motorBGo, LOW);
  digitalWrite(motorBBack, LOW);
  delay(1000);
}

