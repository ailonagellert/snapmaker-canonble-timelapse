#include "SerialBridge.h"
#include "config.h"
#include <HardwareSerial.h>

// Use USB Serial for debug output
#define Serial SerialUSB

SerialBridge::SerialBridge() 
    : printerSerial(nullptr), hostSerial(nullptr), parser(nullptr), 
      onTrigger(nullptr), bytesForwarded(0), linesProcessed(0), 
      passthroughEnabled(true), triggerCount(0), lastTriggerTime(0) {
    startTime = millis();
}

SerialBridge::~SerialBridge() {
}

bool SerialBridge::begin(HardwareSerial* printer, Stream* host, GCodeParser* gcodeParser) {
    printerSerial = printer;
    hostSerial = host;
    parser = gcodeParser;
    
    if (!printerSerial || !hostSerial || !parser) {
        // Serial.println("[Bridge] ERROR: Invalid configuration");
        return false;
    }
    
    // Serial.println("[Bridge] Serial bridge initialized");
    // Serial.println("[Bridge] Printer <-> ESP32 <-> Host");
    
    return true;
}

void SerialBridge::setTriggerCallback(TriggerCallback callback) {
    onTrigger = callback;
}

void SerialBridge::enablePassthrough(bool enable) {
    passthroughEnabled = enable;
    // Serial.printf("[Bridge] Passthrough %s\n", enable ? "enabled" : "disabled");
}

void SerialBridge::process() {
    // Forward from host to printer
    if (hostSerial->available()) {
        while (hostSerial->available()) {
            char c = hostSerial->read();
            
            if (passthroughEnabled && printerSerial) {
                printerSerial->write(c);
                bytesForwarded++;
            }
        }
    }
    
    // Forward from printer to host and parse G-code
    if (printerSerial && printerSerial->available()) {
        while (printerSerial->available()) {
            char c = printerSerial->read();
            
            // Forward to host
            if (passthroughEnabled && hostSerial) {
                hostSerial->write(c);
                bytesForwarded++;
            }
            
            // Buffer for line-based parsing
            if (c == '\n' || c == '\r') {
                if (lineBuffer.length() > 0) {
                    processLine(lineBuffer);
                    lineBuffer = "";
                }
            } else {
                lineBuffer += c;
                
                // Prevent buffer overflow
                if (lineBuffer.length() > 256) {
                    lineBuffer = "";
                }
            }
        }
    }
}

void SerialBridge::processLine(const String& line) {
    linesProcessed++;
    
    // Parse G-code for trigger events
    bool shouldTrigger = false;
    if (parser) {
        parser->parseLine(line, shouldTrigger);
        
        if (shouldTrigger) {
            // Serial.printf("[Bridge] Trigger event! Layer: %d\n", parser->getLayerCount());
            triggerCount++;
            lastTriggerTime = millis();
            
            // Call trigger callback
            if (onTrigger) {
                onTrigger();
            }
        }
    }
}

void SerialBridge::forwardToHost(const String& data) {
    if (hostSerial) {
        hostSerial->print(data);
    }
}

void SerialBridge::forwardToPrinter(const String& data) {
    if (printerSerial) {
        printerSerial->print(data);
    }
}

void SerialBridge::manualTrigger() {
    // Serial.println("[Bridge] Manual trigger activated");
    triggerCount++;
    lastTriggerTime = millis();
    
    if (onTrigger) {
        onTrigger();
    }
}





