#include <WiFi.h>
#include <ESPAsyncWebSrv.h>

const char* ssid = "none";
const char* password = "12345678";

AsyncWebServer server(80);

int ledPin = 27; // GPIO27 is the pin where the LED is connected
bool ledState = LOW;

// Motor pins
const int motor1Pin1 = 14; // G14
const int motor1Pin2 = 12; // G12
const int motor2Pin1 = 26; // G26
const int motor2Pin2 = 25; // G25
// Define additional motors if needed

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, ledState);

  // Initialize all the motor pins as outputs
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  // Initialize additional motors if needed

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
       digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);

  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
    } else if (command == "0") {
      digitalWrite(ledPin, LOW);
      ledState = LOW;
       digitalWrite(motor1Pin1, HIGH);
       digitalWrite(motor1Pin2, LOW);

       digitalWrite(motor2Pin1, HIGH);
      digitalWrite(motor2Pin2, LOW);
    }
    request->send(200, "text/plain", "LED state: " + String(ledState));
  });

  server.begin();
}

void loop() {
  // No need to put code here for this functionality
}