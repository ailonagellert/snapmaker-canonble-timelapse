#ifndef SERIAL_BRIDGE_H
#define SERIAL_BRIDGE_H

#include <Arduino.h>
#include "GCodeParser.h"

// Callback function type for when a trigger event occurs
typedef void (*TriggerCallback)(void);

class SerialBridge {
private:
    HardwareSerial* printerSerial;  // Serial to printer
    Stream* hostSerial;             // USB CDC to host computer
    
    GCodeParser* parser;
    TriggerCallback onTrigger;
    
    String lineBuffer;
    uint32_t bytesForwarded;
    uint32_t linesProcessed;
    bool passthroughEnabled;
    
    // Statistics
    uint32_t triggerCount;
    unsigned long lastTriggerTime;
    unsigned long startTime;
    
public:
    SerialBridge();
    ~SerialBridge();
    
    // Initialize serial bridge
    bool begin(HardwareSerial* printer, Stream* host, GCodeParser* gcodeParser);
    
    // Set trigger callback
    void setTriggerCallback(TriggerCallback callback);
    
    // Enable/disable passthrough
    void enablePassthrough(bool enable);
    bool isPassthroughEnabled() const { return passthroughEnabled; }
    
    // Main processing loop - call frequently
    void process();
    
    // Statistics
    uint32_t getBytesForwarded() const { return bytesForwarded; }
    uint32_t getLinesProcessed() const { return linesProcessed; }
    uint32_t getTriggerCount() const { return triggerCount; }
    unsigned long getLastTriggerTime() const { return lastTriggerTime; }
    unsigned long getUptime() const { return millis() - startTime; }
    
    // Manual trigger
    void manualTrigger();
    
private:
    void processLine(const String& line);
    void forwardToHost(const String& data);
    void forwardToPrinter(const String& data);
};

#endif
