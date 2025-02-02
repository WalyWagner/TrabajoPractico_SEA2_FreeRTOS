#include <Arduino.h>
#include <WiFi.h>
#include "config.h"

// Function to connect to WiFi
void connectToWiFi() {
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to WiFi...");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("Connected to WiFi");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
}

void wifiTask(void *pvParameters) {
    connectToWiFi();
    vTaskDelete(NULL); // Delete the WiFi task after connecting
}