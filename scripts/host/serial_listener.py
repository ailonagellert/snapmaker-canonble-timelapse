#!/usr/bin/env python3
"""
Keep serial port open and forward camera triggers
Uses CAMERA_DEVICE/SERIAL_PORT or auto-detection for reliable triggering
"""
import serial
import sys
import time
import os
import glob

BAUD_RATE = 115200

def resolve_serial_port():
    forced = os.environ.get("CAMERA_DEVICE", "").strip() or os.environ.get("SERIAL_PORT", "").strip()
    if forced:
        return forced

    by_id_devices = sorted(glob.glob('/dev/serial/by-id/*'))
    if by_id_devices:
        return by_id_devices[0]

    acm_devices = sorted(glob.glob('/dev/ttyACM*'))
    if acm_devices:
        return acm_devices[-1]

    return "/dev/ttyACM0"

def main():
    serial_port = resolve_serial_port()
    try:
        ser = serial.Serial(serial_port, BAUD_RATE, timeout=1)
        print(f"Serial port {serial_port} opened at {BAUD_RATE} baud")
        
        while True:
            try:
                if ser.in_waiting:
                    data = ser.readline()
                    if data:
                        print(f"[Serial] {data.decode().strip()}")
            except Exception as e:
                print(f"Error reading: {e}")
            
            time.sleep(0.1)
    
    except serial.SerialException as e:
        print(f"Failed to open {serial_port}: {e}")
        sys.exit(1)
    except KeyboardInterrupt:
        print("\nStopped")
        ser.close()

if __name__ == "__main__":
    main()
