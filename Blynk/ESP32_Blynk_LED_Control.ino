// Include necessary libraries
#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "Your_Template_ID" // Replace with your template ID
#define BLYNK_TEMPLATE_NAME "Your_Template_Name" // Replace with your template name
#define BLYNK_AUTH_TOKEN "Your_Auth_Token" // Replace with your Blynk authentication token
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

// WiFi credentials
const char* ssid = "Your_SSID"; // Replace with your WiFi SSID
const char* pass = "Your_Password"; // Replace with your WiFi password
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
  pinMode(ledPin, OUTPUT);
}

void loop () {
  Blynk.run(); // Run Blynk tasks
}

BLYNK_WRITE(V0) {
  int pinValue = param.asInt(); // Get the value written to V0
  if (pinValue == 1) {
    digitalWrite(ledPin, HIGH); // Set pin 2 (V0) to HIGH
  } else {
    digitalWrite(ledPin, LOW); // Set pin 2 (V0) to LOW
  }
}
