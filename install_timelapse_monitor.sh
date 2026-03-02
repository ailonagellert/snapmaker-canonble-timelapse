#!/usr/bin/env bash
# timelapse_monitor Installation Script
# Installs timelapse monitoring service on Klipper/Moonraker host

set -e

# Color codes for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Configuration
MOONRAKER_HOST="${MOONRAKER_HOST:-localhost}"
MOONRAKER_PORT="${MOONRAKER_PORT:-7125}"
INSTALL_DIR="${INSTALL_DIR:-/opt/timelapse_monitor}"
VENV_DIR="${INSTALL_DIR}/venv"
SERVICE_NAME="timelapse_monitor"

echo -e "${GREEN}================================${NC}"
echo -e "${GREEN}Timelapse Monitor Installation${NC}"
echo -e "${GREEN}================================${NC}\n"

# Check if running as root (not required, but helpful for service install)
if [[ $EUID -ne 0 ]]; then
   echo -e "${YELLOW}⚠ Not running as root. Service auto-start will not be installed.${NC}"
   echo -e "${YELLOW}  You can still run manually with: python3 /opt/timelapse_monitor/timelapse_monitor.py${NC}\n"
   INSTALL_SERVICE=false
else
   INSTALL_SERVICE=true
fi

# Step 1: Create installation directory
echo -e "${GREEN}[1/5]${NC} Creating installation directory..."
sudo mkdir -p "$INSTALL_DIR"
sudo chown -R $USER:$USER "$INSTALL_DIR"
echo -e "${GREEN}✓${NC} Directory created: $INSTALL_DIR\n"

# Step 2: Copy files
echo -e "${GREEN}[2/5]${NC} Copying timelapse_monitor files..."
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
if [ -f "$SCRIPT_DIR/scripts/host/timelapse_monitor.py" ]; then
    cp "$SCRIPT_DIR/scripts/host/timelapse_monitor.py" "$INSTALL_DIR/"
else
    cp "$SCRIPT_DIR/timelapse_monitor.py" "$INSTALL_DIR/"
fi
chmod +x "$INSTALL_DIR/timelapse_monitor.py"
echo -e "${GREEN}✓${NC} Files copied\n"

# Step 3: Create Python virtual environment
echo -e "${GREEN}[3/5]${NC} Setting up Python virtual environment..."
python3 -m venv "$VENV_DIR"
source "$VENV_DIR/bin/activate"
pip install --upgrade pip
pip install websockets requests
deactivate
echo -e "${GREEN}✓${NC} Virtual environment ready\n"

# Step 4: Create systemd service file (if root)
if [ "$INSTALL_SERVICE" = true ]; then
    echo -e "${GREEN}[4/5]${NC} Creating systemd service..."
    
    SERVICE_FILE="/etc/systemd/system/${SERVICE_NAME}.service"
    
    sudo tee "$SERVICE_FILE" > /dev/null <<EOF
[Unit]
Description=Timelapse Monitor for ESP32 Camera Controller
After=network.target moonraker.service
Wants=moonraker.service

[Service]
Type=simple
User=$USER
WorkingDirectory=$INSTALL_DIR
Environment="MOONRAKER_WS=ws://${MOONRAKER_HOST}:${MOONRAKER_PORT}/websocket"
ExecStart=$VENV_DIR/bin/python3 $INSTALL_DIR/timelapse_monitor.py
Restart=always
RestartSec=10

[Install]
WantedBy=multi-user.target
EOF
    
    sudo systemctl daemon-reload
    echo -e "${GREEN}✓${NC} Service file created at: $SERVICE_FILE\n"
else
    echo -e "${GREEN}[4/5]${NC} Skipping systemd service (requires root)\n"
fi

# Step 5: Display next steps
echo -e "${GREEN}[5/5]${NC} Installation complete!\n"

echo -e "${GREEN}================================${NC}"
echo -e "${GREEN}Next Steps:${NC}"
echo -e "${GREEN}================================${NC}\n"

if [ "$INSTALL_SERVICE" = true ]; then
    echo "1. Review configuration (optional):"
    echo "   nano $INSTALL_DIR/timelapse_monitor.py"
    echo ""
    echo "2. Start the service:"
    echo "   sudo systemctl start $SERVICE_NAME"
    echo ""
    echo "3. Enable auto-start on boot:"
    echo "   sudo systemctl enable $SERVICE_NAME"
    echo ""
    echo "4. Check status:"
    echo "   sudo systemctl status $SERVICE_NAME"
    echo ""
    echo "5. View logs:"
    echo "   sudo journalctl -u $SERVICE_NAME -f"
else
    echo "1. Activate virtual environment:"
    echo "   source $VENV_DIR/bin/activate"
    echo ""
    echo "2. Set environment variable:"
    echo "   export MOONRAKER_WS=ws://${MOONRAKER_HOST}:${MOONRAKER_PORT}/websocket"
    echo ""
    echo "3. Run monitor:"
    echo "   python3 $INSTALL_DIR/timelapse_monitor.py"
fi

echo ""
echo -e "${GREEN}Configuration${NC}:"
echo "  Moonraker: ws://${MOONRAKER_HOST}:${MOONRAKER_PORT}/websocket"
echo "  Install Dir: $INSTALL_DIR"
echo ""
echo -e "${YELLOW}Troubleshooting:${NC}"
echo "  - Check firewall: port ${MOONRAKER_PORT} must be accessible"
echo "  - Verify Moonraker is running: ps aux | grep moonraker"
echo "  - Check logs for connection errors"
echo ""
