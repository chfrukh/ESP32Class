#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "Your_Temp_ID" // Replace "Your_Temp_ID" with your Blynk Template ID
#define BLYNK_TEMPLATE_NAME "Your_Temp_Name" // Replace "Your_Temp_Name" with your Blynk Temolate Name
#define BLYNK_AUTH_TOKEN "Your_Auth_Token" // Replace "Your_Auth_Token" with your Blynk Auth Token
#include <WiFi.h> // Library for Wi-Fi connectivity
#include <BlynkSimpleEsp32.h> // Library for Blynk IoT platform

// Define your Wi-Fi credentials
char ssid[] = "Your_SSID"; // Replace "your_SSID" with your Wi-Fi network name (SSID)
char pass[] = "Your_Password"; // Replace "your_PASSWORD" with your Wi-Fi network password

// HC-SR04 connections
const int trigPin = 4; // Connect the trigger pin of the HC-SR04 sensor to GPIO pin 4
const int echoPin = 14; // Connect the echo pin of the HC-SR04 sensor to GPIO pin 2

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

  // Set up HC-SR04 pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // Run Blynk tasks
  Blynk.run();

  // Measure distance using the HC-SR04 sensor
  long duration;
  float distance_cm;

  // Trigger the sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the echo duration
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate distance in centimeters
  distance_cm = duration * 0.034 / 2.0;

  // Convert centimeters to inches
  float inch = distance_cm / 2.54;

  // Send the distance data to Blynk on Virtual Pin V1
  Blynk.virtualWrite(V1, inch);
  //Serial.println(inch);

  // Wait for a moment before taking the next measurement
  delay(1);
}
