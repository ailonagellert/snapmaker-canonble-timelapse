#!/usr/bin/env python3
import serial
import time

try:
    ser = serial.Serial('COM3', 115200, timeout=1)
    print("Connected to COM3")
    print("Waiting for output...")
    
    for i in range(30):  # Read for 30 seconds
        if ser.in_waiting:
            data = ser.read(ser.in_waiting).decode('utf-8', errors='ignore')
            print(data, end='')
        time.sleep(0.1)
        
except Exception as e:
    print(f"Error: {e}")
finally:
    if 'ser' in locals():
        ser.close()
