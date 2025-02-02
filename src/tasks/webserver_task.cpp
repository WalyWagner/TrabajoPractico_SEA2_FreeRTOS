#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include "config.h"
#include "../types/index.h"

// External variables
extern int counterSamples;
extern ADCMeasurement samples[ADC_MEASUREMENT_COUNT]; // Array to store ADC samples

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

String generateHTML() {
    String html = "<!DOCTYPE html><html><head><title>ADC Data</title>";
    html += "<style>body { font-family: Arial, sans-serif; margin: 0; padding: 0; }";
    html += "h1 { background-color: #4CAF50; color: white; padding: 10px; }";
    html += "#chart { width: 100%; height: 400px; }";
    html += "</style></head><body>";
    html += "<h1>ADC Data</h1><canvas id='chart'></canvas>";
    html += "<script src='https://cdn.jsdelivr.net/npm/chart.js'></script>";
    html += "<script>";
    html += "var ctx = document.getElementById('chart').getContext('2d');";
    html += "var chart = new Chart(ctx, {type: 'line', data: {labels: [], datasets: [{label: 'ADC Value', data: [], borderColor: 'rgba(75, 192, 192, 1)', borderWidth: 1, fill: false}]}, options: {scales: {x: {title: {display: true, text: 'Time (ms)'}}, y: {title: {display: true, text: 'ADC Value (0-4095)'}}}}});";
    html += "var ws = new WebSocket('ws://' + window.location.hostname + '/ws');";
    html += "ws.onmessage = function(event) { var data = JSON.parse(event.data); chart.data.labels = data.timestamps; chart.data.datasets[0].data = data.values; chart.update(); };";
    html += "</script></body></html>";
    return html;
}

void notifyClients() {
    String json = "{\"timestamps\":[";
    for (int i = 0; i < counterSamples; i++) {
        json += String(samples[i].timestamp);
        if (i < counterSamples - 1) {
            json += ",";
        }
    }
    json += "],\"values\":[";
    for (int i = 0; i < counterSamples; i++) {
        json += String(samples[i].value);
        if (i < counterSamples - 1) {
            json += ",";
        }
    }
    json += "]}";
    ws.textAll(json);
}

void onWebSocketEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
    if (type == WS_EVT_CONNECT) {
        Serial.println("WebSocket client connected");
    } else if (type == WS_EVT_DISCONNECT) {
        Serial.println("WebSocket client disconnected");
    }
}

void setupWebServer() {
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(200, "text/html", generateHTML());
    });
    ws.onEvent(onWebSocketEvent);
    server.addHandler(&ws);
    server.begin();
}

extern TaskHandle_t buttonTaskHandle;

void webServerTask(void *pvParameters) {
    setupWebServer();
    while (true) {
        // Wait for notification from the ADC task
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        // Notify clients with new data
        notifyClients();

        // Allow the button task to be resumed
        vTaskResume(buttonTaskHandle);
    }

    vTaskDelete(NULL); // Delete the WebServer task after setting up
}