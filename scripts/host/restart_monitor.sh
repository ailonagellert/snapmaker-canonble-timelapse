#!/bin/bash
# Restart timelapse monitor

detect_camera_device() {
	local by_id_first
	local acm_latest

	by_id_first=$(ls -1 /dev/serial/by-id/* 2>/dev/null | head -n1)
	if [ -n "$by_id_first" ]; then
		echo "$by_id_first"
		return 0
	fi

	acm_latest=$(ls -1 /dev/ttyACM* 2>/dev/null | sort -V | tail -n1)
	if [ -n "$acm_latest" ]; then
		echo "$acm_latest"
		return 0
	fi

	return 1
}

CAMERA_DEVICE=$(detect_camera_device)

if [ -z "$CAMERA_DEVICE" ]; then
	echo "ERROR: No camera serial device found (/dev/serial/by-id/* or /dev/ttyACM*)"
	exit 1
fi

export CAMERA_DEVICE
echo "Using camera device: $CAMERA_DEVICE"

echo "Stopping timelapse monitor..."
pkill -9 -f timelapse_monitor.py
sleep 1

echo "Starting timelapse monitor..."
python3 /userdata/scripts/timelapse_monitor.py &
sleep 1

echo "Timelapse monitor started"
ps aux | grep timelapse_monitor.py | grep -v grep
