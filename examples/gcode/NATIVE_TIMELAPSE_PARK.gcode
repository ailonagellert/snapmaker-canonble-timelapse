; =====================================================
; Native Timelapse Park Template (Orca / Snapmaker Orca)
; =====================================================
; Purpose:
; - Park the toolhead before native timelapse capture
; - Keep movement predictable for cleaner frames
;
; Where to use:
; - Printer Settings -> Machine G-code -> Layer Change
; - Or your printer's native timelapse custom G-code field
;
; IMPORTANT:
; - Tune X/Y park location for your machine bounds
; - Tune Z-hop and feed rates for your printer
; - Keep this sequence short to avoid adding too much print time

; Save current state
SAVE_GCODE_STATE NAME=NATIVE_TIMELAPSE_PARK

; Wait for planner buffer to empty
M400

; Z-hop to reduce collision risk
G91
G1 Z2.0 F1200
G90

; Park toolhead (update X/Y to your safe corner)
G1 X5 Y5 F9000

; Optional short settle delay before native capture
G4 P250

; Native timelapse marker/event hook (keep if your workflow needs it)
;LAYER_CHANGE

; Restore previous state and continue print
RESTORE_GCODE_STATE NAME=NATIVE_TIMELAPSE_PARK
