#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL6oUL9N0_M"
#define BLYNK_TEMPLATE_NAME "Hamas ESP32"
#define BLYNK_AUTH_TOKEN "Yg30_jV7DkzfsqNJYFCAnWljCb2GJBai"
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

// WiFi credentials
const char* ssid = "OPPO F15";
const char* pass ="87654321";
const int ledPin = 2;
int ledState = 0;

void setup() {
  // Start serial communication for debugging
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");

  // Configure Blynk with your authentication token
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  pinMode(ledPin,OUTPUT);

}
void loop () {
  Blynk.run(); // Run Blynk tasks

}
BLYNK_WRITE(V0) {
  int pinValue = param.asInt(); // Get the value written to V0
  if (pinValue == 1) {
    digitalWrite(2, HIGH); // Set pin 2 (V0) to HIGH
  } else {
    digitalWrite(2, LOW); // Set pin 2 (V0) to LOW
  }
}