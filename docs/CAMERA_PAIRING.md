# Canon EOS Camera Bluetooth Pairing Guide

Complete step-by-step guide for pairing your Canon EOS camera with the ESP32 Camera Controller.

## Supported Canon Cameras

✓ **Tested & Verified:**
- Canon EOS RP
- Canon EOS R5
- Canon EOS R6

✓ **Should Work:**
- Canon EOS R
- Canon EOS R7
- Canon EOS R10
- Canon EOS M50 Mark II
- Other Canon EOS cameras with Bluetooth

❌ **Not Supported:**
- Older Canon models without built-in Bluetooth
- PowerShot models (different BLE protocol)

## Prerequisites

- Canon camera with Bluetooth capability
- Camera battery fully charged (or plugged in)
- ESP32 Camera Controller flashed with latest firmware
- Camera and ESP32 in same WiFi range (Bluetooth only, not WiFi-dependent)

## Pairing Steps

### On Your Canon Camera

1. **Power on the camera** and ensure battery is sufficient

2. **Access Bluetooth Settings:**
   - Press **MENU** button
   - Navigate to **Bluetooth Settings** (usually in 3rd or 4th tab)
   - Select **Bluetooth Function**
   - Turn **ON**

3. **Enter Pairing Mode:**
   - Return to **Bluetooth Settings**
   - Select **Pairing → New Device**
   - Camera will scan for available Bluetooth devices

4. **Select ESP32 Device:**
   - Look for **"ESP32-Camera-Remote"** in the list
   - Select it to pair
   - Camera may ask for confirmation - confirm it

5. **Verify Connection:**
   - Device should show as ✓ **Connected** 
   - Check LED indicator on ESP32 (will blink to confirm)
   - Status should show in camera's Bluetooth menu

### On Your Computer (Optional - for testing)

If pairing via computer first (not required, but helpful for debugging):

1. Open Bluetooth settings on your computer
2. Add new Bluetooth device
3. Select **"ESP32-Camera-Remote"**
4. PIN should be **0000** (if requested)
5. Confirm pairing

## Troubleshooting

### Camera Won't See ESP32

**Solution 1: Reset Bluetooth on both devices**
- Unplug ESP32 for 5 seconds
- Power cycle camera (OFF → ON)
- Try pairing again

**Solution 2: Check firmware is flashed**
```bash
# Verify by monitoring serial output
pio device monitor
# Should show BLE initialization messages
```

**Solution 3: Ensure proper camera model**
- Confirm your camera has Bluetooth built-in
- Check camera manual for correct Bluetooth menu location
- Some older firmware versions may need updating

### Pairing Fails During Setup

**Solution: Clear existing pairings on camera**
1. Go to **Menu → Bluetooth Settings → Device List**
2. Find any old "ESP32" entries and **Delete**
3. Return to **Pairing → New Device**
4. Try again

### Connected but Camera Won't Trigger

**Solution: Check Android/iOS compatibility mode**
1. In camera **Bluetooth Settings**, look for device compatibility options
2. Ensure set to appropriate mode for ESP32
3. Restart pairing process

**Solution: Verify trigger command is working**
```bash
# Connect to ESP32 via serial monitor
pio device monitor -b 115200

# You should see trigger events in logs
# If not: check camera battery and Bluetooth range
```

## Manual Pairing via Config File (Advanced)

If web interface isn't available, edit `data/config.json`:

```json
{
  "camera": {
    "auto_connect": true,
    "ble_mac_address": "XX:XX:XX:XX:XX:XX",
    "focus_before_shot": false,
    "stabilization_delay_ms": 2000
  }
}
```

Then manually start Bluetooth discovery on camera.

## Camera Won't Auto-Connect After Restart

1. Ensure **Auto-Connect** is enabled in config:
```json
"camera": {
  "auto_connect": true
}
```

2. Camera must have Bluetooth ON and in range
3. First pairing may require manual camera confirmation
4. Subsequent connections should be automatic

## Testing the Connection

### Quick Test: Press Button

If you have optional manual trigger button (GPIO 9):
1. Pair camera successfully
2. Press button on ESP32
3. Camera should take photo (you'll hear shutter sound)

### Test via Web Interface

1. Connect to WiFi AP: **CameraController-Setup**
2. Open **http://192.168.4.1**
3. Click **"Take Photo"** button
4. Camera should trigger immediately

### Test via Serial Monitor

```bash
pio device monitor
# Look for: "[Camera] Taking photo..."
# Then: "[Camera] ✓ Photo captured" or error message
```

## Getting Support

If pairing still fails:

1. **Collect debug logs:**
   ```bash
   pio device monitor --raw > esp32_logs.txt
   # Attempt pairing and capture 1 minute of logs
   ```

2. **Check your camera model:**
   - Is Bluetooth confirmed working in camera manual?
   - Can you pair with your phone successfully?
   - Try pairing with computer first to verify

3. **Verify ESP32 BLE library:**
   - Check `platformio.ini` has correct BLE library
   - Rebuild firmware: `pio clean && pio run --target upload`

## Next Steps

After successful pairing:
- [Add layer change commands to your slicer](GCODE_CONFIG.md)
- [Configure WiFi and advanced settings](../SETUP.md)
- [Set up timelapse monitoring](../INSTALLATION.md)
