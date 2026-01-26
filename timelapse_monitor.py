#!/usr/bin/env python3
import asyncio
import websockets
import json
import subprocess
import time

MOONRAKER_WS = "ws://localhost:7125/websocket"

async def monitor_console():
    print("Connecting to Moonraker websocket...")
    
    async with websockets.connect(MOONRAKER_WS) as websocket:
        # Subscribe to console output
        subscribe_msg = {
            "jsonrpc": "2.0",
            "method": "server.websocket.id",
            "id": 1
        }
        await websocket.send(json.dumps(subscribe_msg))
        
        print("Monitoring console for CAMERA_TRIGGER...\n")
        
        async for message in websocket:
            try:
                data = json.loads(message)
                
                # Debug: print all messages
                if "method" in data:
                    print(f"[DEBUG] Method: {data['method']}")
                
                # Check for console output notifications
                if "method" in data and data["method"] == "notify_gcode_response":
                    response = data.get("params", [None])[0]
                    print(f"[DEBUG] Response: {response}")
                    if response and "CAMERA_TRIGGER" in response:
                        timestamp = time.strftime('%H:%M:%S')
                        print(f"[{timestamp}] Detected: {response.strip()}")
                        print(f"[{timestamp}] >>> Triggering camera!")
                        result = subprocess.run(['sh', '-c', 'echo "trigger" > /dev/ttyACM4'], 
                                     check=False, capture_output=True)
                        print(f"[{timestamp}] Command result: {result.returncode}")
                        
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
