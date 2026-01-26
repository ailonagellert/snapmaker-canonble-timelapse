# Bill of Materials (BOM)

## Required Components

| Item | Description | Quantity | Est. Cost (USD) | Source |
|------|-------------|----------|----------------|---------|
| ESP32-C3 DevKit | ESP32-C3-DevKitM-1 or compatible | 1 | $4-7 | AliExpress, Amazon, Adafruit |
| USB-C Cable | Data cable (not charge-only) | 1 | $3-5 | Amazon, Monoprice |
| USB Cable | Standard USB cable for printer | 1 | $3-5 | Amazon, Monoprice |
| Canon EOS Camera | With Bluetooth (e.g., EOS RP) | 1 | (Already owned) | - |

**Total: ~$10-17** (excluding camera and optional components)

## Optional Components

| Item | Description | Quantity | Est. Cost (USD) | Purpose |
|------|-------------|----------|----------------|---------|
| Push Button | Tactile momentary switch | 1 | $0.10-0.50 | Manual trigger |
| LED | 3mm or 5mm LED (any color) | 1 | $0.10-0.30 | Status indicator |
| Resistor | 220Ω, 1/4W | 1 | $0.05-0.10 | LED current limiting |
| Jumper Wires | Male-to-female or male-to-male | 5-10 | $2-5 | Connections |
| Breadboard | Small breadboard for prototyping | 1 | $2-5 | Testing |
| Enclosure | 3D printed or project box | 1 | $0-10 | Protection/mounting |

## Tools Required

| Tool | Purpose | If You Don't Have It |
|------|---------|---------------------|
| Computer | Compiling and flashing firmware | Required |
| USB Port | Connecting ESP32 | Required |
| Soldering Iron | (Optional) For permanent connections | Use breadboard/jumpers |
| Multimeter | (Optional) For debugging | Nice to have |
| 3D Printer | (Optional) For printing enclosure | Use project box |

## Where to Buy

### ESP32-C3 Boards

**Recommended Boards:**
- **Espressif ESP32-C3-DevKitM-1** - Official board, well documented
- **Seeed XIAO ESP32C3** - Very compact, good alternative
- **DFRobot FireBeetle ESP32-C3** - Good battery support

**Suppliers:**
- **USA:** Adafruit, SparkFun, Mouser, Digikey
- **Worldwide:** AliExpress, Banggood
- **Europe:** Pimoroni, Reichelt

**Price Comparison:**
- AliExpress: $3-5 (shipping takes 2-4 weeks)
- Amazon: $6-10 (fast shipping)
- Adafruit/SparkFun: $8-12 (supports open source)

### USB Cables

**Important:** Must be **data cables**, not charge-only!

- **USB-C to USB-A:** For ESP32-C3 to computer
- **USB-A to USB-B/Micro:** Depends on your printer

**Recommended:**
- Anker cables (good quality)
- Monoprice cables (cheap, reliable)
- Cable Matters (good selection)

### Optional Components

**Electronics:**
- **Amazon:** Good for small quantities
- **Mouser/Digikey:** Best for variety, fast shipping
- **AliExpress:** Cheapest, slow shipping

**3D Printer Filament:**
- ~50g PLA for basic enclosure
- ~$1-2 worth of filament

## Camera Compatibility

### Confirmed Working

| Camera Model | Bluetooth | Tested | Notes |
|--------------|-----------|---------|-------|
| Canon EOS RP | ✅ Yes | ✅ Yes | Fully working |

### Should Work (Unconfirmed)

| Camera Model | Bluetooth | Expected | Notes |
|--------------|-----------|----------|-------|
| Canon EOS R | ✅ Yes | ⚠️ Should work | Same BLE protocol |
| Canon EOS R5 | ✅ Yes | ⚠️ Should work | Same BLE protocol |
| Canon EOS R6 | ✅ Yes | ⚠️ Should work | Same BLE protocol |
| Canon EOS R7 | ✅ Yes | ⚠️ Should work | Same BLE protocol |
| Canon EOS R10 | ✅ Yes | ⚠️ Should work | Same BLE protocol |
| Canon EOS M50 II | ✅ Yes | ⚠️ Should work | Check BLE menu |

