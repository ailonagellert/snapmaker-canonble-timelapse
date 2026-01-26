#!/usr/bin/env python3
import time
import subprocess
import urllib.request
import json

MOONRAKER_URL = "http://localhost:7125"
last_message = None

print("Monitoring Moonraker console for CAMERA_TRIGGER...")

while True:
    try:
        # Get recent console output from Moonraker
        req = urllib.request.Request(f"{MOONRAKER_URL}/server/gcode_store?count=5")
        with urllib.request.urlopen(req, timeout=2) as response:
            data = json.loads(response.read())
            messages = data.get("result", {}).get("gcode_store", [])
            
            for msg in messages:
                message_text = msg.get("message", "")
                msg_time = msg.get("time")
                
                # Check if this is a new message we haven't seen
                if message_text != last_message and "CAMERA_TRIGGER" in message_text:
                    timestamp = time.strftime('%H:%M:%S')
                    print(f"[{timestamp}] Detected: {message_text}")
                    print(f"[{timestamp}] >>> Triggering camera!")
                    
                    result = subprocess.run(['sh', '-c', 'echo "trigger" > /dev/ttyACM4'], 
                                          check=False, capture_output=True)
                    print(f"[{timestamp}] Result: {result.returncode}")
                    
                    last_message = message_text
                    break
        
        time.sleep(0.5)  # Poll twice per second
        
    except Exception as e:
        print(f"Error: {e}")
        time.sleep(2)
