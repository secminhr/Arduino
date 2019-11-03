#include<ESP8266WiFi.h>

const char* ssid = "ii-home";
const char* password = "0936225432";
void setup() {
  //connect to wifi, and show the ip
  WiFi.mode(WIFI_STA);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while(!WiFi.isConnected()) {
    delay(500);
    Serial.println("Not connected yet");
  }
  Serial.println(WiFi.localIP());
}

void loop() {
  //bridge between johnnyFive and uno
  digitalWrite(LED_BUILTIN, HIGH);
  if (Serial.available()){
    Serial.println(Serial.read());
  }
}
