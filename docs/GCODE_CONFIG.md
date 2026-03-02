# OrcaSlicer / Snapmaker Orca G-code Configuration

This guide is intentionally focused on **OrcaSlicer** and **Snapmaker Orca**.
Use it to configure layer-change markers and optional parking behavior for cleaner timelapse shots.

## Quick Reference

| Slicer | Menu | Setting | Command |
|--------|------|---------|---------|
| **OrcaSlicer / Snapmaker Orca** | Printer Settings → Machine G-code | Layer Change | `;LAYER_CHANGE` |

## Video Examples

- **Change Filament G-code example**
   - https://youtube.com/shorts/6lNgAiDCXic?si=o9gQ-PDak_JbY2GQ
- **After Layer Change + Toolhead Parking example**
   - https://youtube.com/shorts/KR0TekyOlNA?si=ugcYNq1vX5-YFizH

These are practical references for workflow behavior when tuning layer-change triggers and parking timing.

---

## OrcaSlicer / Snapmaker Orca Setup

1. Open **Printer Settings**
2. Go to **Machine G-code**
3. Find **Layer Change**
4. Add:
   ```gcode
   ;LAYER_CHANGE
   ```
5. Save the profile
6. Re-slice and export G-code

### Optional: Toolhead Parking Before Trigger

If you want cleaner frames, park the toolhead before the marker:

```gcode
G91
G1 Z2.0 F1200
G90
G1 X5 Y5 F9000
;LAYER_CHANGE
```

Adjust coordinates and speeds for your machine.

---

## Verification

### 1. Check exported G-code

- Open exported `.gcode`
- Search for `;LAYER_CHANGE`
- Confirm one marker per intended layer

### 2. Check monitor logs on host

```bash
sudo journalctl -u timelapse_monitor -f
```

You should see trigger events when markers are reached.

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
1. Check Orca/Snapmaker Orca profile is configured correctly (see above steps)
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

## Orca Template Snippet

Use this in Orca/Snapmaker Orca Layer Change field:

```gcode
;LAYER_CHANGE
```

## Next Steps

1. Add `;LAYER_CHANGE` in Orca/Snapmaker Orca
2. Export and verify marker placement in G-code
3. Pair camera and run a short test print

See [CAMERA_PAIRING.md](CAMERA_PAIRING.md) for pairing details.
