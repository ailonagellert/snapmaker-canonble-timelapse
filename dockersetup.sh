docker build -t camera-monitor .
docker run -d --name camera-monitor \
  -e MOONRAKER_URL=http://10.0.0.217:7125 \
  -e PRINTER_HOST=root@10.0.0.217 \
  -e DEVICE_PATH=/dev/ttyACM4 \
  -v ~/.ssh:/root/.ssh:ro \
  --restart unless-stopped \
  camera-monitor