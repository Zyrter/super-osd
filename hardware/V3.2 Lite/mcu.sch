v 20100214 2
T 80600 50300 9 20 1 0 0 0 1
Super OSD Lite - MCU side
T 80200 49800 9 10 1 0 0 0 1
osd.sch
T 80500 49500 9 10 1 0 0 0 1
3
T 82200 49500 9 10 1 0 0 0 1
4
T 84100 49800 9 10 1 0 0 0 1
3.2
T 84100 49500 9 10 1 0 0 0 1
Tom Oldbury
C 54300 49200 0 0 0 title-bordered-A1.sym
T 78300 69600 9 18 1 0 0 0 7
Unless otherwise noted:
  - All resistors SMD metal film, 1/16W, 5%, 0603
  - All capacitors SMD ceramic, >10V, 10%, 0603, X5R/C0G

Unit of capacitance is FARAD
Unit of resistance is OHM
Unit of inductance is HENRY
C 81000 53800 1 90 0 resistor-2.sym
{
T 80650 54200 5 10 0 0 90 0 1
device=RESISTOR
T 81100 54300 5 10 1 1 0 0 1
refdes=R16
T 81100 54100 5 10 1 1 0 0 1
value=1k
T 81000 53800 5 10 0 0 0 0 1
footprint=0603
}
N 80900 54700 80900 54900 4
C 82200 53800 1 0 0 generic-power.sym
{
T 82400 54050 5 10 1 1 0 3 1
netname=+2.5Vref
T 82200 53800 5 10 0 1 0 0 1
net=2.5Vref_1:1
}
N 80700 53600 81300 53600 4
N 80900 53600 80900 53800 4
N 82400 53600 82400 53800 4
C 80700 54900 1 0 0 generic-power.sym
{
T 80900 55150 5 10 1 1 0 3 1
netname=+3.3V
T 80700 54900 5 10 0 1 0 0 1
net=3V3_1:1
}
C 80800 52300 1 0 0 gnd-1.sym
N 80900 52600 80900 52800 4
N 80900 52800 80700 52800 4
C 79100 52600 1 0 0 LM4040-1.sym
{
T 79395 54100 5 10 1 1 0 0 1
refdes=U6
T 79095 52600 5 10 0 1 0 0 1
device=SUPER_ZENER
T 79100 52600 5 10 0 0 0 0 1
footprint=SOT23
}
C 64500 56300 1 0 0 PIC24FJ64GA004-TQFP44-1.sym
{
T 64495 56295 5 10 0 1 0 0 1
device=MICROCONTROLLER
T 64500 56300 5 10 0 0 0 0 1
footprint=TQFP44_10
T 73600 65000 5 10 1 1 0 0 1
refdes=U7
}
C 69000 68000 1 0 0 generic-power.sym
{
T 69200 68250 5 10 1 1 0 3 1
netname=+3.3V
T 69000 68000 5 10 0 1 0 0 1
net=3V3_1:1
}
C 70800 67900 1 90 1 gnd-1.sym
N 70500 67800 70300 67800 4
N 69400 67800 69200 67800 4
C 69400 68000 1 180 1 capacitor-1.sym
{
T 69600 67300 5 10 0 0 180 6 1
device=CAPACITOR
T 69600 68500 5 10 1 1 0 2 1
refdes=C18
T 69600 67100 5 10 0 0 180 6 1
symversion=0.1
T 69600 68300 5 10 1 1 0 2 1
value=100n
T 69400 68000 5 10 0 1 270 2 1
footprint=0603
}
N 69200 68000 69200 65200 4
C 69400 65700 1 180 1 gnd-1.sym
N 69500 65400 69500 65200 4
C 60500 60200 1 0 0 capacitor-1.sym
{
T 60700 60900 5 10 0 0 0 0 1
device=CAPACITOR
T 60600 60900 5 10 1 1 0 0 1
refdes=C19
T 60700 61100 5 10 0 0 0 0 1
symversion=0.1
T 60600 60700 5 10 1 1 0 0 1
value=10u 6.3V
T 60500 60200 5 10 0 1 90 6 1
footprint=0603
}
N 61400 60400 64500 60400 4
C 60000 60500 1 270 0 gnd-1.sym
N 60300 60400 60500 60400 4
C 64000 60800 1 270 0 gnd-1.sym
N 64300 60700 64500 60700 4
C 71700 54100 1 90 1 connector5-2.sym
{
T 69200 53400 5 10 1 1 270 8 1
refdes=CONN5
T 69250 53800 5 10 0 0 270 2 1
device=CONNECTOR_5
T 69050 53800 5 10 0 0 270 2 1
footprint=JUMPER5
}
N 69700 54100 69700 55800 4
N 69700 55800 69800 55800 4
N 69800 55800 69800 56300 4
N 70900 54100 70900 55800 4
N 70900 55800 70700 55800 4
N 70700 55800 70700 56300 4
N 71300 54100 71300 56000 4
N 71300 56000 71000 56000 4
N 71000 56000 71000 56300 4
C 70300 55200 1 270 0 generic-power.sym
{
T 70550 55000 5 10 1 1 270 3 1
netname=+2.5Vref
T 70300 55200 5 10 0 1 270 0 1
net=2.5Vref_1:1
}
N 70100 55000 70100 56300 4
C 70300 55800 1 0 0 gnd-1.sym
N 70400 56100 70400 56300 4
C 69900 54300 1 0 0 generic-power.sym
{
T 70100 54550 5 10 1 1 0 3 1
netname=+3.3V
T 69900 54300 5 10 0 1 0 0 1
net=3V3_1:1
}
N 70100 54300 70100 54100 4
C 70600 54600 1 180 0 gnd-1.sym
N 70500 54300 70500 54100 4
C 80600 61600 1 0 0 crystal-1.sym
{
T 80800 62100 5 10 0 0 0 0 1
device=CRYSTAL
T 80500 62100 5 10 1 1 0 0 1
refdes=X1
T 80800 62300 5 10 0 0 0 0 1
symversion=0.1
T 80500 61900 5 10 1 1 0 0 1
value=7.3728 MHz
T 80600 61600 5 10 0 0 0 0 1
footprint=HC49
}
N 80600 61700 74100 61700 4
N 74100 61400 81500 61400 4
N 81500 61200 81500 61700 4
N 81500 61700 81300 61700 4
C 80600 61200 1 90 1 capacitor-1.sym
{
T 79900 61000 5 10 0 0 90 6 1
device=CAPACITOR
T 80700 60800 5 10 1 1 180 8 1
refdes=C20
T 79700 61000 5 10 0 0 90 6 1
symversion=0.1
T 80700 60600 5 10 1 1 180 8 1
value=18p
T 80600 61200 5 10 0 1 180 2 1
footprint=0603
}
C 81700 61200 1 90 1 capacitor-1.sym
{
T 81000 61000 5 10 0 0 90 6 1
device=CAPACITOR
T 81800 60800 5 10 1 1 180 8 1
refdes=C21
T 80800 61000 5 10 0 0 90 6 1
symversion=0.1
T 81800 60600 5 10 1 1 180 8 1
value=18p
T 81700 61200 5 10 0 1 180 2 1
footprint=0603
}
N 80400 61200 80400 61700 4
C 80300 59800 1 0 0 gnd-1.sym
N 80400 60100 80400 60300 4
C 81400 59800 1 0 0 gnd-1.sym
N 81500 60100 81500 60300 4
C 79400 61000 1 270 0 generic-power.sym
{
T 79650 60800 5 10 1 1 270 3 1
netname=+3.3V
T 79400 61000 5 10 0 1 270 0 1
net=3V3_1:1
}
C 79300 59200 1 0 1 gnd-1.sym
N 79200 59500 79200 59700 4
N 79200 60600 79200 60800 4
C 79400 60600 1 90 1 capacitor-1.sym
{
T 78700 60400 5 10 0 0 90 6 1
device=CAPACITOR
T 79900 60400 5 10 1 1 270 2 1
refdes=C22
T 78500 60400 5 10 0 0 90 6 1
symversion=0.1
T 79700 60400 5 10 1 1 270 2 1
value=100n
T 79400 60600 5 10 0 1 180 2 1
footprint=0603
}
N 79400 60800 74100 60800 4
N 74100 60200 76700 60200 4
N 76300 57300 76300 60200 4
C 76500 58200 1 0 0 resistor-2.sym
{
T 76900 58550 5 10 0 0 0 0 1
device=RESISTOR
T 76500 58700 5 10 1 1 0 0 1
refdes=R17
T 76500 58500 5 10 1 1 0 0 1
value=150k 0.1%
T 76500 58200 5 10 0 0 0 0 1
footprint=0603
}
N 77400 58300 80000 58300 4
C 76400 56400 1 90 0 resistor-2.sym
{
T 76050 56800 5 10 0 0 90 0 1
device=RESISTOR
T 75900 56600 5 10 1 1 90 0 1
refdes=R18
T 76100 56600 5 10 1 1 90 0 1
value=10k 0.1%
T 76400 56400 5 10 0 0 0 0 1
footprint=0603
}
C 77500 57800 1 0 0 resistor-2.sym
{
T 77900 58150 5 10 0 0 0 0 1
device=RESISTOR
T 77500 58300 5 10 1 1 0 0 1
refdes=R19
T 77500 58100 5 10 1 1 0 0 1
value=150k 0.1%
T 77500 57800 5 10 0 0 0 0 1
footprint=0603
}
N 78400 57900 80000 57900 4
C 78500 57400 1 0 0 resistor-2.sym
{
T 78900 57750 5 10 0 0 0 0 1
device=RESISTOR
T 78500 57900 5 10 1 1 0 0 1
refdes=R20
T 78500 57700 5 10 1 1 0 0 1
value=150k 0.1%
T 78500 57400 5 10 0 0 0 0 1
footprint=0603
}
N 79400 57500 80000 57500 4
C 77400 56400 1 90 0 resistor-2.sym
{
T 77050 56800 5 10 0 0 90 0 1
device=RESISTOR
T 76900 56600 5 10 1 1 90 0 1
refdes=R21
T 77100 56600 5 10 1 1 90 0 1
value=10k 0.1%
T 77400 56400 5 10 0 0 0 0 1
footprint=0603
}
N 76500 58300 76300 58300 4
N 76000 57900 77500 57900 4
N 77300 57900 77300 57300 4
C 78400 56400 1 90 0 resistor-2.sym
{
T 78050 56800 5 10 0 0 90 0 1
device=RESISTOR
T 77900 56600 5 10 1 1 90 0 1
refdes=R22
T 78100 56600 5 10 1 1 90 0 1
value=10k 0.1%
T 78400 56400 5 10 0 0 0 0 1
footprint=0603
}
N 75700 57500 78500 57500 4
N 78300 57500 78300 57300 4
C 76200 55900 1 0 0 gnd-1.sym
N 76300 56200 76300 56400 4
C 77200 55900 1 0 0 gnd-1.sym
N 77300 56200 77300 56400 4
C 78200 55900 1 0 0 gnd-1.sym
N 78300 56200 78300 56400 4
N 76000 57900 76000 59900 4
N 76000 59900 74100 59900 4
N 74100 59600 75700 59600 4
N 75700 55800 75700 59600 4
C 80000 57100 1 0 0 connector3-2.sym
{
T 80700 58800 5 10 1 1 0 6 1
refdes=CONN6
T 80300 58750 5 10 0 0 0 0 1
device=CONNECTOR_3
T 80300 58950 5 10 0 0 0 0 1
footprint=JUMPER3
}
C 76400 51600 1 0 0 connector3-2.sym
{
T 77100 53300 5 10 1 1 0 6 1
refdes=CONN7
T 76700 53250 5 10 0 0 0 0 1
device=CONNECTOR_3
T 76700 53450 5 10 0 0 0 0 1
footprint=JUMPER3
}
T 77300 52100 9 10 1 0 0 0 4
maximum 40V
reads up to 2.5V

