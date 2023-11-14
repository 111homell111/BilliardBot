#include <WiFi.h>
#include <ESPAsyncWebSrv.h>
#include <SPIFFS.h> 

const char* ssid = "none";
const char* password = "12345678";

AsyncWebServer server(80);

int ledPin = 27; // GPIO5 (G5) is the pin where the LED is connected
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

  if(!SPIFFS.begin(true)){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  // Serve HTML for the root directory
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", "text/html");
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
    request->redirect("/");
  });

  server.begin();
}

void loop() {
  // Your code here
}
