#!/usr/bin/env python3
"""
Keep serial port open and forward camera triggers
Ensures /dev/ttyACM0 stays active for reliable triggering
"""
import serial
import sys
import time

SERIAL_PORT = "/dev/ttyACM0"
BAUD_RATE = 115200

def main():
    try:
        ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
        print(f"Serial port {SERIAL_PORT} opened at {BAUD_RATE} baud")
        
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
        print(f"Failed to open {SERIAL_PORT}: {e}")
        sys.exit(1)
    except KeyboardInterrupt:
        print("\nStopped")
        ser.close()

if __name__ == "__main__":
    main()
