# ESP32 Camera Controller for 3D Printer Timelapse

ESP32-C3 Bluetooth remote control for Canon EOS cameras. Connects via USB to your Klipper host - Python script monitors G-code and sends trigger commands to ESP32 over serial, which then triggers the camera via Bluetooth.

## Features

- � **Bluetooth Camera Control** - Wireless Canon EOS camera trigger via BLE
- 🐍 **Python G-code Monitoring** - Watches Moonraker/Klipper G-code stream for layer changes
- 🌐 **Web Interface** - Manual trigger and status via WiFi
- 🔄 **Universal** - Works with any Klipper printer (Snapmaker U1, Creality CR10-SE, etc.)
- 🎯 **Multi-Slicer Support** - Recognizes layer markers from all major slicers
- 📊 **Simple & Reliable** - Dedicated BLE remote, no USB complications

## Hardware Requirements

- **ESP32-C3 DevKit** - Acts as Bluetooth remote
- **Canon EOS camera** with Bluetooth (tested: EOS RP, R5, R6)
- **Klipper/Moonraker host** - Raspberry Pi or similar running printer software
- **USB cable** - Connect ESP32 to Klipper host (creates /dev/ttyACM0)

## Supported Slicers

- PrusaSlicer / SuperSlicer
- Cura
- Simplify3D
- OrcaSlicer
- BambuStudio

## Quick Start

### 1. Flash ESP32 Firmware & Connect to Klipper Host
```bash
git clone https://github.com/yourusername/cameracontroller.git
cd cameracontroller
pio run --target upload
```
Then connect ESP32 via USB to your Klipper host (Raspberry Pi). It should appear as `/dev/ttyACM0`.

### 2. Pair Canon Camera via Bluetooth
1. Turn on your Canon camera (e.g., EOS RP)
2. Go to **Menu → Bluetooth Settings → Bluetooth Function → ON**
3. Go to **Menu → Bluetooth Settings → Pairing → New Device**
4. Select **"ESP32-Camera-Remote"** from the list
5. Confirm pairing on camera
6. Device should show ✓ Connected

### 3. Install Python Monitor on Klipper Host
```bash
# SSH into your printer (Raspberry Pi running Klipper)
ssh pi@printer_ip

# Download and run install script
curl -O https://raw.githubusercontent.com/yourusername/cameracontroller/main/install_timelapse_monitor.sh
chmod +x install_timelapse_monitor.sh
sudo ./install_timelapse_monitor.sh

# Start the service
sudo systemctl start timelapse_monitor
```

### 4. Add Layer Change Command to Slicer
- **PrusaSlicer/Cura/OrcaSlicer**: Add to Layer Change G-code:
  ```gcode
  ;LAYER_CHANGE
  ```
- See [GCODE_CONFIG.md](docs/GCODE_CONFIG.md) for slicer-specific instructions

### 5. Start Your Print!
- Python script monitors G-code and triggers ESP32
- ESP32 triggers camera via Bluetooth
- LED blinks to confirm each photo captured

## Architecture

```
3D Printer → Klipper/Moonraker (on Raspberry Pi)
                      ↓ monitors G-code via WebSocket
                Python Script
                      ↓ writes "trigger" to /dev/ttyACM0
                   ESP32-C3 (connected via USB)
                      ↓ sends BLE command
                  Canon Camera
```

The Python script monitors Moonraker's G-code stream for layer changes, then sends "trigger" command over USB serial to the ESP32. The ESP32 acts as a Bluetooth remote for your Canon camera.

## Configuration

### ESP32 (Optional)
Access web interface at **http://192.168.4.1**:
- Test manual camera trigger
- Check connection status
- Adjust stabilization delay if needed

### Python Script
Edit `/opt/timelapse_monitor/timelapse_monitor.py`:
- Set Moonraker WebSocket URL
- Configure layer detection patterns (supports all major slicers)
- Adjust trigger timing

See [INSTALLATION.md](INSTALLATION.md) for detailed configuration options.
```

## Documentation

- **[📦 Installation Guide](INSTALLATION.md)** - Complete step-by-step setup
- **[📷 Camera Pairing](docs/CAMERA_PAIRING.md)** - Pair your Canon camera via Bluetooth
- **[⚙️ G-code Configuration](docs/GCODE_CONFIG.md)** - Configure your 3D printer slicer
- **[🔧 Development Guide](docs/DEVELOPMENT.md)** - For developers and contributors
- **[🔌 Hardware Wiring](WIRING.md)** - Physical connections and pinout
- **[📋 Setup Details](SETUP.md)** - Detailed firmware building and flashing

## Quick Troubleshooting

| Problem | Solution |
|---------|----------|
| **WiFi AP not visible** | Check serial monitor for boot errors |
| **Camera won't pair** | See [Camera Pairing Guide](docs/CAMERA_PAIRING.md) |
| **Photos not triggering** | Verify `;LAYER_CHANGE` in G-code file |
| **USB serial not working** | Rebuild firmware with `pio run --target upload` |

See [INSTALLATION.md](INSTALLATION.md) for complete troubleshooting guide.

## Support

- 📖 Check the documentation links above
- 🐛 [Report issues](../../issues) on GitHub
- 💬 Discussions in project repository

## License

MIT License - See [LICENSE](LICENSE) file for details
