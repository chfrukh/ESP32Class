
#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "Add Your Temokate ID Here"
#define BLYNK_TEMPLATE_NAME "Add Your Template Name Here"
#define BLYNK_AUTH_TOKEN "Add Your Auth Token Here"
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h> // Include the DHT library

// WiFi credentials
const char* ssid = "Add Your WFI SSID Here";
const char* pass ="Add Your WIFI Password Here";

// DHT sensor settings
#define DHTPIN 4 // DHT11 data pin (change to the actual pin you've connected)
#define DHTTYPE DHT11 // DHT sensor type (DHT11 or DHT22)

DHT dht(DHTPIN, DHTTYPE); // Initialize the DHT sensor

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

  // Initialize the DHT sensor
  dht.begin();
}

void loop() {
  Blynk.run(); // Run Blynk tasks

  // Read humidity and temperature data from the DHT sensor
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Check if the sensor read values successfully
  if (!isnan(humidity) && !isnan(temperature)) {
    // Send humidity and temperature data to Blynk app
    Blynk.virtualWrite(V2, humidity);
    Blynk.virtualWrite(V1, temperature);
  }

  // Your other code here (if any)
}
