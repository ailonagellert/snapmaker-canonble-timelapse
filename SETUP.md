# ESP32-C3 Camera Controller Setup Guide

Complete guide for building and deploying the camera controller for 3D printer timelapse photography.

## Table of Contents

1. [Hardware Requirements](#hardware-requirements)
2. [Software Requirements](#software-requirements)
3. [Building the Firmware](#building-the-firmware)
4. [Flashing to ESP32](#flashing-to-esp32)
5. [Hardware Setup](#hardware-setup)
6. [Initial Configuration](#initial-configuration)
7. [Camera Pairing](#camera-pairing)
8. [Usage](#usage)
9. [Troubleshooting](#troubleshooting)

## Hardware Requirements

### Required Components

- **ESP32-C3 DevKit** (or compatible board with USB)
  - Recommended: ESP32-C3-DevKitM-1 or similar
  - Must support USB CDC (USB serial)
- **Canon EOS Camera with Bluetooth**
  - Tested: Canon EOS RP
  - Should work with: EOS R, R5, R6, R7, R10, M50 Mark II
- **USB Cables**
  - USB-C cable for ESP32-C3
  - Standard USB cable for your printer
- **Optional: Button** for manual trigger (connected to GPIO 9)
- **Optional: LED** for status indication (uses built-in LED on pin 8)

### Supported Printers

- Snapmaker U1 (Klipper)
- Creality CR10-SE (Klipper/Clipper)
- Any 3D printer running Klipper with USB serial output

## Software Requirements

### Development Environment

1. **PlatformIO** - Install via:
   ```bash
   pip install platformio
   ```

2. **Or use PlatformIO IDE** (VS Code extension)
   - Install VS Code
   - Install "PlatformIO IDE" extension

### Required Libraries (auto-installed by PlatformIO)

- ArduinoJson
- ESP32 BLE Arduino
- ESPAsyncWebServer
- AsyncTCP

## Building the Firmware

### Option 1: Command Line

```bash
# Navigate to project directory
cd cameracontroller

# Build the firmware
pio run

# Expected output: SUCCESS
# Firmware will be in .pio/build/esp32c3/firmware.bin
```

### Option 2: VS Code with PlatformIO

1. Open the `cameracontroller` folder in VS Code
2. Click the PlatformIO icon in the sidebar
3. Click "Build" under "esp32c3" environment
4. Wait for compilation to complete

## Flashing to ESP32

### First Time Flash (USB)

1. **Connect ESP32-C3 to computer** via USB-C cable

2. **Put ESP32 in bootloader mode** (if needed):
   - Hold BOOT button
   - Press RESET button
   - Release RESET, then BOOT

3. **Flash firmware**:
   ```bash
   pio run --target upload
   ```

4. **Monitor serial output**:
   ```bash
   pio device monitor
   ```

### Verify Flash Success

You should see output like:
```
========================================
  ESP32-C3 Camera Controller
  Version: 1.0.0
========================================

[Main] Serial bridge initialized
[Main] Initializing Bluetooth...
[WiFi] Starting AP: CameraController-Setup
[WiFi] AP IP: 192.168.4.1
[Main] Setup complete!
```

## Hardware Setup

### Connection Diagram

```
┌─────────────┐          ┌──────────────┐          ┌─────────────┐
│             │          │              │          │             │
│  3D Printer │◄────USB──┤   ESP32-C3   ├────USB───► Computer   │
│   (Klipper) │          │              │          │ (OctoPrint) │
│             │          │              │          │             │
└─────────────┘          └──────┬───────┘          └─────────────┘
                                │
                            Bluetooth
                                │
                         ┌──────▼───────┐
                         │              │
                         │  Canon EOS   │
                         │    Camera    │
                         │              │
                         └──────────────┘
```

### Physical Setup

1. **Disconnect your printer's USB cable** from computer
2. **Connect printer USB to ESP32-C3** (ESP32 acts as USB device)
3. **Connect ESP32-C3 to computer** via separate USB port (ESP32 acts as USB host)
4. **Power on the Canon camera** and ensure Bluetooth is enabled

**Note:** The ESP32-C3 transparently passes all data between printer and computer while monitoring G-code.

## Initial Configuration

### 1. Connect to WiFi Setup

1. **Look for WiFi network: `CameraController`**
2. **Password: `camera123`**
3. Connect your phone or computer to this network
4. **Access the web interface** in two ways:
   - **Via hostname** (recommended): Open browser to **`http://cameracontroller.local`** 
   - **Via IP address**: Open browser to **`http://192.168.4.1`**

### 2. Web Interface

The web interface provides:
- **Real-time status** of camera connection, layer count, photos taken
- **Manual trigger button** to test camera
- **Camera scan** to find and connect Canon camera
- **Statistics** about G-code processing
- **Configuration** options

### 3. Connect to Your Network (Optional)

To control the device from your network:

1. Edit `data/config.json` before flashing:
```json
{
  "wifi": {
    "mode": "sta",
    "sta_ssid": "YourNetworkName",
    "sta_password": "YourPassword"
  }
}
```

2. Or use the web interface to switch from AP mode to station mode

### Troubleshooting WiFi AP Not Visible

If you can't see the WiFi network after flashing:

1. **Check serial monitor output** - Look for these messages:
   ```
   [Setup] Starting WiFi AP mode...
   [Setup] softAP result: SUCCESS
   [Setup] AP IP: 192.168.4.1
   [Setup] mDNS started - access at http://cameracontroller.local
   ```

2. **If you see "FAILED"**:
   - Check that the build succeeded (no compilation errors)
   - Verify the board is actually running (LED should blink 5 times on boot)
   - Try resetting the board

3. **If WiFi is still not visible**:
   - Move closer to the ESP32
   - Restart the ESP32 (press RESET button)
   - Try scanning for networks again on your device
   - Check if another device can see it (multiple device test)

## Camera Pairing

### Canon EOS Camera Setup

1. **Enable Bluetooth on camera**:
   - Menu → Wireless Communication Settings
   - Bluetooth Function → Enable
   - Remote Control → Enable

2. **Set camera to pairing mode**:
   - Keep camera on and Bluetooth enabled
   - Camera will advertise as "Canon EOS RP" (or similar)

3. **Scan from ESP32**:
   - In web interface, click "Scan for Camera"
   - Or wait for automatic scan on startup
   - LED will blink when camera connects

4. **Verify connection**:
   - Web interface should show "Camera: Connected"
   - Serial monitor shows: `[BLE] Camera ready for remote control`

### Troubleshooting Camera Pairing

- **Camera not found**: Ensure Bluetooth is ON and camera is in pairing mode
- **Connection fails**: Power cycle the camera
- **Intermittent connection**: Move ESP32 closer to camera (BLE range ~10m)
- **Wrong camera detected**: The code looks for "Canon" or "EOS" in device name

## Usage

### Starting a Print

1. **Ensure camera is connected** (check web interface or LED indicator)
2. **Start your print** normally through OctoPrint/Fluidd/Mainsail
3. **ESP32 automatically detects layer changes** and triggers camera
4. **Monitor progress** via web interface or serial output

### Manual Trigger

- **Button**: Press the button connected to GPIO 9
- **Web**: Click "Take Picture" button in web interface
- **Serial**: Send command via serial terminal (future feature)

### Statistics

Check web interface for:
- Total photos taken
- Current layer number
- Lines of G-code processed
- System uptime
- Current Z-height

## Configuration Options

### G-code Trigger Patterns

Edit patterns in [data/config.json](data/config.json):

```json
{
  "gcode": {
    "trigger_mode": "layer_change",
    "layer_patterns": [
      ";LAYER_CHANGE",    // PrusaSlicer
      ";LAYER:",          // Cura
      "; layer"           // Simplify3D
    ]
  }
}
```

**Supported trigger modes:**
- `layer_change` - Trigger on layer comment detection (recommended)
- `z_height` - Trigger every X mm of Z movement
- `both` - Trigger on either condition

### Stabilization Delay

Add delay after layer change before taking photo:

```json
{
  "camera": {
    "stabilization_delay_ms": 2000
  }
}
```

This allows the printer to stabilize after movement.

### Camera Settings

```json
{
  "camera": {
    "auto_connect": true,
    "focus_before_shot": false,
    "focus_delay_ms": 500
  }
}
```

## Troubleshooting

### ESP32 Issues

**Problem**: ESP32 won't flash
- **Solution**: Hold BOOT button, press RESET, try flash again

**Problem**: Serial monitor shows garbage
- **Solution**: Check baud rate is set to 115200

**Problem**: WiFi AP not appearing
- **Solution**: Check antenna is connected (if external)

### Camera Issues

**Problem**: Camera not connecting
- **Solution 1**: Enable Bluetooth on camera menu
- **Solution 2**: Power cycle camera
- **Solution 3**: Check if camera is already paired to another device
- **Solution 4**: Update to latest Canon firmware

**Problem**: Camera connects but no photos taken
- **Solution 1**: Check if camera is in correct mode (not video mode)
- **Solution 2**: Check battery level
- **Solution 3**: Verify memory card has space
- **Solution 4**: Check if camera sleep mode is disabled

**Problem**: Photos not triggering on layer change
- **Solution 1**: Check G-code for layer comments (print a test file and monitor serial)
- **Solution 2**: Add your slicer's pattern to config.json
- **Solution 3**: Switch to `z_height` trigger mode

### Printer Communication Issues

**Problem**: Printer not communicating with computer
- **Solution 1**: Check USB cables are properly connected
- **Solution 2**: Verify serial passthrough is enabled (default: ON)
- **Solution 3**: Try different USB ports
- **Solution 4**: Check baud rate matches printer (usually 115200)

**Problem**: G-code not being parsed
- **Solution**: Monitor serial output to see G-code lines, verify format

### Performance Issues

**Problem**: Missed layer changes
- **Solution**: Increase `stabilization_delay_ms` to give more time

**Problem**: Too many photos
- **Solution**: Switch to Z-height trigger with larger increment

## Advanced Configuration

### Custom Layer Patterns

If using a custom slicer or profile, add your pattern:

```json
{
  "gcode": {
    "layer_patterns": [
      ";MY_CUSTOM_LAYER_MARKER",
      "; Custom Layer:"
    ]
  }
}
```

### Serial Debugging

To see detailed G-code parsing:

1. Connect via serial monitor: `pio device monitor`
2. Watch for `[GCode]` log entries
3. Verify layer patterns are matching

### Bluetooth UUIDs

If using a different Canon camera model, you may need to update BLE UUIDs in [include/CanonBLE.h](include/CanonBLE.h).

Research your camera's BLE characteristics using:
- nRF Connect app (Android/iOS)
- LightBlue app (iOS)
- Linux `bluetoothctl` command

## Slicer Configuration

### PrusaSlicer / SuperSlicer

No configuration needed - uses `;LAYER_CHANGE` by default.

### Cura

No configuration needed - uses `;LAYER:` by default.

### Simplify3D

Uses `; layer X` format - already supported.

### Custom Script

Add to your slicer's "Layer Change G-code":

```gcode
;CAMERA_TRIGGER
```

Then add to config.json:
```json
"layer_patterns": [";CAMERA_TRIGGER"]
```

## Support

For issues or questions:

1. Check the troubleshooting section above
2. Review serial monitor output for error messages
3. Check web interface status page
4. Verify Canon camera Bluetooth compatibility
5. Open an issue on GitHub (if applicable)

## Safety Notes

- **Do not modify printer firmware** - this device works externally
- **Monitor first print** to ensure correct triggering
- **Check camera battery** before long prints
- **Ensure memory card space** for all photos
- **Keep ESP32 and camera within BLE range** (~10 meters)

## Next Steps

- Set up post-processing scripts to compile timelapse video
- Integrate with OctoPrint/Mainsail/Fluidd for seamless workflow
- Experiment with camera settings (ISO, exposure)
- Try different angles and lighting setups

---

**Enjoy your automated 3D print timelapses! 📷🎥**
