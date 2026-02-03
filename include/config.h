
#define CONFIG_H

#include <Arduino.h>

// Version
#define FIRMWARE_VERSION "1.0.0"

// WiFi AP Settings (for initial setup)
#define AP_SSID "CameraController"
#define AP_PASSWORD "camera123"

// WiFi Connection Settings (load from config.json at runtime)
// Do NOT hardcode credentials here - use data/config.json instead
#define WIFI_SSID ""
#define WIFI_PASSWORD ""

// Serial Settings
#define SERIAL_BAUD 115200
#define PRINTER_SERIAL Serial0  // Hardware UART0
#define USB_SERIAL SerialUSB    // USB CDC

// Bluetooth Settings
#define BLE_DEVICE_NAME "ESP32-Camera-Remote"
#define CANON_SERVICE_UUID "00050000-0000-1000-8000-00805f9b34fb"
#define CANON_SHUTTER_CHAR_UUID "00050001-0000-1000-8000-00805f9b34fb"

// Pin Definitions (ESP32-C3)
#define LED_BUILTIN 8
#define STATUS_LED LED_BUILTIN
#define TRIGGER_BUTTON 9  // Optional manual trigger button

// Timing
#define LAYER_STABILIZATION_DELAY 2000  // ms to wait after layer change
#define CAMERA_TRIGGER_DURATION 100     // ms to hold shutter
#define DEBOUNCE_DELAY 50               // ms button debounce

// G-code Parser Buffer
#define GCODE_BUFFER_SIZE 256
#define MAX_LAYER_PATTERNS 10

// Web Server
#define WEB_SERVER_PORT 80

// Storage
#define CONFIG_FILE "/config.json"
#define SPIFFS_ENABLED true

#endif
