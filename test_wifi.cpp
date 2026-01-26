#include <Arduino.h>
#include <WiFi.h>

#define LED_BUILTIN 8

void setup() {
    // Setup LED
    pinMode(LED_BUILTIN, OUTPUT);
    
    // Blink LED to show we're running
    for (int i = 0; i < 10; i++) {
        digitalWrite(LED_BUILTIN, HIGH);
        delay(100);
        digitalWrite(LED_BUILTIN, LOW);
        delay(100);
    }
    
    // Disable WiFi power save
    WiFi.setSleep(false);
    
    // Start WiFi AP
    WiFi.mode(WIFI_AP);
    delay(500);
    
    bool result = WiFi.softAP("TestAP123", "password123", 1, false, 4);
    
    // Blink LED differently based on result
    if (result) {
        // SUCCESS - steady blink
        while(1) {
            digitalWrite(LED_BUILTIN, HIGH);
            delay(1000);
            digitalWrite(LED_BUILTIN, LOW);
            delay(1000);
        }
    } else {
        // FAILED - fast blink
        while(1) {
            digitalWrite(LED_BUILTIN, HIGH);
            delay(100);
            digitalWrite(LED_BUILTIN, LOW);
            delay(100);
        }
    }
}

void loop() {
    // Should never reach here
}
