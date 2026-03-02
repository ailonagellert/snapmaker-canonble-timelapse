# Hardware Wiring Guide (USB-C Only)

This project runs with one required physical connection during operation:

- ESP32-C3 USB-C → Klipper/Moonraker host USB

No GPIO wiring is needed.

## Operation Topology

```
Printer ──(normal Klipper connection)──► Klipper/Moonraker Host ◄──USB── ESP32-C3
                                                                         │
                                                                      BLE
                                                                         ▼
                                                                    Canon EOS
```

## Required Connections

### 1) Keep printer wiring unchanged
- Leave printer-to-host wiring exactly as your existing Klipper setup uses.

### 2) Connect ESP32-C3 to host via USB-C
- Plug ESP32-C3 USB-C into the same host that runs Klipper/Moonraker.
- Verify the device appears as `/dev/ttyACM0` (or another `/dev/ttyACM*`).

### 3) Pair camera over BLE
- Pair Canon camera with ESP32-C3.
- Keep camera within Bluetooth range (typically up to ~10 m).

## Flashing Firmware

### Option A: Flash from a computer
1. Connect ESP32-C3 to your computer via USB
2. Run:
   ```bash
   pio run --target upload
   ```
3. Move ESP32-C3 back to the Klipper host for operation

### Option B: Flash from printer host over SSH
Yes, this works if:
- ESP32 is visible as `/dev/ttyACM*`
- `platformio`/`esptool` is installed on host
- SSH user has serial-device permissions

## Cable Guidance

- Use a data-capable USB cable (not charge-only)
- Keep USB length reasonable (typically <= 2 m)
- If detection fails, swap cable first

## Quick Verification

1. Host sees ESP32 under `/dev/ttyACM*`
2. `timelapse_monitor.py` can send `trigger`
3. Camera captures photo during manual trigger test

## Troubleshooting

### ESP32 not detected
- Re-seat USB cable
- Try another host USB port
- Use known-good data cable
- Check host logs (`dmesg`) and `/dev/ttyACM*`

### Can’t flash over SSH
- Install `platformio`/`esptool` on host
- Verify serial permissions (often `dialout`)
- Flash once from PC to validate board/toolchain

## Related Docs

- [INSTALLATION.md](INSTALLATION.md)
- [SETUP.md](SETUP.md)
- [docs/CAMERA_PAIRING.md](docs/CAMERA_PAIRING.md)
