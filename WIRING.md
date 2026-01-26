# Hardware Wiring Guide

## ESP32-C3 Pin Configuration

### Default Pin Assignments

```
ESP32-C3-DevKitM-1
┌─────────────────┐
│                 │
│  GPIO 8  ──────┼──── Status LED (built-in)
│  GPIO 9  ──────┼──── Manual Trigger Button (optional)
│                 │
│  USB-C   ──────┼──── Computer/OctoPrint
│  UART0   ──────┼──── 3D Printer Serial
│                 │
│  GND     ──────┼──── Ground
│  3V3     ──────┼──── 3.3V Power (for button/LED)
│                 │
└─────────────────┘
```

## Connection Options

### Option 1: Direct USB Passthrough (Recommended)

**No additional wiring needed!** Just plug the ESP32-C3 USB-C port directly into your printer:

```
[Printer USB Port] ──USB-C Cable─► [ESP32-C3 USB-C] ──USB─► [Computer]
```

The ESP32-C3 acts as a transparent USB serial bridge. The printer sees it as a normal USB serial device, and your computer sees the ESP32-C3 forwarding all printer communications.

**Connection Steps:**
1. Plug USB-C cable from your printer's USB port into the ESP32-C3's USB-C port
2. Connect ESP32-C3 to your computer via a second USB connection (if your board has a separate programming port)
3. **Or** use the same USB-C port for both (ESP32-C3 in USB device mode)

### Option 2: With Manual Button

Add a push button for manual camera trigger:

```
GPIO 9 ──────┐
             │
         ┌───▼───┐
         │ Button │
         └───┬───┘
             │
GND ─────────┘
```

**Button Wiring:**
- One terminal to GPIO 9
- Other terminal to GND
- Internal pull-up enabled (no external resistor needed)

### Option 3: With Status LED (Optional)

If your board doesn't have a built-in LED:

```
GPIO 8 ───[ 220Ω ]──►|──── GND
                    LED
```

**LED Wiring:**
- Anode (+) to GPIO 8 through 220Ω resistor
- Cathode (-) to GND

## USB Connection Details

### ESP32-C3 USB-C Direct Connection (Recommended)

The ESP32-C3 has **native USB support** and can act as a USB serial device:

**Simple Setup:**
```
Printer USB Port ──► ESP32-C3 USB-C Port
```

The ESP32-C3 will:
1. **Enumerate as a USB serial device** to the printer
2. **Forward all data** between printer and your computer/OctoPrint
3. **Monitor G-code** in real-time for layer changes
4. **Trigger camera** via Bluetooth when needed

**Programming/Debugging:**
- Same USB-C port used for flashing firmware
- Serial monitor output available during operation
- No separate programmer needed

### How It Works

The ESP32-C3's USB-C port provides:
- **USB CDC (Serial)** - Acts as virtual COM port
  - Printer sends G-code → ESP32 forwards to computer
  - Computer sends commands → ESP32 forwards to printer
  - ESP32 monitors all traffic for layer changes
  
- **Transparent Passthrough** - No data modification
  - Full baud rate support (up to 921600)
  - Works with any printer that uses USB serial
  - Compatible with OctoPrint, Fluidd, Mainsail, Repetier

### Physical Connection

**What you need:**
- USB-C to USB-A cable (or USB-C to USB-C depending on your printer)
- Connect ESP32-C3's USB-C port directly to printer's USB port

**The printer sees:**
- A standard USB serial device
- No difference from direct computer connection
- Same baud rate and protocol

**Your computer sees:**
- ESP32-C3 as the printer
- All normal printer communication works
- No configuration changes needed

## Physical Installation

### Mounting Options

1. **Standalone Box**
   - 3D print an enclosure
   - Mount near printer
   - Route cables cleanly

2. **Attached to Printer**
   - Velcro or adhesive mounting
   - Keep ESP32 away from heat sources
   - Ensure good WiFi/Bluetooth signal

3. **Desktop Position**
   - Place ESP32 between printer and computer
   - USB hub can simplify cable management

### Enclosure Design Tips

If 3D printing an enclosure:
- Include mounting holes for M3 screws (standard ESP32 spacing)
- Add ventilation slots (ESP32 can get warm)
- Include LED light pipe for status indication
- Add button hole if using manual trigger
- Label ports (Printer, Computer)

## Cable Requirements

### USB Cables

**You need TWO cables:**