accuracy ±0.2%
C 75300 52700 1 0 0 resistor-2.sym
{
T 75700 53050 5 10 0 0 0 0 1
device=RESISTOR
T 75400 53000 5 10 1 1 0 0 1
refdes=R23
T 75800 53000 5 10 1 1 0 0 1
value=10k
T 75300 52700 5 10 0 0 0 0 1
footprint=0603
}
N 76200 52800 76400 52800 4
C 75300 51900 1 0 0 resistor-2.sym
{
T 75700 52250 5 10 0 0 0 0 1
device=RESISTOR
T 75400 52200 5 10 1 1 0 0 1
refdes=R24
T 75800 52200 5 10 1 1 0 0 1
value=10k
T 75300 51900 5 10 0 0 0 0 1
footprint=0603
}
N 76200 52000 76400 52000 4
C 73900 52500 1 0 0 resistor-2.sym
{
T 74300 52850 5 10 0 0 0 0 1
device=RESISTOR
T 74000 52800 5 10 1 1 0 0 1
refdes=R25
T 74400 52800 5 10 1 1 0 0 1
value=10k
T 73900 52500 5 10 0 0 0 0 1
footprint=0603
}
N 75100 52400 76400 52400 4
N 74800 55200 75100 55200 4
N 75100 52800 75100 59300 4
N 75100 52800 75300 52800 4
N 74800 55800 75700 55800 4
N 74100 59300 75100 59300 4
C 72700 55600 1 270 0 gnd-1.sym
N 73000 55500 73200 55500 4
N 71300 55400 72400 55400 4
N 72400 52600 72400 55400 4
N 71700 52600 73900 52600 4
N 70900 55000 72000 55000 4
N 72000 52000 72000 55000 4
N 71700 52000 75300 52000 4
C 70100 51700 1 0 0 AZ23C-1.sym
{
T 70395 53000 5 10 1 1 0 0 1
refdes=Z3
T 70095 51700 5 10 0 1 0 0 1
device=DUAL_ZENER
T 70400 51500 5 10 1 1 0 0 1
value=3V 425mW
T 70100 51700 5 10 0 0 270 0 1
footprint=SOT23
}
C 73200 54900 1 0 0 AZ23C-1.sym
{
T 73495 56200 5 10 1 1 0 0 1
refdes=Z4
T 73195 54900 5 10 0 1 0 0 1
device=DUAL_ZENER
T 73500 54700 5 10 1 1 0 0 1
value=3V 425mW
T 73200 54900 5 10 0 0 270 0 1
footprint=SOT23
}
C 69600 52400 1 270 0 gnd-1.sym
N 69900 52300 70100 52300 4
C 78300 59300 1 0 1 AZ23C-1.sym
{
T 78005 60600 5 10 1 1 0 6 1
refdes=Z5
T 78305 59300 5 10 0 1 0 6 1
device=DUAL_ZENER
T 78000 59100 5 10 1 1 0 6 1
value=3V 425mW
T 78300 59300 5 10 0 0 270 2 1
footprint=SOT23
}
C 78800 60000 1 90 1 gnd-1.sym
N 78500 59900 78300 59900 4
N 76700 59600 76000 59600 4
N 74800 52600 75100 52600 4
N 75100 52600 75100 52400 4
T 81200 52700 9 10 1 0 0 0 4
Precision voltage reference

