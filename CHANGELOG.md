# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [1.0.0] - 2024-02-02

### Added

- **Plug-and-play ESP32-C3 camera controller** for 3D printer timelapse photography
- **Bluetooth connectivity** to Canon EOS cameras for wireless shutter triggering
- **Smart G-code parsing** with support for multiple slicer formats
- **Layer change detection** with automatic photo triggering
- **Web configuration interface** at http://192.168.4.1 for easy setup
- **WiFi Access Point mode** for initial setup (CameraController-Setup)
- **Manual trigger button** support (GPIO 9) for testing
- **LED status indicators** to show device state and photo captures
- **USB serial passthrough** to transparently relay G-code to printer
- **Auto-connect Bluetooth** to paired Canon camera on startup
- **Flexible G-code pattern matching** for multiple slicer formats:
  - PrusaSlicer/SuperSlicer: `;LAYER_CHANGE`
  - Cura: `;LAYER_CHANGE` or custom markers
  - OrcaSlicer: `;LAYER_CHANGE`
  - Simplify3D: `;LAYER_CHANGE`
  - BambuStudio: `;LAYER_CHANGE`

### Documentation

- Comprehensive [Installation Guide](INSTALLATION.md)
- [Camera Pairing Guide](docs/CAMERA_PAIRING.md) with troubleshooting
- [G-code Configuration Guide](docs/GCODE_CONFIG.md) for all supported slicers
- [Hardware Wiring Guide](WIRING.md) with pinouts
- [Development Guide](docs/DEVELOPMENT.md) for contributors
- [Setup Guide](SETUP.md) for firmware building
- Install script for `timelapse_monitor` Python tool

### Features

- ✅ Transparent USB serial bridge (no printer modifications needed)
- ✅ BLE coexistence with WiFi AP mode
- ✅ Real-time photo count and status via web interface
- ✅ Configurable stabilization delays for focus adjustment
- ✅ JSON-based configuration storage
- ✅ mDNS support for hostname resolution (cameracontroller.local)
- ✅ Systemd service support for timelapse monitoring

### Security

- Hardcoded WiFi credentials removed - load from config.json
- .gitignore updated to prevent credential leaks
- Config file exempted from version control

### Hardware Support

- **Tested:** Canon EOS RP
- **Compatible:** Canon EOS R, R5, R6, R7, R10, M50 Mark II, and other Canon EOS models with Bluetooth
- **Printers:** Any Klipper-based printer (Snapmaker U1, Creality CR10-SE, etc.)

### Known Limitations

- Canon PowerShot models not supported (different BLE protocol)
- Older Canon cameras without built-in Bluetooth incompatible
- Requires Klipper for full functionality (OctoPrint support planned)
- Single camera pairing per device

### Project Status

🟢 **Stable Release** - Ready for production use

This is the initial public release. The firmware is tested on real hardware and ready for distribution.

---

## Planned Features (Future Releases)

- [ ] Multi-camera support (trigger multiple cameras)
- [ ] Temperature-based triggering (trigger at specific bed/nozzle temps)
- [ ] Time-based triggering (automatic photo every N minutes)
- [ ] Z-height specific triggering (photos at specific heights)
- [ ] OctoPrint plugin integration
- [ ] Web-based timelapse video generation
- [ ] Mobile app for remote triggering
- [ ] Cloud sync for photos
- [ ] Support for other camera brands (Sony, Nikon with BLE)

---

## Contributing

See [DEVELOPMENT.md](docs/DEVELOPMENT.md) for guidelines on contributing improvements, bug fixes, and new features.

## License

MIT License - See [LICENSE](LICENSE) file