1. **Printer to ESP32-C3:** USB-C cable (data capable, not charge-only!)
   - Check your printer's USB port type:
     - **USB-B (Standard Square)** → USB-B to USB-C cable
     - **USB-C** → USB-C to USB-C cable
     - **Micro-USB** → Micro-USB to USB-C cable
   
2. **ESP32-C3 to Computer:** Standard USB cable
   - Usually USB-A to USB-C or USB-C to USB-C
   - Must support data transfer (test with other devices first)

**⚠️ Important:** Both cables MUST be **data cables**, not charge-only cables!
- **Test:** If the cable works for transferring files to a phone, it will work here
- **Avoid:** Dollar-store cables often are charge-only

### Cable Length Considerations

- **Bluetooth Range:** Camera should be within **10 meters** of ESP32-C3
- **USB Cable Length:** 
  - Printer to ESP32: Keep under **2 meters** for best reliability
  - ESP32 to Computer: Can be up to **5 meters** (USB 2.0 spec limit)
- **Total distance:** Keep entire setup compact when possible

## Power Considerations

### Power Source

The ESP32-C3 can be powered by:
- **USB from computer** (recommended, simplest)
- **External 5V USB power supply** (if running standalone)
- **3.3V regulator** from printer power (advanced users only)

**Typical Power Draw:**
- Idle: ~80mA
- Active (BLE + WiFi): ~150-200mA
- Peak (transmission): ~250mA

### Battery Operation (Not Recommended)

While possible, battery operation is not ideal because:
- ESP32 must stay on during entire print (could be 24+ hours)
- WiFi and BLE are power-hungry
- If it powers off mid-print, timelapse is lost

## Troubleshooting Wiring Issues

### No Serial Communication

1. **Check USB cable** - Must be a data cable, not charge-only
2. **Try different USB port** - Some ports have better compatibility  
3. **Check printer USB port** - Verify it's the correct port (some printers have multiple)
4. **Verify baud rate** - Should be 115200 (auto-detected in most cases)
5. **Check cable orientation** - USB-C is reversible, but try flipping if issues occur

### Button Not Working

1. **Check pull-up** - Internal pull-up should be enabled in code (it is)
2. **Test button** - Use multimeter continuity mode
3. **Verify GPIO** - Make sure GPIO 9 is used

### LED Issues

1. **Check polarity** - LED has correct orientation (+ to GPIO)
2. **Verify resistor** - 220Ω to 1kΩ range works
3. **Test LED** - Connect directly to 3.3V/GND with resistor

### USB Detection Issues

1. **Check cable** - Must be data cable (not charge-only)
2. **Try different port** - Some USB ports have power issues
3. **Update drivers** - Windows may need CH340/CP2102 drivers
4. **Check boot mode** - ESP32 should boot in normal mode (not download)

## Safety Warnings

⚠️ **Important Safety Notes:**

1. **3.3V Logic Only**
   - ESP32-C3 is **NOT 5V tolerant**
   - Do not connect 5V signals to GPIO pins
   - Use level shifter if printer uses 5V logic

2. **Power Protection**
   - Don't exceed 500mA from USB port
   - Use external power if adding many accessories

3. **ESD Protection**
   - ESP32 is sensitive to static electricity
   - Ground yourself before handling
   - Use anti-static bags for storage

4. **Heat Management**
   - Don't place ESP32 near printer hotend or bed
   - Ensure adequate ventilation
   - Operating temperature: -40°C to +85°C

5. **Short Circuit Protection**
   - Double-check all connections before powering on
   - Use insulated enclosure
   - Keep away from metal printer frame when exposed

## Tested Configurations

### Configuration 1: OctoPrint Setup
```
RaspberryPi (OctoPrint) ──USB─► ESP32-C3 ──USB─► Printer
                                   │
                                Bluetooth
                                   ▼
                              Canon EOS RP
```

### Configuration 2: Direct Computer
```
Computer ──USB─► ESP32-C3 ──USB─► Printer
                    │
                 Bluetooth
                    ▼
               Canon EOS RP
```

### Configuration 3: Standalone (Future)
```
                ESP32-C3 (with WiFi)
                   │  │
          USB─────┘  └─────Bluetooth
           │                   │
        Printer          Canon EOS RP
                   
(Sends G-code over WiFi to host)
```

## Next Steps

After wiring is complete:
1. ✅ Verify all connections
2. ✅ Power on ESP32
3. ✅ Check for WiFi AP "CameraController-Setup"
4. ✅ Connect and access web interface
5. ✅ Follow [SETUP.md](SETUP.md) for software configuration

---

**Need help?** Check the troubleshooting section or review serial monitor output for detailed debugging information.
