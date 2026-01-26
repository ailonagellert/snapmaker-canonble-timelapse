#ifndef GCODE_PARSER_H
#define GCODE_PARSER_H

#include <Arduino.h>
#include <vector>

enum TriggerMode {
    TRIGGER_LAYER_CHANGE,   // Trigger on layer change comments
    TRIGGER_Z_HEIGHT,       // Trigger on Z-axis movement
    TRIGGER_BOTH            // Trigger on either condition
};

struct GCodeConfig {
    TriggerMode mode;
    std::vector<String> layerPatterns;
    float zHeightIncrement;  // mm between photos for Z_HEIGHT mode
    bool requireStabilization;
    uint32_t stabilizationDelay;  // ms
};

class GCodeParser {
private:
    GCodeConfig config;
    float lastZHeight;
    uint32_t layerCount;
    String lineBuffer;
    bool lastLineWasLayerChange;
    
    // Pattern matching
    bool matchesLayerPattern(const String& line);
    bool isZMove(const String& line, float& newZ);
    bool shouldTriggerOnZ(float newZ);
    
public:
    GCodeParser();
    
    // Configuration
    void setConfig(const GCodeConfig& cfg);
    void addLayerPattern(const String& pattern);
    void clearLayerPatterns();
    void setTriggerMode(TriggerMode mode);
    void setZHeightIncrement(float increment);
    void setStabilizationDelay(uint32_t delayMs);
    
    // Parsing
    bool parseLine(const String& line, bool& shouldTrigger);
    void reset();
    
    // Statistics
    uint32_t getLayerCount() const { return layerCount; }
    float getLastZHeight() const { return lastZHeight; }
    
    // Default patterns for common slicers
    static void loadDefaultPatterns(std::vector<String>& patterns);
};

#endif
