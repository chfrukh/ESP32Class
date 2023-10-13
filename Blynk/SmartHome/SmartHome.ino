#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <Servo.h>
#include <DHT.h>

char auth[] = "YourAuthToken";
char ssid[] = "YourNetworkName";
char pass[] = "YourPassword";

// DHT Sensor
#define DHTPIN 2          // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11     // DHT 11

DHT dht(DHTPIN, DHTTYPE);

// Servo Motor
Servo doorServo;
int doorPosition = 90; // Initial position

// LEDs
int redLED = 12;
int greenLED = 14;
int blueLED = 27;

// Fans
int fan1Speed = 0;
int fan2Speed = 0;

void setup()
{
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  dht.begin();
  doorServo.attach(25);

  // Define pin modes
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
}

void loop()
{
  Blynk.run();
  int h = dht.readHumidity();
  int t = dht.readTemperature();
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  
  // Control the door with Blynk button
  doorPosition = doorServo.read();
  Blynk.virtualWrite(V5, doorPosition);
  
  // Control the LEDs with Blynk buttons
  digitalWrite(redLED, Blynk.virtualRead(V6));
  digitalWrite(greenLED, Blynk.virtualRead(V7));
  digitalWrite(blueLED, Blynk.virtualRead(V8));

  // Control fan speeds with Blynk sliders
  fan1Speed = Blynk.virtualRead(V9);
  fan2Speed = Blynk.virtualRead(V10);
  // Apply fan speed to your hardware
  analogWrite(26, fan1Speed);
  analogWrite(33, fan2Speed);

  // Send sensor data to Blynk
  Blynk.virtualWrite(V1, t);
  Blynk.virtualWrite(V2, h);
}

BLYNK_WRITE(V5) // Door servo position
{
  int pos = param.asInt();
  doorServo.write(pos);
}

void fanControl1(int fanSpeed)
{
  // Control fan 1 here
}

void fanControl2(int fanSpeed)
{
  // Control fan 2 here
}
