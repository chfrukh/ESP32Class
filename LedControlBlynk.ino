#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "Add Your Own Temp ID"
#define BLYNK_TEMPLATE_NAME "Add Your Own Temp Name"
#define BLYNK_AUTH_TOKEN "Add Your Own Auth Token"
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

// WiFi credentials
const char* ssid = "Add WIFI SSID";
const char* pass ="Add WIFI Password";
const int ledPin = 2;

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

  // Your other code here (if any)
}

// Function to handle the V1 button state change
void ledButtonPressed(int ledState) {
  digitalWrite(ledPin, ledState); // Set the LED state based on the button state
}