# ESP32 Camera Controller for 3D Printer Timelapse

Plug-and-play ESP32-C3 device that monitors G-code from your 3D printer and triggers a Canon EOS camera via Bluetooth for automatic timelapse photography.

## Features

- 🔌 **Plug & Play** - Insert between printer and USB, no printer modifications needed
- 📷 **Bluetooth Camera Control** - Wireless shutter trigger for Canon EOS cameras
- 🎯 **Layer Detection** - Smart G-code parsing for multiple slicer formats
- 🌐 **Web Configuration** - WiFi-based setup and manual controls
- 🔄 **Universal** - Works with any Klipper printer (Snapmaker U1, Creality CR10-SE, etc.)
- 📊 **Status Display** - Real-time photo count and status feedback

## Hardware Requirements

- ESP32-C3 DevKit (with USB host capability)
- Canon EOS camera with Bluetooth (tested: EOS RP)
- USB cable (printer to ESP32)
- Optional: USB OTG adapter if needed

## Supported Slicers

- PrusaSlicer / SuperSlicer
- Cura
- Simplify3D
- OrcaSlicer
- BambuStudio

## Quick Start

1. Flash firmware to ESP32-C3
2. Connect ESP32 between printer and USB host
3. Connect to WiFi network "CameraController-Setup"
4. Configure via web interface at http://192.168.4.1
5. Pair Canon camera in Bluetooth settings
6. Start printing!

## Architecture

```
3D Printer → USB → ESP32-C3 → Bluetooth → Canon Camera
                  (G-code Monitor)
```

The ESP32 acts as a transparent USB serial passthrough while monitoring for layer change commands in the G-code stream.

## Configuration

Edit `config.json` via web interface or SD card:

```json
{
  "wifi": {
    "ssid": "YourNetwork",
    "password": "YourPassword"
  },
  "camera": {
    "delay_ms": 2000,
    "stabilization_delay": 500
  },
  "gcode": {
    "layer_patterns": [
      ";LAYER_CHANGE",
      ";LAYER:",
      "; layer",
      ";Layer:"
    ],
    "trigger_mode": "layer_change"
  }
}
```

## Building

```bash
# Install PlatformIO
pip install platformio

# Clone and build
git clone <repo>
cd cameracontroller
pio run

# Upload to ESP32-C3
pio run --target upload

# Monitor serial output
pio device monitor
```

## License

MIT
