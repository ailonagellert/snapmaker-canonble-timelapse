#!/usr/bin/env python3
import asyncio
import websockets
import json
import subprocess
import time
import glob
import os

MOONRAKER_WS = "ws://localhost:7125/websocket"

# Auto-detect ESP32 serial device
def find_esp32_device():
    """Find ESP32 device by searching /dev/ttyACM*"""
    acm_devices = glob.glob('/dev/ttyACM*')
    if acm_devices:
        device = acm_devices[0]  # Use first available
        print(f"Found ESP32 at: {device}")
        return device
    return None

CAMERA_DEVICE = find_esp32_device()

# Trigger modes (set True/False as needed)
TRIGGER_ON_TOOLCHANGE = False
TRIGGER_ON_PREEXTRUDE_MACRO = False
PREEXTRUDE_MACRO_NAME = "SM_PRINT_PREEXTRUDE_FILAMENT"
TRIGGER_ON_ACTIVATING = False
ACTIVATING_MARKER = "pick extruder"
TRIGGER_ON_LAYER_PHOTO = True
LAYER_PHOTO_MARKER = "LAYER_PHOTO"
TRIGGER_ON_WIPE = False
WIPE_START_MARKER = "WIPE_START"

# Debug mode - log all gcode responses
DEBUG_ALL_RESPONSES = False

async def monitor_console():
    print("Connecting to Moonraker websocket...")
    
    if not CAMERA_DEVICE:
        print("ERROR: Camera device not found! Exiting.")
        return
    
    async with websockets.connect(MOONRAKER_WS) as websocket:
        # Identify websocket
        identify_msg = {
            "jsonrpc": "2.0",
            "method": "server.websocket.id",
            "id": 1
        }
        await websocket.send(json.dumps(identify_msg))

        # Subscribe to status updates for tool changes
        subscribe_status_msg = {
            "jsonrpc": "2.0",
            "method": "printer.objects.subscribe",
            "params": {
                "objects": {
                    "toolhead": ["extruder"]
                }
            },
            "id": 2
        }
        await websocket.send(json.dumps(subscribe_status_msg))
        
        print(f"Monitoring for marker: {LAYER_PHOTO_MARKER}...\n")

        last_extruder = None
        
        async for message in websocket:
            try:
                data = json.loads(message)
                
                # Debug: print all messages
                if "method" in data:
                    print(f"[DEBUG] Method: {data['method']}")
                
                # Tool change detection via status update
                if "method" in data and data["method"] == "notify_status_update":
                    params = data.get("params", [])
                    status = params[0] if params else {}
                    toolhead = status.get("toolhead", {})
                    current_extruder = toolhead.get("extruder")
                    if current_extruder and current_extruder != last_extruder:
                        last_extruder = current_extruder
                        if TRIGGER_ON_TOOLCHANGE:
                            timestamp = time.strftime('%H:%M:%S')
                            print(f"[{timestamp}] Tool change detected: {current_extruder}")
                            print(f"[{timestamp}] >>> Triggering camera!")
                            if CAMERA_DEVICE:
                                result = subprocess.run(['sh', '-c', f'echo "trigger" > {CAMERA_DEVICE}'],
                                            check=False, capture_output=True)
                                print(f"[{timestamp}] Command result: {result.returncode}")
                            else:
                                print(f"[{timestamp}] ERROR: Camera device not found!")

                # Optional: detect pre-extrude macro in console output
                if "method" in data and data["method"] == "notify_gcode_response":
                    response = data.get("params", [None])[0]
                    if DEBUG_ALL_RESPONSES:
                        print(f"[DEBUG RESPONSE] {repr(response)}")
                    
                    if response:
                        if TRIGGER_ON_PREEXTRUDE_MACRO and PREEXTRUDE_MACRO_NAME.lower() in str(response).lower():
                            timestamp = time.strftime('%H:%M:%S')
                            print(f"[{timestamp}] Detected macro: {response.strip()}")
                            print(f"[{timestamp}] >>> Triggering camera!")
                            if CAMERA_DEVICE:
                                result = subprocess.run(['sh', '-c', f'echo "trigger" > {CAMERA_DEVICE}'],
                                            check=False, capture_output=True)
                                print(f"[{timestamp}] Command result: {result.returncode}")
                            else:
                                print(f"[{timestamp}] ERROR: Camera device not found!")

                        if TRIGGER_ON_ACTIVATING and ACTIVATING_MARKER.lower() in str(response).lower():
                            timestamp = time.strftime('%H:%M:%S')
                            print(f"[{timestamp}] Detected tool ready: {response.strip()}")
                            print(f"[{timestamp}] >>> Triggering camera!")
                            if CAMERA_DEVICE:
                                result = subprocess.run(['sh', '-c', f'echo "trigger" > {CAMERA_DEVICE}'],
                                            check=False, capture_output=True)
                                print(f"[{timestamp}] Command result: {result.returncode}")
                            else:
                                print(f"[{timestamp}] ERROR: Camera device not found!")

                        if TRIGGER_ON_LAYER_PHOTO and LAYER_PHOTO_MARKER.lower() in str(response).lower():
                            timestamp = time.strftime('%H:%M:%S')
                            print(f"[{timestamp}] Detected layer photo trigger: {response.strip()}")
                            print(f"[{timestamp}] >>> Triggering camera!")
                            if CAMERA_DEVICE:
                                result = subprocess.run(['sh', '-c', f'echo "trigger" > {CAMERA_DEVICE}'],
                                            check=False, capture_output=True)
                                print(f"[{timestamp}] Command result: {result.returncode}")
                            else:
                                print(f"[{timestamp}] ERROR: Camera device not found!")

                        if TRIGGER_ON_WIPE and WIPE_START_MARKER.lower() in str(response).lower():
                            timestamp = time.strftime('%H:%M:%S')
                            print(f"[{timestamp}] Detected wipe start: {response.strip()}")
                            print(f"[{timestamp}] >>> Triggering camera!")
                            if CAMERA_DEVICE:
                                result = subprocess.run(['sh', '-c', f'echo "trigger" > {CAMERA_DEVICE}'],
                                            check=False, capture_output=True)
                                print(f"[{timestamp}] Command result: {result.returncode}")
                            else:
                                print(f"[{timestamp}] ERROR: Camera device not found!")
                        
            except json.JSONDecodeError:
                pass
            except Exception as e:
                print(f"Error: {e}")

if __name__ == "__main__":
    try:
        asyncio.run(monitor_console())
    except KeyboardInterrupt:
        print("\nStopped")
    except Exception as e:
        print(f"Failed to connect: {e}")
        print("Make sure Moonraker is running on localhost:7125")
