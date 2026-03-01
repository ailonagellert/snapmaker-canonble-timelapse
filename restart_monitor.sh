#!/bin/bash
# Restart timelapse monitor

echo "Stopping timelapse monitor..."
pkill -9 -f timelapse_monitor.py
sleep 1

echo "Starting timelapse monitor..."
python3 /userdata/scripts/timelapse_monitor.py &
sleep 1

echo "Timelapse monitor started"
ps aux | grep timelapse_monitor.py | grep -v grep