### Not Compatible

| Camera Model | Reason |
|--------------|--------|
| Canon EOS 5D/6D/7D series | No Bluetooth |
| Canon EOS Rebel series (older) | No Bluetooth |
| Canon PowerShot series | Different protocol |
| Non-Canon cameras | Different BLE protocol |

**Note:** For cameras without Bluetooth, consider using gphoto2 with USB instead.

## Printer Compatibility

### Confirmed Compatible

| Printer | Interface | Tested | Notes |
|---------|-----------|--------|-------|
| Snapmaker U1 | USB Serial | ✅ Yes | Klipper firmware |
| Creality CR10-SE | USB Serial | ⚠️ Should work | Klipper/Clipper |

### Should Work

Any 3D printer with:
- ✅ Klipper firmware
- ✅ USB serial connection
- ✅ G-code layer comments from slicer

**Popular Compatible Printers:**
- Voron 2.4, Trident, 0.1
- Creality Ender 3/5 (with Klipper)
- Prusa i3 (with Klipper)
- Artillery Sidewinder/Genius
- Anycubic Kobra (with Klipper)

### Not Compatible

- Printers without USB serial output
- Printers using proprietary protocols
- Printers with encrypted G-code

## Total Cost Estimate

### Minimum Setup (DIY)
- ESP32-C3: $4
- USB cables: $6
- Jumper wires: $2
**Total: ~$12**

### Recommended Setup
- ESP32-C3: $7
- USB cables (quality): $10
- Button + LED + resistor: $1
- Breadboard: $3
- Project box: $5
**Total: ~$26**

### Premium Setup
- ESP32-C3 (official): $10
- Premium USB cables: $15
- 3D printed enclosure: $2 (filament)
- Soldered connections: $5 (supplies)
**Total: ~$32**

## Alternatives

### Using What You Have

**Don't have ESP32-C3?**
- ✅ ESP32 (original) will work with minor code changes
- ✅ ESP32-S3 will work
- ❌ ESP8266 won't work (no BLE support)

**Don't have buttons/LEDs?**
- ✅ Can use software-only (web interface)
- ✅ Monitor via serial output

**Don't have 3D printer for enclosure?**
- ✅ Use cardboard box
- ✅ Buy generic project box ($5-10)
- ✅ Use as-is (exposed PCB)

## Long-term Costs

### Consumables

**Camera:**
- Battery replacement: $40-60 every few years
- Or use AC adapter: $15-30

**ESP32:**
- Very long lifespan (10+ years typical)
- No consumables

### Upgrades

**Optional Improvements:**
- Better enclosure design
- Multiple cameras
- Improved power supply
- Backup ESP32 (recommended: $7)

## Budget Breakdown

### Starter Budget: $15
- Minimum components only
- Use existing cables if possible
- No enclosure
- No optional features

### Hobbyist Budget: $30
- Quality components
- Basic enclosure
- Optional button/LED
- Spare parts

### Enthusiast Budget: $50+
- Premium components
- Custom 3D printed enclosure
- Multiple cameras
- Backup hardware
- Nice-to-have features

## Bulk Pricing (Multiple Units)

If building several units (workshop, makerspaces):

| Quantity | Cost per Unit | Total |
|----------|---------------|-------|
| 1 | $25 | $25 |
| 5 | $18 | $90 |
| 10 | $15 | $150 |
| 20 | $12 | $240 |

*Based on AliExpress bulk pricing and shared shipping*

## Supplier Links

### USA
- **Adafruit:** https://www.adafruit.com/
- **SparkFun:** https://www.sparkfun.com/
- **Mouser:** https://www.mouser.com/
- **Digikey:** https://www.digikey.com/

### Worldwide
- **AliExpress:** https://www.aliexpress.com/
- **Banggood:** https://www.banggood.com/
- **Amazon:** https://www.amazon.com/

### Europe
- **Pimoroni:** https://www.pimoroni.com/
- **Reichelt:** https://www.reichelt.com/
- **TME:** https://www.tme.eu/

---

**Note:** Prices are estimates as of 2026 and may vary by region and supplier.
