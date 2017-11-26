#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

const char* ssid = "navshoes";
const char* password = "jugendhackt";
const char* side = "right";

ESP8266WebServer server(1841);

void setup(void){
  WiFi.hostname("right");
  WiFi.begin(ssid, password);
  Serial.begin(9600);

  pinMode(LED_BUILTIN, OUTPUT);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/vibrate", [](){
    server.send(200, "text/plain", "running");
    for(int i = 0; i < server.arg("times").toInt(); i++){
      digitalWrite(LED_BUILTIN, LOW);
      delay(600);
      digitalWrite(LED_BUILTIN, HIGH);
      delay(600);
    };
  });

  server.on("/status", [](){
    server.send(200, "text/plain", side);
  });

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void){
  server.handleClient();
}
