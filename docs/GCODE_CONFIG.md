# G-code Configuration Guide for Layer Change Triggering

This guide shows how to add layer change commands to your 3D printer slicer, so the ESP32 Camera Controller can automatically trigger photos.

## Quick Reference

| Slicer | Menu | Setting | Command |
|--------|------|---------|---------|
| **PrusaSlicer** | Printer Settings → Custom G-code | Layer Change G-code | `;LAYER_CHANGE` |
| **Cura** | Printer → Manage Printers → Custom G-code | Between Layers | `;LAYER_CHANGE` |
| **OrcaSlicer** | Printer Settings → Machine G-code | Layer Change | `;LAYER_CHANGE` |
| **Simplify3D** | Machine Control → Custom Scripts | Layer Change Script | `;LAYER_CHANGE` |
| **BambuStudio** | Printer → Printer Settings → Machine Scripts | Layer Change | `;LAYER_CHANGE` |

---

## Detailed Setup by Slicer

### PrusaSlicer / SuperSlicer

1. Open **Printer Settings**
2. Click the **Custom G-code** tab
3. Find the **Layer Change G-code** section
4. Add this line:
   ```gcode
   ;LAYER_CHANGE
   ```
5. **Save** and export profile
6. Set as default printer

**Optional: Add Z-height tracking**
```gcode
;LAYER_CHANGE
; Z Height: [current_layer_z]
```

### Cura

1. Go to **Printer → Manage Printers**
2. Select your printer, click **Machine Settings**
3. Find **Custom G-code** tab
4. In **Between Layers**, add:
   ```gcode
   ;LAYER_CHANGE
   ```
5. Click **Close**
6. Re-slice your model

**Note:** Cura also shows this in Preview → Features. Layer change will appear as small colored markers.

### OrcaSlicer

1. Open **Printer Settings**
2. Go to **Machine G-code** section
3. Find **Layer Change** field
4. Add:
   ```gcode
   ;LAYER_CHANGE
   ```
5. **Save** and reload model

**Pro tip:** OrcaSlicer has real-time preview - you'll see layer changes marked on the preview.

### Simplify3D

1. Go to **Machine Control → Custom Scripts**
2. Find **Layer Change Script**
3. Add:
   ```gcode
   ;LAYER_CHANGE
   ```
4. **Save printer profile**
5. Export and re-slice

### BambuStudio

1. Open **Printer Settings**
2. Go to **Machine Scripts** section
3. Find **Layer Change**
4. Enter:
   ```gcode
   ;LAYER_CHANGE
   ```
5. **Save** printer settings

---

## Advanced Configuration

### Multiple Slicer Patterns (Already Supported)

The ESP32 automatically recognizes these patterns:
```gcode
;LAYER_CHANGE
;BEFORE_LAYER_CHANGE
;LAYER:
; layer
;Layer:
; Layer 
;layer 
;LAYER_END
;LAYER_START
; layer_z
```

**You only need to add ONE** of these commands in your slicer.

### Custom Trigger with Height Info

Some slicers support variable substitution. For debugging/logging:

**PrusaSlicer:**
```gcode
;LAYER_CHANGE [layer_num]
```

**Cura:**
```gcode
;LAYER_CHANGE
;info: {layer_number}
```

### Conditional Triggering (Advanced)

To trigger only on specific layers, add logic in slicer custom G-code:

**Example - Skip first 3 layers:**
```gcode
;LAYER_CHANGE
; (This will be processed on every layer)
; (ESP32 applies additional filtering if needed)
```

Then configure in ESP32 web interface:
- Set `start_layer` = 4
- Set `end_layer` = (your max layer)

---

## Verification

After adding layer change commands:

### 1. Check G-code File

**In PrusaSlicer:**
- Export G-code
- Open in text editor (Notepad)
- Search for `;LAYER_CHANGE`
- Should find multiple occurrences (one per layer)

**Example:**
```gcode
G92 E0
;LAYER_CHANGE
;TYPE:External perimeter
G1 X10 Y10 F3000
```

### 2. Test with Dry Run

1. Load the G-code into Klipper's web interface (Fluidd/Mainsail)
2. Click **Dry Run** or **Simulate**
3. Watch for `;LAYER_CHANGE` notifications
4. ESP32 should log each trigger

### 3. Monitor via Serial

```bash
# On ESP32 host, watch logs:
pio device monitor

# You should see:
# [GCode] Layer change detected!
# [Camera] Taking photo...
# [Camera] ✓ Photo captured
```

---

## Troubleshooting

### Layer changes not detected

**Problem:** G-code has comments but no layer changes appear in logs

**Solution:**
1. Verify `;LAYER_CHANGE` exists in G-code file
2. Check ESP32 config recognizes the pattern:
   ```bash
   curl http://192.168.4.1/api/config | grep layer_patterns
   ```
3. Verify G-code is being parsed:
   ```bash
   pio device monitor
   # Look for: [Serial] Received: `;LAYER_CHANGE`
   ```

### Too many or too few photos

**Problem:** Getting photos at every line, or missing some layers

**Solution:**
1. Check slicer is configured correctly (see above steps)
2. Verify in G-code export - should have ONE `;LAYER_CHANGE` per layer
3. In ESP32 config, check `require_stabilization: true`
4. Increase `stabilization_delay_ms` if camera is slow

### Photos starting mid-layer

**Problem:** Camera triggering at wrong time, exposing partial layer

**Solution:**
1. Increase `stabilization_delay_ms` in config (default: 2000ms)
2. Try 3000-5000ms for slower cameras
3. Ensure `;LAYER_CHANGE` is at START of layer (not end)

---

## Profile Templates

### PrusaSlicer Profile (copy & paste)

Edit your printer profile and add to Custom G-code section:

```gcode
; ========== Layer Change Trigger ==========
;LAYER_CHANGE
; ==========================================
```

### Cura Machine Profile

Add to `machine_extruder_start_code`:
```gcode
;LAYER_CHANGE
```

---

## FAQ

**Q: Will this affect print quality?**  
A: No - comments (lines starting with `;`) are completely ignored by printers. They're metadata only.

**Q: Can I use different trigger words?**  
A: Yes! ESP32 config already supports many patterns. You can also add custom patterns by editing config.json if needed.

**Q: Do I need to add this to every print?**  
A: No - once configured in your slicer profile, all future exports will include it automatically.

**Q: What if my slicer doesn't have this option?**  
A: Check the slicer's documentation for "Custom G-code" or "Post-processing". If unavailable, you can edit G-code files manually before printing.

---

## Next Steps

1. ✓ Add `;LAYER_CHANGE` to your slicer
2. ✓ Export a test G-code file  
3. ✓ Verify the command appears in G-code
4. ✓ Load firmware to ESP32
5. ✓ Pair Canon camera
6. Start printing and enjoy automatic timelapses!

See [CAMERA_PAIRING.md](CAMERA_PAIRING.md) for camera setup.
