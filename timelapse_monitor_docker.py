#!/usr/bin/env python3
import time
import subprocess
import urllib.request
import json
import os

MOONRAKER_URL = os.getenv("MOONRAKER_URL", "http://10.0.0.217:7125")
PRINTER_HOST = os.getenv("PRINTER_HOST", "root@10.0.0.217")
DEVICE_PATH = os.getenv("DEVICE_PATH", "/dev/ttyACM4")

last_message = None

print(f"Monitoring {MOONRAKER_URL} for CAMERA_TRIGGER...")
print(f"Will trigger via SSH to {PRINTER_HOST}")

while True:
    try:
        req = urllib.request.Request(f"{MOONRAKER_URL}/server/gcode_store?count=5")
        with urllib.request.urlopen(req, timeout=2) as response:
            data = json.loads(response.read())
            messages = data.get("result", {}).get("gcode_store", [])
            
            for msg in messages:
                message_text = msg.get("message", "")
                
                if message_text != last_message and "CAMERA_TRIGGER" in message_text:
                    timestamp = time.strftime('%H:%M:%S')
                    print(f"[{timestamp}] Detected: {message_text}")
                    print(f"[{timestamp}] >>> Triggering camera via SSH...")
                    
                    # SSH to printer and trigger
                    result = subprocess.run(
                        ['ssh', '-o', 'StrictHostKeyChecking=no', 
                         PRINTER_HOST, f'echo "trigger" > {DEVICE_PATH}'],
                        check=False, capture_output=True, timeout=5
                    )
                    print(f"[{timestamp}] Result: {result.returncode}")
                    if result.returncode != 0:
                        print(f"[{timestamp}] Error: {result.stderr.decode()}")
                    
                    last_message = message_text
                    break
        
        time.sleep(0.5)
        
    except Exception as e:
        print(f"Error: {e}")
        time.sleep(2)
