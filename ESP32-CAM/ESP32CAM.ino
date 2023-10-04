#include "esp_camera.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include "Base64.h"

const char* ssid = "Your_SSID";
const char* password = "Your_Password";
const char* apiEndpoint = "Your_API_Endpoint"; // Replace with your API endpoint

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Initialize the camera
  camera_config_t config;
  config.frame_size = FRAMESIZE_QVGA;
  config.jpeg_quality = 10;
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    return;
  }

  // Capture an image
  camera_fb_t *fb = esp_camera_fb_get();
  if (!fb) {
    Serial.println("Camera capture failed");
    return;
  }

  // Encode the image in base64
  String encodedImage = base64_encode(fb->buf, fb->len);

  // Send the image to the API
  HTTPClient http;
  http.begin(apiEndpoint);
  http.addHeader("Content-Type", "application/json");

  String jsonPayload = "{\"image\":\"" + encodedImage + "\"}";

  int httpResponseCode = http.POST(jsonPayload);

  if (httpResponseCode > 0) {
    Serial.printf("HTTP Response code: %d\n", httpResponseCode);
    String response = http.getString();
    Serial.println(response);
  } else {
    Serial.printf("HTTP Error: %s\n", http.errorToString(httpResponseCode).c_str());
  }

  http.end();

  // Return the image buffer
  esp_camera_fb_return(fb);
}

void loop() {
  // Your main code, if any, goes here
}
