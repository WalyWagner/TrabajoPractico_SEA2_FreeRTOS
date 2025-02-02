#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <Arduino.h>
#include "config.h"
#include "../types/index.h"
#include <esp_heap_caps.h>

// Function prototypes
void ledTask(void *pvParameters);
void adcTask(void *pvParameters);

// Task handles
extern TaskHandle_t buttonTaskHandle;
extern TaskHandle_t adcTaskHandle;
extern TaskHandle_t ledTaskHandle;

// External variables
extern int counterSamples;
extern ADCMeasurement samples[ADC_MEASUREMENT_COUNT]; // Array to store ADC samples

void buttonTask(void *pvParameters) {
    pinMode(BUTTON_PIN, INPUT_PULLUP); // Configure button pin as input with pull-up
    while (true) {
        if (digitalRead(BUTTON_PIN) == LOW) { // Check if the button is pressed
            vTaskDelay(pdMS_TO_TICKS(50)); // Debounce delay
            if (digitalRead(BUTTON_PIN) == LOW) { // Check again if the button is pressed
                int randomDelay = random(RANDOM_DELAY_MIN, RANDOM_DELAY_MAX); // Generate a random delay between 2 and 5 seconds
                vTaskDelay(pdMS_TO_TICKS(randomDelay)); // Apply the random delay
                
                // Reset the sample counter and clear previous samples
                counterSamples = 0;
                memset(samples, 0, sizeof(samples));

                // Create LED and ADC tasks
                xTaskCreate(ledTask, "LED Task", LED_TASK_STACK_SIZE, NULL, LED_TASK_PRIORITY, &ledTaskHandle);
                xTaskCreate(adcTask, "ADC Task", ADC_TASK_STACK_SIZE, NULL, ADC_TASK_PRIORITY, &adcTaskHandle);
                vTaskSuspend(NULL); // Suspend the button task
            }
        }
        vTaskDelay(pdMS_TO_TICKS(10)); // Add a small delay to avoid busy-waiting
    }
}