-B variant: ±0.2% (production)
-A variant: ±0.1%
C 74600 61200 1 90 1 gnd-1.sym
N 74300 61100 74100 61100 4
C 62900 61200 1 0 0 input-2.sym
{
T 62900 61400 5 10 0 0 0 0 1
net=OSD_TX:1
T 63500 61900 5 10 0 0 0 0 1
device=none
T 63400 61300 5 10 1 1 0 7 1
value=OSD_TX
}
N 64500 61300 64300 61300 4
C 62900 62100 1 0 0 input-2.sym
{
T 62900 62300 5 10 0 0 0 0 1
net=UART_RX:1
T 63500 62800 5 10 0 0 0 0 1
device=none
T 63400 62200 5 10 1 1 0 7 1
value=UART_RX
}
N 64500 62200 64300 62200 4
C 64300 62000 1 180 0 output-2.sym
{
T 63400 61900 5 10 1 1 180 1 1
value=UART_TX
T 63400 61800 5 10 0 0 180 0 1
net=UART_TX:1
T 64100 61300 5 10 0 0 180 0 1
device=none
}
N 64300 61900 64500 61900 4
C 68700 70500 1 90 1 resistor-2.sym
{
T 68350 70100 5 10 0 0 270 2 1
device=RESISTOR
T 68400 70100 5 10 1 1 0 6 1
refdes=R26
T 68400 69900 5 10 1 1 0 6 1
value=1k
T 68700 70500 5 10 0 0 0 0 1
footprint=0603
}
N 68600 69600 68600 65200 4
C 69100 70500 1 270 0 resistor-2.sym
{
T 69450 70100 5 10 0 0 270 0 1
device=RESISTOR
T 69400 70100 5 10 1 1 0 0 1
refdes=R27
T 69400 69900 5 10 1 1 0 0 1
value=1k
T 69100 70500 5 10 0 0 0 0 1
footprint=0603
}
N 68900 65200 68900 68500 4
N 68900 68500 69200 68500 4
N 69200 68500 69200 69600 4
C 68400 70700 1 0 0 generic-power.sym
{
T 68600 70950 5 10 1 1 0 3 1
netname=+3.3V
T 68400 70700 5 10 0 1 0 0 1
net=3V3_1:1
}
N 68600 70700 68600 70500 4
C 69000 70700 1 0 0 generic-power.sym
{
T 69200 70950 5 10 1 1 0 3 1
netname=+3.3V
T 69000 70700 5 10 0 1 0 0 1
net=3V3_1:1
}
N 69200 70700 69200 70500 4
C 74500 65600 1 0 0 crystal-1.sym
{
T 74700 66100 5 10 0 0 0 0 1
device=CRYSTAL
T 74400 66100 5 10 1 1 0 0 1
refdes=X2
T 74700 66300 5 10 0 0 0 0 1
symversion=0.1
T 74400 65900 5 10 1 1 0 0 1
value=32.768kHz
T 74500 65600 5 10 0 0 0 0 1
footprint=RCY100
T 74500 65600 5 10 0 0 0 0 1
specific_model=AB15T-32.768KHZ
}
T 74600 62500 9 10 1 0 0 0 2
Full industrial operating temperature -40°C to +85°C.
RTC only guaranteed accurate within -20°C to +70°C.
N 71000 65200 71000 65700 4
N 71000 65700 74500 65700 4
N 76200 65700 76200 62300 4
N 76200 62300 74100 62300 4
C 74200 64100 1 0 0 gnd-1.sym
N 74300 64400 74300 64600 4
C 74500 65500 1 90 1 capacitor-1.sym
{
T 74600 65100 5 10 1 1 180 8 1
refdes=C23
T 73800 65300 5 10 0 0 90 6 1
device=CAPACITOR
T 73600 65300 5 10 0 0 90 6 1
symversion=0.1
T 74600 64900 5 10 1 1 180 8 1
value=12p
T 74500 65500 5 10 0 1 180 2 1
footprint=0603
}
C 75300 64100 1 0 0 gnd-1.sym
N 75400 64400 75400 64600 4
C 75600 65500 1 90 1 capacitor-1.sym
{
T 75700 65100 5 10 1 1 180 8 1
refdes=C24
T 74900 65300 5 10 0 0 90 6 1
device=CAPACITOR
T 74700 65300 5 10 0 0 90 6 1
symversion=0.1
T 75700 64900 5 10 1 1 180 8 1
value=12p
T 75600 65500 5 10 0 1 180 2 1
footprint=0603
}
N 75200 65700 76200 65700 4
N 75400 65700 75400 65500 4
N 74300 65500 74300 65700 4
C 67900 67200 1 90 0 connector2-2.sym
{
T 66600 68000 5 10 1 1 90 6 1
refdes=CONN8
T 66650 67500 5 10 0 0 90 0 1
device=CONNECTOR_2
T 66450 67500 5 10 0 0 90 0 1
footprint=JUMPER2
}
N 67100 65600 68000 65600 4
N 68000 65600 68000 65200 4
N 67500 65900 68300 65900 4
N 68300 65900 68300 65200 4
T 66700 68000 9 10 1 0 0 0 2
dual RC inputs
±10V max
C 67400 67000 1 270 0 resistor-2.sym
{
T 67750 66600 5 10 0 0 270 0 1
device=RESISTOR
T 67700 66600 5 10 1 1 0 0 1
refdes=R28
T 67700 66400 5 10 1 1 0 0 1
value=10k
T 67400 67000 5 10 0 0 0 0 1
footprint=0603
}
N 67500 67000 67500 67200 4
C 67200 67000 1 90 1 resistor-2.sym
{
T 66850 66600 5 10 0 0 270 2 1
device=RESISTOR
T 66900 66600 5 10 1 1 0 6 1
refdes=R29
T 66900 66400 5 10 1 1 0 6 1
value=10k
T 67200 67000 5 10 0 0 0 0 1
footprint=0603
}
N 67100 67000 67100 67200 4
N 67100 66100 67100 65600 4
N 67500 65900 67500 66100 4
C 61200 59600 1 90 1 led-1.sym
{
T 60600 58800 5 10 0 0 270 2 1
device=LED
T 60500 59200 5 10 1 1 0 6 1
refdes=LED2
T 60400 58800 5 10 0 0 270 2 1
symversion=0.1
T 60500 59000 5 10 1 1 0 6 1
value=GRN 2.8V
T 61200 59600 5 10 0 0 0 6 1
footprint=603
T 61200 59600 5 10 0 0 0 6 1
specific_model=KPG-1608PBC-A
}
C 60900 57600 1 270 1 resistor-2.sym
{
T 61250 58000 5 10 0 0 90 2 1
device=RESISTOR
T 60800 58100 5 10 1 1 0 6 1
refdes=R30
T 60800 57900 5 10 1 1 0 6 1
value=56R
T 60900 57600 5 10 0 0 0 6 1
footprint=0603
}
N 61000 58500 61000 58700 4
C 63300 59600 1 90 1 led-1.sym
{
T 62700 58800 5 10 0 0 270 2 1
device=LED
T 62600 59200 5 10 1 1 0 6 1
refdes=LED3
T 62500 58800 5 10 0 0 270 2 1
symversion=0.1
T 62600 59000 5 10 1 1 0 6 1
value=ORANGE 2.2V
T 63300 59600 5 10 0 0 0 6 1
footprint=603
T 63300 59600 5 10 0 0 0 6 1
specific_model=KPG-1608PBC-A
}
C 63000 57600 1 270 1 resistor-2.sym
{
T 63350 58000 5 10 0 0 90 2 1
device=RESISTOR
T 62900 58100 5 10 1 1 0 6 1
refdes=R31
T 62900 57900 5 10 1 1 0 6 1
value=120R
T 63000 57600 5 10 0 0 0 6 1
footprint=0603
}
N 63100 58500 63100 58700 4
N 63100 59600 63100 59800 4
N 63100 59800 64500 59800 4
N 64500 60100 61000 60100 4
N 61000 60100 61000 59600 4
C 60900 57100 1 0 0 gnd-1.sym
N 61000 57400 61000 57600 4
C 63000 57100 1 0 0 gnd-1.sym
N 63100 57400 63100 57600 4
T 80800 57500 9 10 1 0 0 0 4
maximum 45V
reads up to 40V

