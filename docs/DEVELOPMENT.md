# Development & Best Practices Guide

This document outlines best practices for developing, testing, and maintaining the ESP32 Camera Controller.

## Code Standards

### C++ (ESP32 Firmware)

#### Security
- ✓ **NEVER hardcode WiFi credentials** in code
  - Use `data/config.json` for all credentials
  - Load from config file at runtime
  - Example in `config.h`:
    ```cpp
    // config.h - TEMPLATE ONLY
    #define AP_SSID "CameraController-Setup"
    #define AP_PASSWORD "camera123"
    // ^ These are temporary AP defaults, not for persistent storage
    ```

- ✓ **Use JSON config for user settings**
  ```json
  {
    "wifi": {
      "ssid": "YourNetwork",
      "password": "YourPassword"
    }
  }
  ```

#### Memory Management
- ✓ Use `const` for read-only data
- ✓ Minimize dynamic allocations - ESP32 has limited RAM
- ✓ Use proper buffer sizes: 256 bytes for G-code, not 4096
- ✓ Check return values of critical operations

#### Code Organization
- ✓ Use header files in `/include/` for interfaces
- ✓ Keep implementation in `/src/`
- ✓ One class/module per file (e.g., `CanonBLERemote.h/cpp`)
- ✓ Add documentation comments for public methods

#### Serial Output
- ✓ Use consistent logging format: `[Module] Message`
  ```cpp
  Serial.println("[Camera] ✓ Photo captured");
  Serial.printf("[GCode] Layer: %d at Z=%.2f\n", layer, z_height);
  ```
- ✓ Use `Serial.printf()` for formatted output
- ✓ Include timestamps for debugging: check `millis()` if needed

### Python (Host Tools)

#### Style
- ✓ Follow PEP 8
- ✓ Use type hints (Python 3.6+)
  ```python
  def monitor_console() -> None:
      """Monitor G-code from printer."""
  ```
- ✓ Use docstrings for all functions

#### Dependencies
- ✓ List in `requirements.txt`:
  ```
  websockets>=10.0
  requests>=2.28.0
  ```
- ✓ Install in virtual environment: `pip install -r requirements.txt`
- ✓ Pin major versions: `websockets>=10.0,<11.0`

### Documentation

#### Markdown Files
- ✓ Use consistent heading hierarchy (# → ## → ###)
- ✓ Include code examples for all procedures
- ✓ Add troubleshooting sections
- ✓ Include table of contents for long documents

#### Comments
- ✓ Explain WHY, not WHAT
  ```cpp
  // GOOD: Explain the reason
  delay(2000);  // Wait for camera to stabilize after focus

  // BAD: Just describes the code
  delay(2000);  // Wait 2 seconds
  ```

## Build & Test

### PlatformIO Build

```bash
# Clean build (remove artifacts)
pio run -t clean

# Build firmware
pio run -e esp32c3

# Upload to device
pio run -t upload

# Monitor serial output
pio device monitor -b 115200

# Run tests (if configured)
pio test
```

### Testing Checklist

- [ ] Firmware compiles without warnings
- [ ] Device boots and initializes successfully
- [ ] WiFi AP starts and is discoverable
- [ ] Web interface responds at `192.168.4.1`
- [ ] BLE can pair with Canon camera
- [ ] G-code parsing correctly detects layer changes
- [ ] Camera triggers on layer change
- [ ] LED indicators work as expected
- [ ] Serial output shows no errors

### Known Issues & Workarounds

#### WiFi & BLE Coexistence
- **Issue:** WiFi AP and BLE can interfere
- **Solution:** Start WiFi AP first (give it 500ms to stabilize), then initialize BLE
- **Evidence:** See `main.cpp` `setup()` function timing

#### USB Serial Initialization
- **Issue:** USB CDC serial doesn't start immediately
- **Solution:** Add 1000ms delay before first `Serial.println()`
- **Code:** See `setup()` after `Serial.begin()`

## Version Control & Publishing

### Git Setup

```bash
# Initialize repo
git init
git remote add origin https://github.com/yourusername/cameracontroller.git

# Branches
- main: Stable releases
- develop: Active development
- feature/*: Feature branches

# Commits
- Use conventional commits: feat(), fix(), docs(), etc.
- Example: "feat(ble): add auto-reconnect on disconnect"
```

### Before Release

- [ ] Update `FIRMWARE_VERSION` in `config.h`
- [ ] Update version in `platformio.ini` (if applicable)
- [ ] Update `CHANGELOG.md` with changes
- [ ] Review all documentation for accuracy
- [ ] Test on real hardware (not just simulation)
- [ ] Create git tag: `git tag v1.0.0`

### Files to Exclude (.gitignore)

```
# Build artifacts
.pio/
.vscode/
build/
*.pyc
__pycache__/
*.o

# User files
.DS_Store
Thumbs.db
*.backup
*.swp

# Credentials (IMPORTANT!)
.env
local_config.json
wifi_credentials.txt
```

## Continuous Integration / Automation

### GitHub Actions Example

```yaml
name: Build Firmware
on: [push, pull_request]
jobs:
  build:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v2
      - uses: actions/setup-python@v2
        with:
          python-version: '3.9'
      - run: pip install platformio
      - run: pio run -e esp32c3
```

## Performance Optimization

### Memory Usage
- G-code buffer: 256 bytes (adequate for lines up to 250 chars)
- JSON config: Parsed once at startup (not on every action)
- BLE: Uses ~10-15KB stack space

### CPU Usage
- Serial processing: Main loop task
- Web server: Responds to requests asynchronously
- BLE: Callback-driven (minimal polling)

### Power Consumption
- WiFi AP: ~150mA
- BLE connected: ~50-100mA
- Idle: ~30mA
- LED: ~5mA when on

## Debugging Tips

### Enable Verbose Logging
```cpp
// In main.cpp, uncomment Serial.println() statements:
Serial.println("[Main] Taking timelapse photo...");
Serial.println("[Main] ✓ Photo captured");
```

### Monitor Serial Output
```bash
# Real-time logs with filtering
pio device monitor -b 115200 | grep "Camera"

# Save to file
pio device monitor -b 115200 > esp32_debug.log
```

### Common Issues & Solutions

| Symptom | Cause | Fix |
|---------|-------|-----|
| No WiFi AP visible | WiFi not initialized | Check `setup()` WiFi sequence |
| USB serial not working | CDC not enabled in menuconfig | Rebuild with `-DARDUINO_USB_CDC_ON_BOOT=1` |
| G-code not parsed | Serial1 baud mismatch | Verify printer baud = 115200 |
| Camera won't pair | BLE service UUID incorrect | Check `config.h` against camera spec |
| Photos not triggering | G-code pattern not recognized | Add pattern to `config.json` `layer_patterns` |

## Contributing

When adding new features:

1. Create feature branch: `git checkout -b feature/my-feature`
2. Follow code standards (see above)
3. Add tests and documentation
4. Submit pull request with description
5. Ensure all checks pass

## License

This project is licensed under MIT. See LICENSE file for details.

---

**Last Updated:** 2024-01  
**Maintainer:** [Your Name]  
**Questions?** Open an issue on GitHub
