#!/usr/bin/env python3
import subprocess
import time

print("Monitoring for CAMERA_TRIGGER messages...")
try:
    proc = subprocess.Popen(['tail', '-F', '/tmp/klippy.log'],
                           stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    
    for line in proc.stdout:
        if 'CAMERA_TRIGGER' in line:
            print(f"[{time.strftime('%H:%M:%S')}] Triggering camera...")
            subprocess.run(['sh', '-c', 'echo "trigger" > /dev/ttyACM4'], check=False)
except KeyboardInterrupt:
    print("\nStopped")
    proc.terminate()