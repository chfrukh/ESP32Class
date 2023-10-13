# ESP32 Blynk Project

This project demonstrates how to use an ESP32 with Blynk to control three LEDs, monitor a DHT11 sensor, and control a servo motor and two fans with speed control.

## Prerequisites

Before you begin, you need the following:

1. ESP32 board (e.g., ESP-WROOM-32).
2. Blynk account. (Download the Blynk app from your app store and sign up for an account).
3. Arduino IDE installed.
4. Libraries: Blynk, Servo, DHT.

## Setup Blynk App

1. Install the Blynk app on your mobile device.
2. Create a new Blynk project.
3. Write down the "Auth Token" sent to your email.

## Wiring

- Connect the DHT11 sensor to pin 2.
- Connect the servo motor to pin 25.
- Connect three LEDs to pins 12, 14, and 27.
- Connect two fans to pins 26 and 33 for speed control.

## Upload Code

1. Open the Arduino IDE.
2. Set up your Arduino IDE for the ESP32 board.
3. Install the necessary libraries (Blynk, Servo, DHT) via the Arduino Library Manager.
4. Open the provided `.ino` file in the IDE.
5. Update `auth`, `ssid`, and `pass` with your Blynk Auth Token and Wi-Fi credentials.
6. Customize pin configurations if needed.
7. Upload the code to your ESP32.

## Blynk Configuration

1. Open the Blynk app.
2. Create a new project.
3. Add buttons (V6, V7, V8), sliders (V9, V10), and a display (V1, V2) widgets.
4. Connect each widget to your ESP32 using the corresponding virtual pin numbers.
5. Configure the widgets to control LEDs, fans, and display sensor data.
6. Add a button (V5) and a slider (V4) to control the servo motor.
7. Deploy the project and run it.

## Usage

1. Open the Blynk app and start the project.
2. Control the LEDs with buttons.
3. Control the fans with sliders.
4. Monitor the temperature and humidity with the display widget.
5. Control the servo motor with the button and slider.

## License

This project is licensed under the MIT License.

## Acknowledgments

- [Blynk](https://blynk.io/) - For the Blynk IoT platform.
- [Adafruit](https://www.adafruit.com/) - For the DHT library.

## Troubleshooting

- If you encounter issues, check your Wi-Fi and Blynk token settings.
- Ensure your ESP32 is correctly wired.

