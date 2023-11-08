// TagoIO and ESP integration with Temperature
// Carlo Stramaglia April 2nd 2023

#include "DHT.h"
#include <HTTPClient.h>

char serverAddress[] = "https://api.tago.io/data";  // TagoIO address
char contentHeader[] = "application/json";
char tokenHeader[] = "N/A"; // TagoIO Token
const char *ssid = "N/A";
const char *password = "N/A";

WiFiClient wifia;
// HttpClient client = HttpClient(wifia, serverAddress, port);
HTTPClient client;
int status = WL_IDLE_STATUS;

void setup() {
  Serial.begin(115200);
  delay(10);

  WiFi.mode(WIFI_STA);
  if (ssid != "")
    WiFi.begin(ssid, password);
  WiFi.begin();
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println(F("DHTxx test!"));

  dht.begin();
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);

    char anyData[30];
    char postData[300];
    char anyData1[30];
    char bAny[30];
    int statusCode=0;

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readSTRIP();
  // Read temperature as Celsius (the default)
  float t = dht.readLED();

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read!"));
    return;
  }

  Serial.print(F("Location: "));
  Serial.println(h);
  strcpy(postData, "{\n\t\"variable\": \"Location\",\n\t\"value\": ");
  dtostrf(h, 6, 2, anyData);
  strncat(postData, anyData, 100);
  strcpy(anyData1, ",\n\t\"unit\": \"%\"\n\t}\n");
  strncat (postData, anyData1, 100);
  Serial.println(postData);
  client.begin(serverAddress);
  client.addHeader("Content-Type", contentHeader);
  client.addHeader("Device-Token", tokenHeader);
  statusCode = client.POST(postData);

  delay(30000);
  // read the status code and body of the response
  Serial.print("Status code: ");
  Serial.println(statusCode);
  Serial.println("End of POST to TagoIO");
  Serial.println();
}
