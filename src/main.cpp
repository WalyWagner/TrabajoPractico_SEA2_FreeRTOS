#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "config.h"
#include "types/index.h"

// Task handles
TaskHandle_t buttonTaskHandle = NULL;
TaskHandle_t adcTaskHandle = NULL;
TaskHandle_t ledTaskHandle = NULL;
TaskHandle_t wifiTaskHandle = NULL;
TaskHandle_t webServerTaskHandle = NULL;

// Function prototypes
void buttonTask(void *pvParameters);
void adcTask(void *pvParameters);
void ledTask(void *pvParameters);
void wifiTask(void *pvParameters);
void webServerTask(void *pvParameters);

// Define the variables here
int counterSamples = 0;
ADCMeasurement samples[ADC_MEASUREMENT_COUNT]; // Array to store ADC samples

void setup() {
    Serial.begin(115200); // Initialize serial communication
    pinMode(BUTTON_PIN, INPUT_PULLUP); // Configure button pin as input with pull-up
    pinMode(LED_PIN, OUTPUT); // Configure LED pin as output

    // Create tasks
    xTaskCreate(buttonTask, "Button Task", BUTTON_TASK_STACK_SIZE, NULL, BUTTON_TASK_PRIORITY, &buttonTaskHandle);
    xTaskCreate(wifiTask, "WiFi Task", WIFI_TASK_STACK_SIZE, NULL, WIFI_TASK_PRIORITY, &wifiTaskHandle);
    xTaskCreate(webServerTask, "WebServer Task", WEBSERVER_TASK_STACK_SIZE, NULL, WEBSERVER_TASK_PRIORITY, &webServerTaskHandle);
}

void loop() {
    // The loop is intentionally left empty as FreeRTOS handles task scheduling
}