
#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "esp_sleep.h"

void sleepTask(void *pvParameters) {
    while (true) {
        Serial.println("Entering light sleep mode...");
        // Enter light sleep mode
        esp_light_sleep_start();
        // Delay to allow other tasks to run
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}