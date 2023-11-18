#include <WiFi.h>
#include <ThingSpeak.h>
#include <ESPAsyncWebServer.h>
#include <ESPAsyncWiFiManager.h>

const char* ssid = "ssid";
const char* password = "password";
const char* thingSpeakApiKey = "thingSpeakAPIkey";

const int buttonPin = 2; // Button pin
const int ledPin = 4;    // LED pin

AsyncWebServer server(80);

bool ledState = false;

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi using ESPAsyncWiFiManager
  AsyncWiFiManager wifiManager(&server);
  wifiManager.autoConnect("ESP32-Button-Light");

  // Initialize ThingSpeak
  ThingSpeak.begin(client);

  // Set up GPIO pins
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);

  // Set up server routes
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", "Hello, ESP32!");
  });

  server.on("/update", HTTP_GET, [](AsyncWebServerRequest *request){
    if (request->hasParam("state")) {
      ledState = request->getParam("state")->value().toInt();
      digitalWrite(ledPin, ledState);
    }
    request->send(200, "text/plain", "OK");
  });

  server.begin();
}

void loop() {
  // Read button state
  int buttonState = digitalRead(buttonPin);

  // If the button is pressed, send an update to ThingSpeak
  if (buttonState == LOW) {
    ThingSpeak.writeField(1, 1, ledState, thingSpeakApiKey);
    delay(500); // debounce
  }
}

