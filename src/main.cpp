#include <Arduino.h>
#include <WiFi.h>
#include <HardwareSerial.h>
#include <ESPmDNS.h>
#include "config.h"
#include "CanonBLERemote.h"
#include "GCodeParser.h"
#include "SerialBridge.h"
#include "WebConfig.h"

CanonBLERemote camera("ESP32-Camera-Remote");
GCodeParser gcodeParser;
SerialBridge serialBridge;
WebConfig webConfig;

// State
unsigned long lastStatusPrint = 0;

// Trigger callback for camera
void onLayerChange() {
    if (!camera.isConnected()) {
        // Serial.println("[Main] Camera not ready, skipping photo");
        return;
    }
    
    // Optional: Add stabilization delay
    delay(LAYER_STABILIZATION_DELAY);
    
    // Take picture
    // Serial.println("[Main] Taking timelapse photo...");
    bool success = camera.trigger();
    
    if (success) {
        // Serial.println("[Main] ✓ Photo captured");
        // Blink LED
        digitalWrite(STATUS_LED, HIGH);
        delay(100);
        digitalWrite(STATUS_LED, LOW);
    } else {
        // Serial.println("[Main] ✗ Photo failed");
    }
}

void setup() {
    // Setup LED first thing
    pinMode(STATUS_LED, OUTPUT);
    digitalWrite(STATUS_LED, LOW);
    delay(100);
    
    // Initialize USB Serial
    Serial.begin(115200);
    delay(1000);  // Wait for USB serial to initialize
    
    Serial.println("\n\n=== ESP32-C3 Camera Controller ===");
    Serial.print("MAC Address: ");
    Serial.println(WiFi.macAddress());
    
    // Immediate single blink to confirm boot
    digitalWrite(STATUS_LED, HIGH);
    delay(200);
    digitalWrite(STATUS_LED, LOW);
    delay(200);
    
    // Blink LED to indicate boot
    for (int i = 0; i < 3; i++) {
        digitalWrite(STATUS_LED, HIGH);
        delay(100);
        digitalWrite(STATUS_LED, LOW);
        delay(100);
    }
    
    // Initialize G-code parser with default settings
    gcodeParser.setTriggerMode(TRIGGER_LAYER_CHANGE);
    gcodeParser.setStabilizationDelay(LAYER_STABILIZATION_DELAY);
    
    // Initialize serial bridge
    Serial1.begin(SERIAL_BAUD, SERIAL_8N1, 20, 21);  // Printer: RX=GPIO20, TX=GPIO21
    serialBridge.begin(&Serial1, &Serial, &gcodeParser);
    serialBridge.setTriggerCallback(onLayerChange);
    
    // Start WiFi AP FIRST (before BLE)
    Serial.println("\n[Setup] Starting WiFi AP mode...");
    
    WiFi.mode(WIFI_AP);
    delay(100);
    
    Serial.printf("[Setup] WiFi mode: %d (2=AP)\n", WiFi.getMode());
    Serial.printf("[Setup] Starting AP with SSID: '%s'\n", AP_SSID);
    
    // Configure AP with better settings
    WiFi.softAPConfig(IPAddress(192,168,4,1), IPAddress(192,168,4,1), IPAddress(255,255,255,0));
    bool apStarted = WiFi.softAP(AP_SSID, AP_PASSWORD, 1, false, 4);  // Channel 1, max 4 clients
    Serial.printf("[Setup] softAP result: %s\n", apStarted ? "SUCCESS" : "FAILED");
    
    delay(1000);  // Wait for AP to stabilize
    
    IPAddress apIP = WiFi.softAPIP();
    Serial.printf("[Setup] AP IP: %s\n", apIP.toString().c_str());
    Serial.printf("[Setup] AP MAC: %s\n", WiFi.softAPmacAddress().c_str());
    
    // Start mDNS for hostname resolution
    if (MDNS.begin("cameracontroller")) {
        MDNS.addService("http", "tcp", 80);
        Serial.println("[Setup] mDNS started - access at http://cameracontroller.local");
    } else {
        Serial.println("[Setup] WARNING: mDNS failed to start");
    }
    
    // Now start web server
    webConfig.begin(&camera, &gcodeParser, &serialBridge);
    
    Serial.println("=================================");
    Serial.println("WiFi AP is running!");
    Serial.printf("Connect to: %s\n", AP_SSID);
    Serial.printf("Password: %s\n", AP_PASSWORD);
    Serial.printf("Then browse to: http://%s\n", apIP.toString().c_str());
    Serial.println("=================================\n");
    
    // NOW initialize BLE after WiFi is stable
    Serial.println("Initializing Canon BLE (coexistence mode)...");
    delay(500);  // Give WiFi time to establish before starting BLE
    camera.init();
    Serial.println("Canon BLE initialized");
    Serial.println("=================================\n");
    
    // LED feedback - 5 quick blinks for AP started
    for (int i = 0; i < 5; i++) {
        digitalWrite(STATUS_LED, HIGH);
        delay(100);
        digitalWrite(STATUS_LED, LOW);
        delay(100);
    }
    
    // Final ready indication
    for (int i = 0; i < 3; i++) {
        digitalWrite(STATUS_LED, HIGH);
        delay(200);
        digitalWrite(STATUS_LED, LOW);
        delay(200);
    }
    digitalWrite(STATUS_LED, HIGH);  // Keep LED on
}

void loop() {
    // Heartbeat LED - blink every 2 seconds to show device is alive
    static unsigned long lastBlink = 0;
    if (millis() - lastBlink > 2000) {
        lastBlink = millis();
        digitalWrite(STATUS_LED, HIGH);
        delay(50);
        digitalWrite(STATUS_LED, LOW);
    }
    
    // Process serial bridge (most important task)
    serialBridge.process();
    
    // Check manual trigger button
    static bool lastButtonState = HIGH;
    bool buttonState = digitalRead(TRIGGER_BUTTON);
    
    if (buttonState == LOW && lastButtonState == HIGH) {
        delay(DEBOUNCE_DELAY);
        if (digitalRead(TRIGGER_BUTTON) == LOW) {
            // Serial.println("[Main] Manual trigger button pressed");
            serialBridge.manualTrigger();
            onLayerChange();
        }
    }
    lastButtonState = buttonState;
    
    // Periodic status output
    if (millis() - lastStatusPrint > 10000) {
        lastStatusPrint = millis();
        
        // Serial.println("\n--- Status ---");
        // Serial.printf("Camera: %s\n", camera.isConnected() ? "Connected" : "Disconnected");
        // Serial.printf("Layers: %d\n", gcodeParser.getLayerCount());
        // Serial.printf("Photos: %d\n", serialBridge.getTriggerCount());
        // Serial.printf("Lines processed: %d\n", serialBridge.getLinesProcessed());
        // Serial.printf("Z-height: %.2f mm\n", gcodeParser.getLastZHeight());
        // Serial.printf("WiFi: %s\n", webConfig.getIPAddress().c_str());
        // Serial.println("--------------\n");
    }
    
    // Small delay to prevent watchdog issues
    delay(1);
}





