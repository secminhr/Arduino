#include <Ultrasonic.h>
#include<ESP8266WiFi.h>
#define motorAGo D4
#define motorABack D7
#define motorBGo D2
#define motorBBack D1
#define trig_pin D6
#define echo_pin D5

const char* ssid = "ZyXEL5F69AC";
const char* password = "qaz12345";
WiFiServer server(80);
Ultrasonic ultra(trig_pin, echo_pin);
double distance;

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (!WiFi.isConnected()) {
    Serial.println("Not connected yet");
    delay(500);
  }
  server.begin();
  digitalWrite(LED_BUILTIN, LOW);
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
  pinMode(motorAGo, OUTPUT);
  pinMode(motorABack, OUTPUT);
  pinMode(motorBGo, OUTPUT);
  pinMode(motorBBack, OUTPUT);
  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
}

void loop() {
  distance = ultra.distanceRead();
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
  client.println("<button onClick=\"forward()\">Move Forward</button>");
  client.println("<br>");
  client.println("<button onClick=\"right()\">Turn Right</button>");
  client.println("<br>");
  client.println("<button onClick=\"left()\">Turn Left</button>");
  client.println("<br>");
  client.println("<button onClick=\"backward()\">Move Backward</button>");
  client.println("<br>");
  client.println("<button onClick=\"stop()\">Stop</button>");
  client.println("<br>");
  client.print("<p>Distance in front of the car: ");
  client.print(distance);
  client.println("cm.</p>");
  client.println("<script>");
  client.println("setTimeout(function(){window.location.reload(1);}, 5000);");
  client.println("function forward() {");
  client.println("var requestObj = new XMLHttpRequest();");
  client.println("requestObj.open(\'GET\', \"FORWARD\", true);");
  client.println("requestObj.send();");
  client.println("}");
  client.println("function right() {");
  client.println("var requestObj = new XMLHttpRequest();");
  client.println("requestObj.open(\'GET\', \"RIGHT\", true);");
  client.println("requestObj.send();");
  client.println("}");
  client.println("function left() {");
  client.println("var requestObj = new XMLHttpRequest();");
  client.println("requestObj.open(\'GET\', \"LEFT\", true);");
  client.println("requestObj.send();");
  client.println("}");
  client.println("function backward() {");
  client.println("var requestObj = new XMLHttpRequest();");
  client.println("requestObj.open(\'GET\', \"BACKWARD\", true);");
  client.println("requestObj.send();");
  client.println("}");
  client.println("function stop() {");
  client.println("var requestObj = new XMLHttpRequest();");
  client.println("requestObj.open(\'GET\', \"STOP\", true);");
  client.println("requestObj.send();");
  client.println("}");
  client.println("</script>");
  client.println("</body>");
  client.println("</html>");
}

void moveForward() {
  digitalWrite(motorAGo, HIGH);
  digitalWrite(motorABack, LOW);
  digitalWrite(motorBGo, HIGH);
  digitalWrite(motorBBack, LOW);
}
void turnRight() {
  digitalWrite(motorAGo, LOW);
  digitalWrite(motorABack, HIGH);
  digitalWrite(motorBGo, HIGH);
  digitalWrite(motorBBack, LOW);
}
void turnLeft() {
  digitalWrite(motorAGo, HIGH);
  digitalWrite(motorABack, LOW);
  digitalWrite(motorBGo, LOW);
  digitalWrite(motorBBack, HIGH);
}
void moveBackward() {
  digitalWrite(motorAGo, LOW);
  digitalWrite(motorABack, HIGH);
  digitalWrite(motorBGo, LOW);
  digitalWrite(motorBBack, HIGH);
}
void stopMove() {
  digitalWrite(motorAGo, LOW);
  digitalWrite(motorABack, LOW);
  digitalWrite(motorBGo, LOW);
  digitalWrite(motorBBack, LOW);
}
