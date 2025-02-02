#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "config.h"
#include "../types/index.h"
#include <esp_heap_caps.h>

// Handle for the button task
extern TaskHandle_t buttonTaskHandle;
extern TaskHandle_t webServerTaskHandle;

// External variables
extern int counterSamples;
extern ADCMeasurement samples[ADC_MEASUREMENT_COUNT]; // Array to store ADC samples

void adcTask(void *pvParameters) {
    const int maxSamples = ADC_MEASUREMENT_COUNT;
    analogReadResolution(ADC_RESOLUTION); // Set ADC resolution
    
    TickType_t startTime = xTaskGetTickCount(); // Task start time
    TickType_t endTime = startTime + pdMS_TO_TICKS(ADC_MEASUREMENT_DURATION); // Task end time

    Serial.print("ADC Task running... \n Total samples: ");
    Serial.println(counterSamples); Serial.println(maxSamples);
    while (xTaskGetTickCount() < endTime && counterSamples < maxSamples) {
        samples[counterSamples].value = analogRead(ADC_PIN); // Read ADC value
        samples[counterSamples].timestamp = (xTaskGetTickCount() - startTime) * portTICK_PERIOD_MS; // Store sample timestamp
        counterSamples++;    

        vTaskDelay(1); // Delay for sampling rate
    }

    Serial.print("ADC Task running... \n Total samples: ");
    Serial.println(counterSamples);
    for (int i = 0; i < counterSamples; i++) {
        Serial.print("Sample ");
        Serial.print(i);
        Serial.print(" - Time: ");
        Serial.print(samples[i].timestamp);
        Serial.print(" ms, Value: ");
        Serial.println(samples[i].value);
    }
    
    // Notify the web server task that new data is available
    xTaskNotifyGive(webServerTaskHandle);

    vTaskDelete(NULL); // Delete the ADC task
}