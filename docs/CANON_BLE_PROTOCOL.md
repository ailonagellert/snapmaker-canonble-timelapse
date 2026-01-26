# Canon Bluetooth Protocol Notes

## Overview

Canon EOS cameras with Bluetooth use a proprietary BLE (Bluetooth Low Energy) protocol for remote control. This document contains research notes and implementation details.

## BLE Service Information

### Primary Service UUID
```
Service: 00050000-0000-1000-8000-00805f9b34fb
```

This appears to be a Canon proprietary service, not a standard BLE service.

### Characteristics

#### Shutter Control
```
UUID: 00050001-0000-1000-8000-00805f9b34fb
Properties: Write, Notify
```

Used for triggering camera shutter.

#### Pairing/Status
```
UUID: 00050002-0000-1000-8000-00805f9b34fb
Properties: Read, Notify
```

Used for pairing confirmation and status updates.

## Command Protocol

### Shutter Commands

The following byte sequences have been observed:

**Press Shutter:**
```cpp
{0x01, 0x00, 0x00}  // Press shutter button
```

**Release Shutter:**
```cpp
{0x00, 0x00, 0x00}  // Release shutter button
```

**Focus Press (Half-press):**
```cpp
{0x00, 0x01, 0x00}  // Press focus (AF)
```

**Focus Release:**
```cpp
{0x00, 0x00, 0x00}  // Release focus
```

### Full Shutter Cycle

For a complete photo with autofocus:

1. Send focus press: `{0x00, 0x01, 0x00}`
2. Wait 500ms (for AF to complete)
3. Send shutter press: `{0x01, 0x00, 0x00}`
4. Wait 100ms (hold shutter)
5. Send release: `{0x00, 0x00, 0x00}`

## Camera Models

### Tested
- **Canon EOS RP** - Working ✅

### Should Work (Unconfirmed)
- Canon EOS R
- Canon EOS R5
- Canon EOS R6
- Canon EOS R7
- Canon EOS R10
- Canon EOS M50 Mark II

### Camera Setup Required

On the Canon camera, you must:

1. Enable Bluetooth in menu:
   - Menu → Wireless Communication
   - Bluetooth Function → Enable

2. Enable Remote Control:
   - Remote Control (Bluetooth) → Enable

3. Pairing Mode:
   - Camera will advertise with name like "EOS RP" or "Canon EOS RP"
   - Some models require "Pairing" submenu activation

## BLE Connection Process

### 1. Scanning

Look for devices advertising with names containing:
- "Canon"
- "EOS"
- Model-specific names

### 2. Connection

Standard BLE connection to the camera's MAC address.

### 3. Service Discovery

Query for service `00050000-0000-1000-8000-00805f9b34fb`.

### 4. Characteristic Access

Get handle to characteristic `00050001-0000-1000-8000-00805f9b34fb`.

### 5. Command Transmission

Write command bytes to the characteristic (no response needed).

## Alternative Approaches

### Canon Camera Connect App Protocol

Canon's official app uses a more complex protocol that includes:
- Image transfer
- Live view streaming
- Full camera control
- Settings adjustment

This is likely based on PTP/IP over BLE but is undocumented.

### CCAPI (Canon Camera Control API)

Some Canon cameras support HTTP-based control via WiFi:
- Requires WiFi connection to camera
- RESTful API for control
- Not available on all models
- Requires camera WiFi setup

**Not used in this project** because:
- Requires dual-connection (WiFi + printer USB)
- More complex setup
- BLE is simpler for basic shutter control

## Reverse Engineering Resources

If you need to update UUIDs or commands for a different camera:

### Tools

1. **nRF Connect** (Android/iOS)
   - Best tool for BLE exploration
   - Can read all services and characteristics
   - Log all communications

2. **LightBlue** (iOS)
   - Similar to nRF Connect
   - Good for quick testing

3. **Wireshark with Bluetooth**
   - Capture BLE traffic between phone and camera
   - Requires Bluetooth sniffer hardware

4. **hcitool / bluetoothctl** (Linux)
   - Command-line BLE tools
   - Good for scripting

