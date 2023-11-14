#include <WiFi.h>
#include <ESPAsyncWebSrv.h>

const char* ssid = "none";
const char* password = "12345678";

AsyncWebServer server(80);

int ledPin = 27; // GPIO5 (G27) is the pin where the LED is connected
bool ledState = LOW;

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, ledState);

  Serial.begin(115200);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", "Hello, ESP32!");
  });

  server.on("/control", HTTP_GET, [](AsyncWebServerRequest *request){
    String command = request->arg("cmd");
    if (command == "1") {
      digitalWrite(ledPin, HIGH);
      ledState = HIGH;
    } else if (command == "0") {
      digitalWrite(ledPin, LOW);
      ledState = LOW;
    }
    request->send(200, "text/plain", "LED state: " + String(ledState));
  });

  server.begin();
}

void loop() {
  // Your code here
}