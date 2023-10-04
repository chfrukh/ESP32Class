# ESP32-CAM Image Capture and API Upload

This project demonstrates how to capture images using the ESP32-CAM and send them to an API endpoint in base64 format. The captured image is encoded and sent as a JSON payload to the specified API endpoint.

## Prerequisites

Before running this project, make sure you have the following:

- Arduino IDE installed.
- ESP32 board support installed in Arduino IDE.
- Base64 library installed in Arduino IDE.
- A working Wi-Fi connection.
- Access to the API endpoint where you want to send the images.

## Setup

1. Clone or download this repository to your local machine.

2. Open the `esp32_cam_image_capture.ino` file in the Arduino IDE.

3. Update the following variables in the code:
   - `ssid`: Your Wi-Fi network name (SSID).
   - `password`: Your Wi-Fi network password.
   - `apiEndpoint`: The URL of the API endpoint where you want to send the images.

4. Connect your ESP32-CAM to your computer using a USB cable.

5. Select the ESP32 board type and port in the Arduino IDE.

6. Upload the code to your ESP32-CAM.

7. Open the Serial Monitor in the Arduino IDE to view the status and debug information.

8. The ESP32-CAM will capture an image and send it to the specified API endpoint.

## Troubleshooting

- If you encounter issues with the image format or the API, check the API documentation for the expected format and adjust the code accordingly.

- Ensure that the ESP32-CAM is connected to a stable Wi-Fi network.

- Verify that the ESP32 board support and required libraries are correctly installed in your Arduino IDE.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- This project uses the ESP32-CAM library.
- Base64 encoding is done using the Base64 library for Arduino.
