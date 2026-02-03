; =====================================================
; ESP32 Camera Controller - Layer Change G-code
; =====================================================
; Copy this into your slicer's "Layer Change G-code" section
; 
; BASIC (Recommended for most users):
;LAYER_CHANGE
;
; ADVANCED (With Z-lift for better photos):
;AFTER_LAYER_CHANGE
;[layer_z]
SET_PRINT_STATS_INFO TOTAL_LAYER={total_layer_count}
SET_PRINT_STATS_INFO CURRENT_LAYER={layer_num+1}

SAVE_GCODE_STATE NAME=TIMELAPSE
M400
G91
G1 Z5 F1800
G90
G1 X30 Y270 F10000
M400
M118 LAYER_PHOTO
RESTORE_GCODE_STATE NAME=TIMELAPSE

; =====================================================
; USAGE:
; 1. Copy the BASIC version (line starting with ;LAYER_CHANGE)
; 2. Paste into your slicer's Layer Change G-code section
; 3. See docs/GCODE_CONFIG.md for slicer-specific instructions
; =====================================================