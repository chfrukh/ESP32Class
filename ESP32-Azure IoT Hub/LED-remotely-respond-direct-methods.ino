#include <Arduino.h>
#include <WiFi.h>
#include <mqtt_client.h>
#include <az_core.h>
#include <az_iot.h>
#include <azure_ca.h>
#include "AzIoTSasToken.h"
#include "SerialLogger.h"
#include "iot_configs.h"

#define AZURE_SDK_CLIENT_USER_AGENT "c%2F" AZ_SDK_VERSION_STRING "(ard;esp32)"

// ... (Constants and variables declarations)

// Function to connect to Wi-Fi using provided credentials
static void connectToWiFi()
{
    Logger.Info("Connecting to WIFI SSID " + String(ssid));

    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");

    Logger.Info("WiFi connected, IP address: " + WiFi.localIP().toString());
}

// Function to initialize time using SNTP
static void initializeTime()
{
    Logger.Info("Setting time using SNTP");

    configTime(GMT_OFFSET_SECS, GMT_OFFSET_SECS_DST, NTP_SERVERS);
    time_t now = time(NULL);
    while (now < UNIX_TIME_NOV_13_2017)
    {
        delay(500);
        Serial.print(".");
        now = time(nullptr);
    }
    Serial.println("");
    Logger.Info("Time initialized!");
}

// Function to set the LED state based on the command received
static void setLedState(bool level)
{
    if (level)
    {
        Logger.Info("Turning LED ON");
        digitalWrite(flashPin, HIGH);
    }
    else
    {
        Logger.Info("Turning LED OFF");
        digitalWrite(flashPin, LOW);
    }
    ledState = level;
}

// Callback function to handle received direct methods
void receivedCallback(char *method, char *payload, unsigned int method_length)
{
    Logger.Info("Received [");
    Logger.Info(method);
    Logger.Info("]: ");
    for (int i = 0; i < method_length; i++)
    {
        Serial.print((char)payload[i]);
    }

    if (strncmp((char *)method, SET_LED_STATE_COMMAND, method_length) == 0)
    {
        bool arg = (strncmp((char *)payload, "true", method_length) == 0);
        setLedState(arg);
    }

    Serial.println("");
}

// MQTT event handler function
static esp_err_t mqtt_event_handler(esp_mqtt_event_handle_t event)
{
    switch (event->event_id)
    {
    case MQTT_EVENT_ERROR:
        Logger.Info("MQTT event MQTT_EVENT_ERROR");
        break;
    case MQTT_EVENT_CONNECTED:
        Logger.Info("MQTT event MQTT_EVENT_CONNECTED");
        esp_mqtt_client_subscribe(mqtt_client, AZ_IOT_HUB_CLIENT_C2D_SUBSCRIBE_TOPIC, 1);
        break;
    case MQTT_EVENT_DISCONNECTED:
        Logger.Info("MQTT event MQTT_EVENT_DISCONNECTED");
        break;
    case MQTT_EVENT_SUBSCRIBED:
        Logger.Info("MQTT event MQTT_EVENT_SUBSCRIBED");
        break;
    case MQTT_EVENT_UNSUBSCRIBED:
        Logger.Info("MQTT event MQTT_EVENT_UNSUBSCRIBED");
        break;
    case MQTT_EVENT_PUBLISHED:
        Logger.Info("MQTT event MQTT_EVENT_PUBLISHED");
        break;
    case MQTT_EVENT_DATA:
        receivedCallback(event->topic, event->data, event->data_len);
        break;
    case MQTT_EVENT_BEFORE_CONNECT:
        Logger.Info("MQTT event MQTT_EVENT_BEFORE_CONNECT");
        break;
    default:
        Logger.Error("MQTT event UNKNOWN");
        break;
    }
    return ESP_OK;
}

// Initialize the IoT Hub client
static void initializeIoTHubClient()
{
    az_iot_hub_client_options options = az_iot_hub_client_options_default();
    options.user_agent = AZ_SPAN_FROM_STR(AZURE_SDK_CLIENT_USER_AGENT);

    if (az_result_failed(az_iot_hub_client_init(
            &client,
            az_span_create((uint8_t *)host, strlen(host)),
            az_span_create((uint8_t *)device_id, strlen(device_id)),
            &options)))
    {
        Logger.Error("Failed initializing Azure IoT Hub client");
        return;
    }

    size_t client_id_length;
    if (az_result_failed(az_iot_hub_client_get_client_id(
            &client, mqtt_client_id, sizeof(mqtt_client_id) - 1, &client_id_length)))
    {
        Logger.Error("Failed getting client id");
        return;
    }

    if (az_result_failed(az_iot_hub_client_get_user_name(
            &client, mqtt_username, sizeofarray(mqtt_username), NULL)))
    {
        Logger.Error("Failed to get MQTT clientId, return code");
        return;
    }

    Logger.Info("Client ID: " + String(mqtt_client_id));
    Logger.Info("Username: " + String(mqtt_username));
}

// Initialize the MQTT client
static int initializeMqttClient()
{
    if (sasToken.Generate(SAS_TOKEN_DURATION_IN_MINUTES) != 0)
    {
        Logger.Error("Failed generating SAS token");
        return 1;
    }

    esp_mqtt_client_config_t mqtt_config;
    memset(&mqtt_config, 0, sizeof(mqtt_config));
    mqtt_config.uri = mqtt_broker_uri;
    mqtt_config.port = mqtt_port;
    mqtt_config.client_id = mqtt_client_id;
    mqtt_config.username = mqtt_username;
    mqtt_config.password = (const char *)az_span_ptr(sasToken.Get());
    mqtt_config.keepalive = 30;
    mqtt_config.disable_clean_session = 0;
    mqtt_config.disable_auto_reconnect = false;
    mqtt_config.event_handle = mqtt_event_handler;
    mqtt_config.user_context = NULL;
    mqtt_config.cert_pem = (const char *)ca_pem;

    mqtt_client = esp_mqtt_client_init(&mqtt_config);

    if (mqtt_client == NULL)
    {
        Logger.Error("Failed creating mqtt client");
        return 1;
    }

    esp_err_t start_result = esp_mqtt_client_start(mqtt_client);

    if (start_result != ESP_OK)
    {
        Logger.Error("Could not start mqtt client; error code:" + start_result);
        return 1;
    }
    else
    {
        Logger.Info("MQTT client started");
        return 0;
    }
}
