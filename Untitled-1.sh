cat <<'EOF' > /tmp/trigger_camera.sh
#!/bin/sh
echo "trigger" > /dev/ttyACM4
EOF
chmod +x /tmp/trigger_camera.sh