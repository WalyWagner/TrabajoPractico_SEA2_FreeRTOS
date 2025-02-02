# ESP32 FreeRTOS Project

This project is part of a practical assignment for the course SISTEMAS EMBEBIDOS AVANZADOS 2.

## Author
- **Name**: Walter S. Wagner
- **Email**: wagner@fceia.unr.edu.ar

## Project Description
This project demonstrates the use of FreeRTOS on an ESP32 to manage multiple tasks, including reading from an ADC, controlling an LED, and handling a button press. The ADC readings are displayed on the serial monitor.

## Project Structure

esp32-freertos-project  
├── src  
│ ├── main.cpp // Entry point of the application  
│ ├── tasks  
│ │ ├── adc_task.cpp // Implementation of the ADC task  
│ │ ├── button_task.cpp // Implementation of the button task  
│ │ ├── led_task.cpp // Management of the LED indicator  
│ │ ├── sleep_task.cpp // Implementation of the sleep task  
│ │ ├── webserver_task.cpp // Implementation of the webserver task  
│ │ └── wifi_task.cpp // Implementation of the WiFi task  
│ └── types  
│ └── index.h // Type definitions and structures  
├── include  
│ └── config.h // Configuration settings  
├── platformio.ini // PlatformIO configuration file  
└── README.md // Project documentation  

## Task Descriptions
- **Button Task**: Monitors the button state and creates the LED and ADC tasks when the button is pressed.
- **ADC Task**: Collects analog measurements for 2 seconds and stores the values with timestamps.
- **LED Task**: Controls the LED indicator based on signals from the button and ADC tasks.
- **Sleep Task**: Manages the sleep mode of the ESP32.
- **Webserver Task**: Hosts a web server to display ADC readings.
- **WiFi Task**: Manages the WiFi connection.

## Notes
- Ensure that the button and LED are connected to the correct pins as defined in `config.h`.
- Modify the configuration settings in `config.h` as needed for your specific hardware setup.

## License
This project is closed source. No one is allowed to use, modify, or distribute this code without explicit permission from the author.