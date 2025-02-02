#ifndef CONFIG_H
#define CONFIG_H

// Pin definitions
#define BUTTON_PIN 5
#define LED_PIN 18
#define ADC_PIN 34

// ADC configuration
#define ADC_RESOLUTION 12
#define SAMPLE_RATE 6000 // 6 kSPS

// Task stack sizes
#define BUTTON_TASK_STACK_SIZE 2048 // Stack size for button task
#define LED_TASK_STACK_SIZE 1024 // Stack size for LED task
#define ADC_TASK_STACK_SIZE 10000 // Increase stack size for ADC task
#define WIFI_TASK_STACK_SIZE 4096 // Stack size for WiFi task
#define WEBSERVER_TASK_STACK_SIZE 50000 // Stack size for WebServer task

// Task priorities
#define BUTTON_TASK_PRIORITY 1
#define ADC_TASK_PRIORITY 5
#define LED_TASK_PRIORITY 4
#define WIFI_TASK_PRIORITY 4
#define WEBSERVER_TASK_PRIORITY 3

// Timing configurations
#define ADC_MEASUREMENT_DURATION 3000 // in milliseconds
#define ADC_MEASUREMENT_COUNT 3000 // in counts
#define RANDOM_DELAY_MIN 2000 // in milliseconds
#define RANDOM_DELAY_MAX 5000 // in milliseconds

// WiFi configuration
#define WIFI_SSID "Pb 2.4"
#define WIFI_PASSWORD "DELUNOALOCHO"

#endif // CONFIG_H