accuracy ±0.6%
C 61000 54400 1 0 0 TC1047A-1.sym
{
T 101000 94400 5 10 0 1 0 0 1
device=TEMP_SENSOR
T 101000 94400 5 10 0 1 0 0 1
footprint=SOT23
T 61000 56100 5 10 1 1 0 0 1
refdes=U8
}
C 60400 55700 1 90 1 capacitor-1.sym
{
T 59700 55500 5 10 0 0 90 6 1
device=CAPACITOR
T 60500 55300 5 10 1 1 180 8 1
refdes=C25
T 59500 55500 5 10 0 0 90 6 1
symversion=0.1
T 60500 55100 5 10 1 1 180 8 1
value=100n
T 60400 55700 5 10 0 1 180 2 1
footprint=0603
}
N 60200 55700 60200 56700 4
N 60200 56500 61700 56500 4
N 61700 56500 61700 56300 4
N 60200 54800 60200 54200 4
N 60200 54200 61700 54200 4
N 61700 54000 61700 54400 4
C 67300 54800 1 90 1 generic-power.sym
{
T 67050 54600 5 10 1 1 270 5 1
netname=+3.3V
T 67300 54800 5 10 0 1 270 2 1
net=3V3_1:1
}
C 68500 53000 1 0 0 gnd-1.sym
N 68600 53300 68600 53500 4
N 68600 54400 68600 54600 4
C 68400 54400 1 270 0 capacitor-1.sym
{
T 68300 54000 5 10 1 1 0 6 1
refdes=C34
T 68300 53800 5 10 1 1 0 6 1
value=100n DNP
T 69100 54200 5 10 0 0 90 8 1
device=CAPACITOR
T 69300 54200 5 10 0 0 90 8 1
symversion=0.1
T 68400 54400 5 10 0 1 180 8 1
footprint=0603
}
N 68400 54600 69700 54600 4
C 69100 55800 1 0 0 gnd-1.sym
N 69200 56100 69200 56300 4
C 60400 56700 1 0 1 generic-power.sym
{
T 60200 56950 5 10 1 1 180 5 1
netname=+3.3V
T 60400 56700 5 10 0 1 180 2 1
net=3V3_1:1
}
C 57100 67900 1 0 1 connector4-2.sym
{
T 56300 70000 5 10 1 1 0 0 1
refdes=CONN9
T 56800 69950 5 10 0 0 0 6 1
device=CONNECTOR_4
T 56800 70150 5 10 0 0 0 6 1
footprint=JUMPER4
}
C 58700 68400 1 180 0 input-2.sym
{
T 58700 68200 5 10 0 0 180 0 1
net=UART_TX:1
T 58100 67700 5 10 0 0 180 0 1
device=none
T 58200 68300 5 10 1 1 180 7 1
value=UART_TX
}
N 57100 68300 57300 68300 4
C 57300 68600 1 0 0 output-2.sym
{
T 58200 68700 5 10 1 1 0 1 1
value=UART_RX
T 58200 68800 5 10 0 0 0 0 1
net=UART_RX:1
T 57500 69300 5 10 0 0 0 0 1
device=none
}
N 57300 68700 57100 68700 4
C 60600 69700 1 0 0 generic-power.sym
{
T 60800 69950 5 10 1 1 0 3 1
netname=+3.3V
T 60600 69700 5 10 0 1 0 0 1
net=3V3_1:1
}
C 59600 69400 1 0 0 fuse-2.sym
{
T 59800 69950 5 10 0 0 0 0 1
device=FUSE
T 59500 70100 5 10 1 1 0 0 1
refdes=RF2
T 59800 70150 5 10 0 0 0 0 1
symversion=0.1
T 59500 69900 5 10 1 1 0 0 1
value=350mA 6V
T 59600 69400 5 10 0 0 0 0 1
footprint=0603
T 59500 69700 5 10 1 1 0 0 1
specific_model=0603L035YR
}
N 60800 69700 60800 69500 4
N 60800 69500 60500 69500 4
N 59600 69500 57100 69500 4
C 57600 69200 1 90 1 gnd-1.sym
N 57300 69100 57100 69100 4
C 59600 69300 1 90 1 capacitor-1.sym
{
T 59700 68900 5 10 1 1 0 0 1
refdes=C27
T 59700 68700 5 10 1 1 0 0 1
value=10u 6.3V
T 58900 69100 5 10 0 0 90 6 1
device=CAPACITOR
T 58700 69100 5 10 0 0 90 6 1
symversion=0.1
T 59600 69300 5 10 0 1 180 2 1
footprint=0603
}
C 59500 67900 1 0 1 gnd-1.sym
N 59400 68200 59400 68400 4
N 59400 69300 59400 69500 4
T 56300 70200 9 10 1 0 0 0 1
UART/GPS
C 62100 67900 1 0 1 connector4-2.sym
{
T 61300 70000 5 10 1 1 0 0 1
refdes=CONN10
T 61800 69950 5 10 0 0 0 6 1
device=CONNECTOR_4
T 61800 70150 5 10 0 0 0 6 1
footprint=JUMPER4
}
N 62100 68300 62300 68300 4
C 65600 69700 1 0 0 generic-power.sym
{
T 65800 69950 5 10 1 1 0 3 1
netname=+3.3V
T 65600 69700 5 10 0 1 0 0 1
net=3V3_1:1
}
C 64600 69400 1 0 0 fuse-2.sym
{
T 64800 69950 5 10 0 0 0 0 1
device=FUSE
T 64500 70100 5 10 1 1 0 0 1
refdes=RF3
T 64800 70150 5 10 0 0 0 0 1
symversion=0.1
T 64500 69900 5 10 1 1 0 0 1
value=350mA 6V
T 64600 69400 5 10 0 0 0 0 1
footprint=0603
T 64500 69700 5 10 1 1 0 0 1
specific_model=0603L035YR
}
N 65800 69700 65800 69500 4
N 65800 69500 65500 69500 4
N 64600 69500 62100 69500 4
C 62600 69200 1 90 1 gnd-1.sym
N 62300 69100 62100 69100 4
C 64600 69300 1 90 1 capacitor-1.sym
{
T 64700 68900 5 10 1 1 0 0 1
refdes=C28
T 64700 68700 5 10 1 1 0 0 1
value=10u 6.3V
T 63900 69100 5 10 0 0 90 6 1
device=CAPACITOR
T 63700 69100 5 10 0 0 90 6 1
symversion=0.1
T 64600 69300 5 10 0 1 180 2 1
footprint=0603
}
C 64500 67900 1 0 1 gnd-1.sym
N 64400 68200 64400 68400 4
N 64400 69300 64400 69500 4
T 61300 70200 9 10 1 0 0 0 1
I2C
N 64500 59500 63600 59500 4
N 63600 55300 63600 59500 4
N 63600 55300 62800 55300 4
T 60500 58800 9 10 1 0 0 6 1
STAT
T 62600 58800 9 10 1 0 0 6 1
FAULT/ALERT
C 61600 53700 1 0 0 gnd-1.sym
C 64100 53600 1 90 0 resistor-2.sym
{
T 63750 54000 5 10 0 0 90 0 1
device=RESISTOR
T 63800 54100 5 10 1 1 0 6 1
refdes=R32
T 63800 53900 5 10 1 1 0 6 1
value=10k 0.1%
T 64100 53600 5 10 0 0 0 0 1
footprint=0603
}
N 64000 54500 64000 59200 4
C 64200 54600 1 0 0 resistor-2.sym
{
T 64600 54950 5 10 0 0 0 0 1
device=RESISTOR
T 64300 55100 5 10 1 1 0 0 1
refdes=R33
T 64300 54900 5 10 1 1 0 0 1
value=150k 0.1%
T 64200 54600 5 10 0 0 0 0 1
footprint=0603
}
N 64000 54700 64200 54700 4
N 64500 59200 64000 59200 4
C 66700 54600 1 0 1 input-2.sym
{
T 66700 54800 5 10 0 0 0 6 1
net=BATT:1
T 66100 55300 5 10 0 0 0 6 1
device=none
T 66200 54700 5 10 1 1 0 1 1
value=BATT
}
N 65300 54700 65100 54700 4
C 63900 53100 1 0 0 gnd-1.sym
N 64000 53400 64000 53600 4
C 67800 56200 1 180 0 output-2.sym
{
T 66900 56100 5 10 1 1 180 1 1
value=LED_CH1
T 66900 56000 5 10 0 0 180 0 1
net=LED_CH1:1
T 67600 55500 5 10 0 0 180 0 1
device=none
}
C 67800 55900 1 180 0 output-2.sym
{
T 66900 55800 5 10 1 1 180 1 1
value=LED_CH2
T 66900 55700 5 10 0 0 180 0 1
net=LED_CH2:1
T 67600 55200 5 10 0 0 180 0 1
device=none
}
N 67800 55800 68300 55800 4
N 68300 55800 68300 56300 4
N 67800 56100 68000 56100 4
N 68000 56100 68000 56300 4
C 66400 55100 1 0 0 input-2.sym
{
T 66400 55300 5 10 0 0 0 0 1
net=BUTTONS:1
T 67000 55800 5 10 0 0 0 0 1
device=none
T 66900 55200 5 10 1 1 0 7 1
value=BUTTONS
}
N 67800 55200 68900 55200 4
N 68900 55200 68900 56300 4
T 64400 51900 9 10 1 0 0 0 2
CH1 LEDs: button LEDs
CH2 LEDs: spare channel (for user)
C 72100 68400 1 0 0 AT25DF161-1.sym
{
T 112100 108400 5 10 0 1 0 0 1
device=SERIAL_FLASH
T 112100 108400 5 10 0 1 0 0 1
footprint=SO8
T 72400 70200 5 10 1 1 0 0 1
refdes=U9
}
N 72100 69400 71500 69400 4
N 71500 67100 71500 69400 4
N 71500 67100 69800 67100 4
N 69800 67100 69800 65200 4
N 74300 69000 75200 69000 4
N 75200 66800 75200 69000 4
N 70100 66800 75200 66800 4
N 70100 66800 70100 65200 4
N 70400 65200 70400 66500 4
N 70400 66500 74800 66500 4
N 74800 66500 74800 68600 4
N 74800 68600 74300 68600 4
C 74300 70700 1 0 0 generic-power.sym
{
T 74500 70950 5 10 1 1 0 3 1
netname=+3.3V
T 74300 70700 5 10 0 1 0 0 1
net=3V3_1:1
}
C 76100 69900 1 90 1 gnd-1.sym
N 75800 69800 75600 69800 4
C 74700 70000 1 180 1 capacitor-1.sym
{
T 74900 69300 5 10 0 0 180 6 1
device=CAPACITOR
T 74900 70500 5 10 1 1 0 2 1
refdes=C29
T 74900 69100 5 10 0 0 180 6 1
symversion=0.1
T 74900 70300 5 10 1 1 0 2 1
value=100n
T 74700 70000 5 10 0 1 270 2 1
footprint=0603
}
N 74700 69800 74300 69800 4
N 74500 70700 74500 69800 4
C 71600 68500 1 270 1 gnd-1.sym
N 71900 68600 72100 68600 4
N 72100 69000 71300 69000 4
N 71300 69000 71300 70500 4
N 74500 70500 71300 70500 4
N 74300 69400 74500 69400 4
N 74500 69400 74500 69800 4
C 58000 64500 1 0 0 24xx1025-1.sym
{
T 98000 104500 5 10 0 1 0 0 1
device=SERIAL_EEPROM
T 98000 104500 5 10 0 1 0 0 1
footprint=SO8
T 58300 66300 5 10 1 1 0 0 1
refdes=U10
}
C 68400 69000 1 0 1 output-2.sym
{
T 67500 69200 5 10 0 0 0 6 1
net=SCL:1
T 68200 69700 5 10 0 0 0 6 1
device=none
T 67500 69100 5 10 1 1 0 7 1
value=SCL
}
C 68400 69400 1 0 1 io-1.sym
{
T 67500 69600 5 10 0 0 0 6 1
net=SDA:1
T 68200 70000 5 10 0 0 0 6 1
device=none
T 67500 69500 5 10 1 1 0 7 1
value=SDA
}
C 61800 65000 1 0 1 input-2.sym
{
T 61800 65200 5 10 0 0 0 6 1
net=SCL:1
T 61200 65700 5 10 0 0 0 6 1
device=none
T 61300 65100 5 10 1 1 0 1 1
value=SCL
}
N 68400 69500 69200 69500 4
N 68400 69100 68600 69100 4
N 60400 65100 60200 65100 4
C 60400 64600 1 0 0 io-1.sym
{
T 61300 64800 5 10 0 0 0 0 1
net=SDA:1
T 60600 65200 5 10 0 0 0 0 1
device=none
T 61300 64700 5 10 1 1 0 1 1
value=SDA
}
N 60400 64700 60200 64700 4
C 60200 66100 1 0 0 generic-power.sym
{
T 60400 66350 5 10 1 1 0 3 1
netname=+3.3V
T 60200 66100 5 10 0 1 0 0 1
net=3V3_1:1
}
C 62000 66000 1 90 1 gnd-1.sym
N 61700 65900 61500 65900 4
C 60600 66100 1 180 1 capacitor-1.sym
{
T 60800 65400 5 10 0 0 180 6 1
device=CAPACITOR
T 60800 66600 5 10 1 1 0 2 1
refdes=C30
T 60800 65200 5 10 0 0 180 6 1
symversion=0.1
T 60800 66400 5 10 1 1 0 2 1
value=100n
T 60600 66100 5 10 0 1 270 2 1
footprint=0603
}
N 60600 65900 60200 65900 4
N 60400 66100 60400 65900 4
C 60700 65600 1 90 1 gnd-1.sym
N 60400 65500 60200 65500 4
C 57500 66000 1 270 0 gnd-1.sym
N 57800 65900 58000 65900 4
C 57500 65600 1 270 0 gnd-1.sym
N 57800 65500 58000 65500 4
C 57800 64900 1 90 0 generic-power.sym
{
T 57550 65100 5 10 1 1 90 3 1
netname=+3.3V
T 57800 64900 5 10 0 1 90 0 1
net=3V3_1:1
}
N 57800 65100 58000 65100 4
C 57500 64800 1 270 0 gnd-1.sym
N 57800 64700 58000 64700 4
C 63700 68200 1 0 1 input-2.sym
{
T 63200 68300 5 10 1 1 0 1 1
value=SCL
T 63700 68400 5 10 0 0 0 6 1
net=SCL:1
T 63100 68900 5 10 0 0 0 6 1
device=none
}
T 57900 64000 9 10 1 0 0 0 2
Optional 128KB EEPROM 
(for versions without 2MB flash)
B 57200 63300 4900 3500 3 0 0 0 -1 -1 0 -1 -1 -1 -1 -1
T 72200 68100 9 10 1 0 0 0 1
16MBit / 2MB DataFlash
B 71100 67900 5100 3300 3 0 0 0 -1 -1 0 -1 -1 -1 -1 -1
N 62100 68700 62300 68700 4
C 62300 68600 1 0 0 io-1.sym
{
T 63200 68800 5 10 0 0 0 0 1
net=SDA:1
T 62500 69200 5 10 0 0 0 0 1
device=none
T 63200 68700 5 10 1 1 0 1 1
value=SDA
}
T 57500 63500 9 10 1 0 0 0 2
On development versions, both are present,
and system status is written to the EEPROM.
T 62400 61300 9 10 1 0 0 7 1
From OSD side
L 61900 61500 62100 61700 3 0 0 0 -1 -1
L 62100 61700 62400 61700 3 0 0 0 -1 -1
L 61900 61100 62100 60900 3 0 0 0 -1 -1
L 62100 60900 62400 60900 3 0 0 0 -1 -1
C 62900 60900 1 0 0 input-2.sym
{
T 62900 61100 5 10 0 0 0 0 1
net=OSD_CTS:1
T 63500 61600 5 10 0 0 0 0 1
device=none
T 63400 61000 5 10 1 1 0 7 1
value=OSD_CTS
}
N 64300 61000 64500 61000 4
N 64300 61600 64500 61600 4
C 64300 61700 1 180 0 output-2.sym
{
T 63400 61600 5 10 1 1 180 1 1
value=OSD_RX
T 63400 61500 5 10 0 0 180 0 1
net=OSD_RX:1
T 64100 61000 5 10 0 0 180 0 1
device=none
}
C 71600 69700 1 270 1 gnd-1.sym
N 71900 69800 72100 69800 4
N 67500 54600 67300 54600 4
C 67500 54500 1 0 0 resistor-2.sym
{
T 67900 54850 5 10 0 0 0 0 1
device=RESISTOR
T 67700 55000 5 10 1 1 0 0 1
refdes=R43
T 67700 54800 5 10 1 1 0 0 1
value=1k
T 67500 54500 5 10 0 1 0 0 1
footprint=0603
}
C 81300 53500 1 0 0 resistor-2.sym
{
T 81700 53850 5 10 0 0 0 0 1
device=RESISTOR
T 81500 54000 5 10 1 1 0 0 1
refdes=R44
T 81500 53800 5 10 1 1 0 0 1
value=1k
T 81300 53500 5 10 0 1 0 0 1
footprint=0603
}
N 82400 53600 82200 53600 4
C 69000 54900 1 0 0 resistor-2.sym
{
T 69400 55250 5 10 0 0 0 0 1
device=RESISTOR
T 69200 55400 5 10 1 1 0 0 1
refdes=R45
T 69200 55200 5 10 1 1 0 0 1
value=1M
T 69000 54900 5 10 0 1 0 0 1
footprint=0603
}
N 69900 55000 70300 55000 4
N 69000 55000 68600 55000 4
N 68600 55000 68600 56300 4
T 75800 54900 9 10 1 0 0 0 1
Z4, Z5, Z6: DNP
C 69300 56100 1 180 1 generic-power.sym
{
T 69500 55850 5 10 1 1 0 5 1
netname=+3.3V
T 69300 56100 5 10 0 1 0 2 1
net=3V3_1:1
}
N 69500 56100 69500 56300 4
C 68400 51800 1 270 0 capacitor-1.sym
{
T 68300 51400 5 10 1 1 0 6 1
refdes=C35
T 68300 51200 5 10 1 1 0 6 1
value=100n DNP
T 69100 51600 5 10 0 0 90 8 1
device=CAPACITOR
T 69300 51600 5 10 0 0 90 8 1
symversion=0.1
T 68400 51800 5 10 0 1 180 8 1
footprint=0603
}
C 68800 52000 1 0 1 generic-power.sym
{
T 68600 52250 5 10 1 1 180 5 1
netname=+3.3V
T 68800 52000 5 10 0 1 180 2 1
net=3V3_1:1
}
N 68600 52000 68600 51800 4
C 68500 50400 1 0 0 gnd-1.sym
N 68600 50700 68600 50900 4
T 68900 51300 9 10 1 0 0 0 1
for AVdd