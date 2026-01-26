#!/usr/bin/env python3
import serial
import time

try:
    ser = serial.Serial('COM3', 115200, timeout=1)
    time.sleep(2)  # Give device time to respond
    
    print("=== Waiting for Serial Output ===\n")
    while True:
        if ser.in_waiting:
            line = ser.readline().decode('utf-8', errors='ignore')
            print(line, end='')
except KeyboardInterrupt:
    print("\n\nStopped by user")
except Exception as e:
    print(f"Error: {e}")
finally:
    try:
        ser.close()
    except:
        pass
