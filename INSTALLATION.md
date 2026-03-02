# Installation Guide (Recommended Workflow)

This is the canonical setup path for this project:

1. Clone on your workstation
2. Flash ESP32 firmware from workstation
3. Plug ESP32 into your Klipper/Moonraker host
4. SSH into host and install/run monitor scripts
5. Pair camera and print

## Table of Contents

1. [Prerequisites](#prerequisites)
2. [Clone on Workstation](#clone-on-workstation)
3. [Flash Firmware on Workstation](#flash-firmware-on-workstation)
4. [Move ESP32 to Printer Host](#move-esp32-to-printer-host)
5. [Install Monitor via SSH](#install-monitor-via-ssh)
6. [Initial Configuration (Optional)](#initial-configuration-optional)
7. [Pair Canon Camera](#pair-canon-camera)
8. [Configure Your Slicer](#configure-your-slicer)
9. [First Print Verification](#first-print-verification)
10. [Troubleshooting](#troubleshooting)

---

## Prerequisites

- ESP32-C3 dev board
   - Example board: https://amzn.to/4l1zeoW
- Canon EOS camera with Bluetooth
- Klipper + Moonraker host (Snapmaker controller/Raspberry Pi/etc.)
- Root SSH access (or equivalent admin access) to that host
- One USB data cable (ESP32-C3 → host)
- Workstation with PlatformIO for initial flash

### Snapmaker U1 Requirement

If you are running this on Snapmaker U1, you typically need custom firmware that enables root SSH and script installation.

Recommended project:
- https://github.com/paxx12/SnapmakerU1-Extended-Firmware

Wiring model is USB-only and documented in [WIRING.md](WIRING.md).

---

## Clone on Workstation

### Option 1: Git Clone (Recommended)

```bash
# Clone the repository
git clone https://github.com/yourusername/snapmaker-canonble-timelapse.git
cd snapmaker-canonble-timelapse
```

### Option 2: Download ZIP

1. Go to GitHub repository page
2. Click **Code → Download ZIP**
3. Extract to a local folder
4. Open terminal in that folder

---

## Flash Firmware on Workstation

### Install PlatformIO

**Option A: VS Code Extension (Easiest)**

1. Open VS Code
2. Go to **Extensions** (Ctrl+Shift+X)
3. Search for "PlatformIO IDE"
4. Click **Install**
5. Reload VS Code
6. PlatformIO icon appears in sidebar

**Option B: Command Line**

```bash
pip install platformio
```

### Build & Upload Firmware

**Using VS Code PlatformIO:**

1. Open the `snapmaker-canonble-timelapse` folder in VS Code
2. Click **PlatformIO** icon (ant logo) in sidebar
3. Expand **esp32c3** environment
4. Click **Build** (wait for "SUCCESS")
5. Click **Upload** (esp32 will restart)
6. Click **Serial Monitor** to verify startup

**Using Command Line:**

```bash
# Build the firmware
pio run -e esp32c3

# Upload to connected ESP32
pio run -t upload -e esp32c3

# Monitor serial output (Ctrl+C to exit)
pio device monitor -b 115200
```

### Verify Upload

You should see in the serial monitor:
```
=== ESP32-C3 Camera Controller ===
MAC Address: XX:XX:XX:XX:XX:XX
[Setup] Starting WiFi AP mode...
WiFi AP is running!
Connect to: CameraController-Setup
Password: camera123
Then browse to: http://192.168.4.1
```

---

## Move ESP32 to Printer Host

1. Unplug ESP32-C3 from workstation
2. Plug ESP32-C3 into the USB port on your Klipper/Moonraker host
3. On host, verify serial device exists (`/dev/ttyACM0` or `/dev/ttyACM*`)

---

## Install Monitor via SSH

SSH into your printer host and run:

> Requires root SSH (or a user with equivalent sudo/admin permissions).

```bash
# SSH into your printer host
ssh root@printer_ip

# Download and run install script
cd /tmp
curl -O https://raw.githubusercontent.com/yourusername/snapmaker-canonble-timelapse/main/install_timelapse_monitor.sh
chmod +x install_timelapse_monitor.sh
./install_timelapse_monitor.sh

# Start and verify
sudo systemctl start timelapse_monitor
sudo systemctl status timelapse_monitor
```

This installs dependencies, configures a service, and starts Moonraker event monitoring.

---

## Initial Configuration (Optional)

### Access Web Interface

1. **Find your device's WiFi AP:**
   - Look for WiFi network named: **CameraController-Setup**
   - Password: **camera123**

2. **Connect to the AP**
   - On your phone or computer, select this network
   - Enter password: camera123

3. **Open web interface:**
   - Open browser and go to: **http://192.168.4.1**
   - You should see the ESP32 Camera Controller interface

### Configure WiFi (Optional - for remote access)

1. In web interface, click **WiFi Settings**
2. Select your home WiFi network
3. Enter WiFi password
4. Click **Save**
5. Device will restart and connect to your network

*Note: Once connected to your home WiFi, you can still use the setup AP if needed by factory resetting.*

### Configure Camera Settings

1. In web interface, click **Camera Settings**
2. Adjust if needed:
   - **Stabilization Delay**: 2000-3000ms (time to wait after layer change before taking photo)
   - **Focus Before Shot**: OFF (unless your camera supports AF trigger)
   - **Auto Connect**: ON (auto-pair camera on startup)
3. Click **Save**

---

## Pair Canon Camera

Follow the detailed guide: **[CAMERA_PAIRING.md](docs/CAMERA_PAIRING.md)**

**Quick Summary:**

1. Ensure Canon camera is powered on
2. Go to Camera **Menu → Bluetooth Settings → Bluetooth Function → ON**
3. Go to **Menu → Bluetooth Settings → Pairing → New Device**
4. Select **"ESP32-Camera-Remote"** from the list
5. Confirm pairing on camera
6. LED on ESP32 will blink when connected

For detailed troubleshooting, see [CAMERA_PAIRING.md](docs/CAMERA_PAIRING.md).

---

## Configure Your Slicer

Add layer change G-code command to your slicer so the ESP32 knows when to take photos.

### Quick Setup by Slicer

**PrusaSlicer / SuperSlicer:**
- Go to **Printer Settings → Custom G-code → Layer Change G-code**
- Add: `;LAYER_CHANGE`
- Save and set as default printer

**Cura:**
- Go to **Printer → Manage Printers → Machine Settings → Custom G-code**
- In **Between Layers** section, add: `;LAYER_CHANGE`
- Click **Close**

**OrcaSlicer:**
- Go to **Printer Settings → Machine G-code → Layer Change**
- Add: `;LAYER_CHANGE`
- Click **Save**

**Simplify3D:**
- Go to **Machine Control → Custom Scripts → Layer Change Script**
- Add: `;LAYER_CHANGE`
- Save printer profile

**BambuStudio:**
- Go to **Printer Settings → Machine Scripts → Layer Change**
- Add: `;LAYER_CHANGE`
- Save

For detailed slicer instructions: **[GCODE_CONFIG.md](docs/GCODE_CONFIG.md)**

---

## First Print Verification

### Pre-Print Checklist

- [ ] ESP32 powered and connected
- [ ] ESP32 detected on host as `/dev/ttyACM*`
- [ ] `timelapse_monitor` service running on host
- [ ] Canon camera powered on and in range
- [ ] Camera shows ✓ Connected in Bluetooth settings
- [ ] Slicer has `;LAYER_CHANGE` in layer change G-code
- [ ] G-code exported with the configured slicer profile

### During Print

1. **Start your print** via Klipper, OctoPrint, or printer UI
2. **Check monitor logs** on host for trigger events
3. **Confirm camera captures** at layer markers

Example service log check:

```bash
sudo journalctl -u timelapse_monitor -f
```

Typical output:
   ```
   [HH:MM:SS] Detected layer photo trigger: ...
   [HH:MM:SS] >>> Triggering camera!
   ```

### After Print

1. Check your camera's image gallery
2. Verify you have photos for each layer
3. Compile into timelapse video (use any video editor or ffmpeg)

---

## Troubleshooting

### Issue: ESP32 won't flash

**Solution:**
1. Put ESP32 in bootloader mode:
   - Hold BOOT button
   - Press RESET button
   - Release RESET, then BOOT
2. Try again: `pio run -t upload`

### Issue: WiFi AP not visible

**Check serial output:**
```bash
pio device monitor
```

Look for: `WiFi AP is running!`

If not there:
1. Try uploading again
2. Check USB connection is secure
3. Verify correct board selected: `esp32-c3-devkitm-1`

### Issue: Can't connect to web interface

1. Verify WiFi connected to **CameraController-Setup**
2. Try accessing: http://192.168.4.1 (not localhost)
3. Check firewall isn't blocking
4. Try different browser
5. Restart both ESP32 and computer

### Issue: Camera won't pair

See **[CAMERA_PAIRING.md](docs/CAMERA_PAIRING.md)** for detailed troubleshooting

### Issue: Photos not triggering

1. Verify G-code has `;LAYER_CHANGE` (open exported file in text editor)
2. Check `timelapse_monitor` logs on host
3. Confirm monitor can write to `/dev/ttyACM*`
4. Try manual trigger from web interface
5. Check camera battery and sleep settings

### Issue: Too many/few photos

1. Verify only ONE `;LAYER_CHANGE` per layer in G-code
2. Check slicer isn't duplicating the command
3. See [GCODE_CONFIG.md](docs/GCODE_CONFIG.md) for slicer verification steps

---

## Getting Help

**Documentation:**
- [Camera Pairing Guide](docs/CAMERA_PAIRING.md) - Detailed Bluetooth pairing help
- [G-code Configuration](docs/GCODE_CONFIG.md) - Slicer setup by model
- [Development Guide](docs/DEVELOPMENT.md) - Contributing and advanced topics
- [Hardware Wiring](WIRING.md) - USB-C host connection only

**GitHub Issues:**
- Check existing issues
- Create new issue with:
  - What you were trying to do
  - What went wrong
   - `timelapse_monitor` logs (if applicable)
  - Your hardware setup

**Service Logs:**
When troubleshooting, capture service logs:
```bash
sudo journalctl -u timelapse_monitor -n 200 > debug_log.txt
# Share debug_log.txt in your issue
```

---

## Next Steps

- Tune marker strategy in [docs/GCODE_CONFIG.md](docs/GCODE_CONFIG.md)
- Review BLE pairing details in [docs/CAMERA_PAIRING.md](docs/CAMERA_PAIRING.md)
- Use [SETUP.md](SETUP.md) only for deeper configuration details
