#include "GCodeParser.h"
#include "config.h"
#include <HardwareSerial.h>

// Use USB Serial for debug output
#define Serial SerialUSB

GCodeParser::GCodeParser() 
    : lastZHeight(0.0f), layerCount(0), lastLineWasLayerChange(false) {
    
    // Set default configuration
    config.mode = TRIGGER_LAYER_CHANGE;
    config.zHeightIncrement = 0.2f;  // Default layer height
    config.requireStabilization = true;
    config.stabilizationDelay = 2000;
    
    // Load default layer patterns
    loadDefaultPatterns(config.layerPatterns);
}

void GCodeParser::setConfig(const GCodeConfig& cfg) {
    config = cfg;
}

void GCodeParser::addLayerPattern(const String& pattern) {
    config.layerPatterns.push_back(pattern);
}

void GCodeParser::clearLayerPatterns() {
    config.layerPatterns.clear();
}

void GCodeParser::setTriggerMode(TriggerMode mode) {
    config.mode = mode;
}

void GCodeParser::setZHeightIncrement(float increment) {
    config.zHeightIncrement = increment;
}

void GCodeParser::setStabilizationDelay(uint32_t delayMs) {
    config.stabilizationDelay = delayMs;
}

bool GCodeParser::parseLine(const String& line, bool& shouldTrigger) {
    shouldTrigger = false;
    
    // Skip empty lines
    if (line.length() == 0) {
        return true;
    }
    
    // Check for layer change comment
    if (config.mode == TRIGGER_LAYER_CHANGE || config.mode == TRIGGER_BOTH) {
        if (matchesLayerPattern(line)) {
            layerCount++;
            shouldTrigger = true;
            lastLineWasLayerChange = true;
            
            // Serial.printf("[GCode] Layer change detected: %d\n", layerCount);
            return true;
        }
    }
    
    // Check for Z-axis movement
    if (config.mode == TRIGGER_Z_HEIGHT || config.mode == TRIGGER_BOTH) {
        float newZ = 0.0f;
        if (isZMove(line, newZ)) {
            if (shouldTriggerOnZ(newZ)) {
                shouldTrigger = true;
                lastZHeight = newZ;
                
                // Serial.printf("[GCode] Z-height trigger: %.2f mm\n", newZ);
                return true;
            }
            lastZHeight = newZ;
        }
    }
    
    lastLineWasLayerChange = false;
    return true;
}

bool GCodeParser::matchesLayerPattern(const String& line) {
    // Layer change patterns are typically comments
    String trimmed = line;
    trimmed.trim();
    
    // Must be a comment
    if (!trimmed.startsWith(";")) {
        return false;
    }
    
    // Check against all patterns
    for (const String& pattern : config.layerPatterns) {
        if (trimmed.indexOf(pattern) >= 0) {
            return true;
        }
    }
    
    return false;
}

bool GCodeParser::isZMove(const String& line, float& newZ) {
    String trimmed = line;
    trimmed.trim();
    trimmed.toUpperCase();
    
    // Must be a G0 or G1 command (move)
    if (!trimmed.startsWith("G0 ") && !trimmed.startsWith("G1 ")) {
        return false;
    }
    
    // Look for Z parameter
    int zIndex = trimmed.indexOf('Z');
    if (zIndex < 0) {
        return false;
    }
    
    // Parse Z value
    String zString = trimmed.substring(zIndex + 1);
    
    // Find end of number (space or end of string)
    int endIndex = 0;
    for (int i = 0; i < zString.length(); i++) {
        char c = zString.charAt(i);
        if (!isdigit(c) && c != '.' && c != '-') {
            break;
        }
        endIndex = i + 1;
    }
    
    if (endIndex > 0) {
        newZ = zString.substring(0, endIndex).toFloat();
        return true;
    }
    
    return false;
}

bool GCodeParser::shouldTriggerOnZ(float newZ) {
    // Only trigger if Z has increased by at least the increment
    if (newZ > lastZHeight + (config.zHeightIncrement * 0.9f)) {
        return true;
    }
    return false;
}

void GCodeParser::reset() {
    lastZHeight = 0.0f;
    layerCount = 0;
    lastLineWasLayerChange = false;
    lineBuffer = "";
}

void GCodeParser::loadDefaultPatterns(std::vector<String>& patterns) {
    patterns.clear();
    
    // PrusaSlicer / SuperSlicer
    patterns.push_back(";LAYER_CHANGE");
    patterns.push_back(";BEFORE_LAYER_CHANGE");
    patterns.push_back(";AFTER_LAYER_CHANGE");
    
    // Cura
    patterns.push_back(";LAYER:");
    
    // Simplify3D
    patterns.push_back("; layer");
    
    // OrcaSlicer / BambuStudio
    patterns.push_back(";LAYER_CHANGE");
    patterns.push_back("; layer_z");
    
    // Generic patterns
    patterns.push_back(";Layer:");
    patterns.push_back("; Layer ");
    patterns.push_back(";layer ");
    
    // IdeaMaker
    patterns.push_back(";LAYER_END");
    patterns.push_back(";LAYER_START");
}