### Process

1. Pair camera with Canon Camera Connect app on phone
2. Use BLE sniffer to capture traffic
3. Trigger shutter in app
4. Analyze captured packets
5. Identify write commands to shutter characteristic
6. Extract byte sequences
7. Test with ESP32

## Known Limitations

### What Works
- ✅ Shutter trigger
- ✅ Focus + shutter (half-press, full-press)
- ✅ Basic remote control
- ✅ Connection status

### What Doesn't Work (Yet)
- ❌ Live view streaming
- ❌ Image download over BLE
- ❌ Camera settings control (ISO, aperture, shutter speed)
- ❌ Focus point selection
- ❌ Video recording start/stop
- ❌ Camera status queries (battery, shots remaining)

### Workarounds

For advanced features:
- Use Canon's WiFi API (CCAPI) instead of BLE
- Pre-configure camera settings manually
- Use manual focus mode
- Check camera status via LCD screen

## Power Considerations

### BLE Power Usage

- **Camera battery drain:** Moderate
  - BLE is low power, but camera must stay awake
  - Expect ~10-20% faster battery drain with BLE active
  - Recommend AC adapter for long prints

- **ESP32 power:** ~150mA with BLE active
  - Not significant compared to WiFi usage

### Sleep Mode

Canon cameras may enter sleep mode:
- **Symptom:** Connection lost after inactivity
- **Solution:** 
  - Disable auto-sleep in camera menu
  - Or send periodic "keep-alive" commands (every 30 seconds)

## Future Improvements

### Possible Enhancements

1. **Bidirectional Communication**
   - Read camera battery status
   - Get shots remaining
   - Confirm photo was taken

2. **Advanced Control**
   - Adjust exposure compensation
   - Change ISO/aperture
   - Select focus points

3. **Image Transfer**
   - Download thumbnails over BLE
   - Preview images on web interface
   - Automatic timelapse compilation

4. **Multiple Cameras**
   - Connect to multiple cameras simultaneously
   - Synchronized shooting
   - Different angles

## References

### Unofficial Documentation

- BLE Protocol reverse engineering: Community forums
- Canon Camera Connect app analysis: XDA Developers
- PTP/IP specification: ISO 15740

### Official Canon Resources

- Canon CCAPI Documentation (for WiFi control)
- Canon SDK (requires application/approval)
- Camera Connect app (reference implementation)

### Related Projects

- **gphoto2** - USB camera control (not BLE)
- **Magic Lantern** - Canon firmware addon (different approach)
- **CHDK** - Canon Hack Development Kit (Canon PowerShot cameras)

## Security Note

⚠️ **Bluetooth Security:**

- BLE connection is **not encrypted** by default in this implementation
- Commands are sent in plaintext
- Camera pairing provides minimal security

For a production/commercial deployment, consider:
- Implementing BLE encryption
- Using authentication
- Secure pairing process

For hobbyist/personal use (this project), security is not critical since:
- Local BLE range (~10m)
- Worst case: someone triggers your camera remotely
- No sensitive data transmitted

## Troubleshooting

### Camera Won't Connect

1. **Check Bluetooth is enabled** in camera menu
2. **Power cycle camera** - Turn off and on
3. **Check if already paired** - Unpair from other devices
4. **Distance** - Move ESP32 closer (BLE range limited)
5. **Interference** - Turn off other 2.4GHz devices

### Commands Not Working

1. **Verify connection** - Check `isConnected()` returns true
2. **Check camera mode** - Must be in photo mode (not video)
3. **Camera sleep** - Wake camera by half-pressing shutter button
4. **Memory card** - Ensure card is inserted and has space
5. **Battery** - Low battery may prevent shutter

### Inconsistent Behavior

1. **Signal strength** - Keep ESP32 within 5 meters of camera
2. **Timing** - Increase delays between commands
3. **Focus time** - Some lenses need longer to autofocus (increase `focusDelay`)

---

**Note:** This protocol information is based on reverse engineering and community research. Canon has not officially documented this BLE protocol. Implementation may vary by camera model and firmware version.
