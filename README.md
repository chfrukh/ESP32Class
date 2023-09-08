# ESP32 Blynk IoT Project

This project demonstrates how to create an IoT project with an ESP32 microcontroller, Blynk, a DHT11 temperature and humidity sensor, and an ultrasonic distance sensor. With this project, you can remotely monitor temperature, humidity, and distance using the Blynk mobile app.

## Table of Contents

- [Overview](#overview)
- [Prerequisites](#prerequisites)
- [Hardware Setup](#hardware-setup)
- [Software Setup](#software-setup)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

## Overview

This IoT project combines an ESP32 with two sensors: the DHT11 sensor for temperature and humidity readings and the ultrasonic distance sensor. It sends sensor data to the Blynk mobile app, allowing you to monitor and visualize the environment remotely.

## Prerequisites

Before you begin, ensure you have the following:

- ESP32 microcontroller
- DHT11 temperature and humidity sensor
- Ultrasonic distance sensor
- Blynk account and authentication token
- Arduino IDE with the ESP32 board package installed

## Hardware Setup

1. Connect the DHT11 sensor to the ESP32's GPIO pin (e.g., pin 4).
2. Connect the ultrasonic distance sensor to the ESP32's GPIO pins (e.g., trigger to pin 5, echo to pin 6).
3. Make sure your hardware connections are secure and free from loose wires.

## Software Setup

1. Clone or download this repository to your local machine.
2. Open the Arduino IDE and install the Blynk, DHT, and ESP32 libraries if not already installed.
3. Replace the placeholders in the code (SSID, Password, Blynk Auth Token) with your actual Wi-Fi credentials and Blynk authentication token.
4. Upload the code to your ESP32 using the Arduino IDE.
5. Set up a Blynk project in the Blynk mobile app and create three value display widgets linked to virtual pins V0 (temperature), V1 (humidity), and V2 (distance).

## Usage

1. Power up your ESP32.
2. Open the Blynk mobile app and ensure it's connected to your project.
3. Use the Blynk app to monitor real-time temperature, humidity, and distance readings.

## Contributing

If you would like to contribute to this project or make improvements, feel free to fork the repository and submit a pull request. Contributions are welcome.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

