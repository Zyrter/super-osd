# element_flags, description, pcb-name, value, mark_x, mark_y,
# text_x, text_y, text_direction, text_scale, text_flags

# TL1240 illuminated tactile switch footprint. 
# Also compatible with most other 6mmx6mm switches without illumination.
# Works in tandem with TL1240-pushbutton-with-led-1.sym.
# Author: Thomas Oldbury
# Use: Unlimited
# Distribution: CC-BY 3.0

# All dimensions in mils!
Element[0x00000000 "TL1240-1" "" "" 0 0 0 0 0 100 0x00]
(
    # Note: All dimensions in 1/100th mil.
    # Mark is positioned in the centre of the footprint; all dimensions relative to this.
    
    # Outer two pins for the LED, each 2.7mm (106.299 mils) from mark.
    # Diameter/drill for pin hole is 0.7mm (27.55 mils), I've added 10 mils 
    # to the thickness and 5 mils to the clearance.
    #
    # The datasheet is unclear on the polarity of the LED - this needs to be 
    # checked - however, the switch may be mounted either way around with the 
    # same functionality, but different polarity of the LED.
    #
    # Pin[x y Thickness Clearance Mask DrillHole Name Number Flags]
    Pin[-10630 0 3755 500 4255 2755 "LedAnode5" "5" 0x00000000]
    Pin[ 10630 0 3755 500 4255 2755 "LedCathode6" "6" 0x00000000]
    
    # Four pins in each corner for the switch contacts. 
    # Xo = 2.25mm (88.58 mils), Yo = 3.25mm (127.95 mils)
    # Diameter/drill for pin hole is 1.0mm (39.37 mils); I've added 10 mils
    # to thickness and 5 mils to clearance, as above.
    Pin[ 8858  12795 4937 500 5437 3937 "1" "1" 0x00000000]
    Pin[ 8858 -12795 4937 500 5437 3937 "2" "2" 0x00000000]
    Pin[-8858  12795 4937 500 5437 3937 "3" "3" 0x00000000]
    Pin[-8858 -12795 4937 500 5437 3937 "4" "4" 0x00000000]
    
    # Dimensions of the switch body a 6mmx6mm square, line 10 mils.
    # ElementLine[x1 y1 x2 y2 Thickness]
    ElementLine[-11811 -11811  11811 -11811 1000] # horizontal line
    ElementLine[-11811  11811  11811  11811 1000] # horizontal line
    ElementLine[-11811 -11811 -11811  11811 1000] # vertical line
    ElementLine[ 11811 -11811  11811  11811 1000] # vertical line
)
