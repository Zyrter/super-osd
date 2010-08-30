v 20100214 2
T 58900 55500 9 20 1 0 0 0 1
FPV version - analog inputs
T 57900 55000 9 10 1 0 0 0 1
FPV_version_analog_inputs.sch
T 58400 54700 9 10 1 0 0 0 1
1
T 60100 54700 9 10 1 0 0 0 1
1
T 62100 55000 9 10 1 0 0 0 1
1
T 62100 54700 9 10 1 0 0 0 1
Thomas Oldbury
C 41700 54600 0 0 0 title-A2.sym
N 54500 67300 51500 67300 4
N 55400 67300 57300 67300 4
C 51500 64200 1 180 0 output-2.sym
{
T 50600 64100 5 10 1 1 180 1 1
value=ANALOG5HV
T 50600 64000 5 10 0 0 180 0 1
net=ANALOG5HV:1
T 51300 63500 5 10 0 0 180 0 1
device=none
}
N 54500 64100 51500 64100 4
N 54500 63300 51500 63300 4
T 50000 67700 9 10 1 0 0 0 3
Unscaled ADC inputs 0-3V (rated to handle ±50V)
Input impedence non-overloaded: about 1 Mohm
Input impedence overloaded: about 100 kohm
T 50800 60400 9 10 1 0 0 0 1
Scaled ADC inputs 0-30V (rated to handle ±50V)
N 54500 62500 51500 62500 4
N 55400 64100 57500 64100 4
N 55400 63300 56100 63300 4
N 57500 63700 56100 63700 4
N 56100 63700 56100 63300 4
N 57500 63300 56500 63300 4
N 56500 63300 56500 62500 4
N 56500 62500 55400 62500 4
C 51500 63400 1 180 0 output-2.sym
{
T 50600 63300 5 10 1 1 180 1 1
value=ANALOG6HV
T 50600 63200 5 10 0 0 180 0 1
net=ANALOG6HV:1
T 51300 62700 5 10 0 0 180 0 1
device=none
}
C 51500 62600 1 180 0 output-2.sym
{
T 50600 62500 5 10 1 1 180 1 1
value=ANALOG7HV
T 50600 62400 5 10 0 0 180 0 1
net=ANALOG7HV:1
T 51300 61900 5 10 0 0 180 0 1
device=none
}
C 51500 66600 1 180 0 output-2.sym
{
T 50600 66500 5 10 1 1 180 1 1
value=ANALOG1
T 50600 66400 5 10 0 0 180 0 1
net=ANALOG1:1
T 51300 65900 5 10 0 0 180 0 1
device=none
}
C 51500 67400 1 180 0 output-2.sym
{
T 50600 67300 5 10 1 1 180 1 1
value=ANALOG0
T 50600 67200 5 10 0 0 180 0 1
net=ANALOG0:1
T 51300 66700 5 10 0 0 180 0 1
device=none
}
N 53500 62200 53500 62500 4
N 52700 62200 52700 63300 4
C 51800 60800 1 0 0 gnd-1.sym
C 52600 60800 1 0 0 gnd-1.sym
N 52700 61100 52700 61300 4
C 53400 60800 1 0 0 gnd-1.sym
N 53500 61100 53500 61300 4
C 51500 65800 1 180 0 output-2.sym
{
T 50600 65700 5 10 1 1 180 1 1
value=ANALOG3
T 50600 65600 5 10 0 0 180 0 1
net=ANALOG3:1
T 51300 65100 5 10 0 0 180 0 1
device=none
}
C 51500 65000 1 180 0 output-2.sym
{
T 50600 64900 5 10 1 1 180 1 1
value=ANALOG4
T 50600 64800 5 10 0 0 180 0 1
net=ANALOG4:1
T 51300 64300 5 10 0 0 180 0 1
device=none
}
N 54500 66500 51500 66500 4
N 57500 65300 56900 65300 4
N 56900 65300 56900 66500 4
N 56900 66500 55400 66500 4
N 56500 65700 56500 64900 4
N 57500 64900 56500 64900 4
N 56100 64900 56100 64500 4
N 51500 65700 54500 65700 4
N 51500 64900 54500 64900 4
N 56500 65700 55400 65700 4
N 55400 64900 56100 64900 4
N 51900 61100 51900 61300 4
N 51900 62200 51900 64100 4
N 56100 64500 57500 64500 4
N 57500 65700 57300 65700 4
N 57300 65700 57300 67300 4
C 57500 62900 1 0 0 connector7-2.sym
{
T 58200 66200 5 10 1 1 0 6 1
refdes=CONN1
T 57800 66150 5 10 0 0 0 0 1
device=CONNECTOR_7
T 57800 66350 5 10 0 0 0 0 1
footprint=MTA100_7
}
C 54500 67200 1 0 0 resistor-2.sym
{
T 54900 67550 5 10 0 0 0 0 1
device=RESISTOR
T 54700 67700 5 10 1 1 0 0 1
refdes=R1
T 54700 67500 5 10 1 1 0 0 1
value=100k
T 54500 67200 5 10 0 0 0 0 1
footprint=0603
}
C 54500 66400 1 0 0 resistor-2.sym
{
T 54900 66750 5 10 0 0 0 0 1
device=RESISTOR
T 54700 66900 5 10 1 1 0 0 1
refdes=R2
T 54700 66700 5 10 1 1 0 0 1
value=100k
T 54500 66400 5 10 0 0 0 0 1
footprint=0603
}
C 54500 65600 1 0 0 resistor-2.sym
{
T 54900 65950 5 10 0 0 0 0 1
device=RESISTOR
T 54700 66100 5 10 1 1 0 0 1
refdes=R3
T 54700 65900 5 10 1 1 0 0 1
value=100k
T 54500 65600 5 10 0 0 0 0 1
footprint=0603
}
C 54500 64800 1 0 0 resistor-2.sym
{
T 54900 65150 5 10 0 0 0 0 1
device=RESISTOR
T 54700 65300 5 10 1 1 0 0 1
refdes=R4
T 54700 65100 5 10 1 1 0 0 1
value=100k
T 54500 64800 5 10 0 0 0 0 1
footprint=0603
}
C 54500 64000 1 0 0 resistor-2.sym
{
T 54900 64350 5 10 0 0 0 0 1
device=RESISTOR
T 54700 64500 5 10 1 1 0 0 1
refdes=R5
T 54700 64300 5 10 1 1 0 0 1
value=100k
T 54500 64000 5 10 0 0 0 0 1
footprint=0603
}
C 54500 63200 1 0 0 resistor-2.sym
{
T 54900 63550 5 10 0 0 0 0 1
device=RESISTOR
T 54700 63700 5 10 1 1 0 0 1
refdes=R6
T 54700 63500 5 10 1 1 0 0 1
value=100k
T 54500 63200 5 10 0 0 0 0 1
footprint=0603
}
C 54500 62400 1 0 0 resistor-2.sym
{
T 54900 62750 5 10 0 0 0 0 1
device=RESISTOR
T 54700 62900 5 10 1 1 0 0 1
refdes=R7
T 54700 62700 5 10 1 1 0 0 1
value=100k
T 54500 62400 5 10 0 0 0 0 1
footprint=0603
}
C 53400 62200 1 270 0 resistor-2.sym
{
T 53750 61800 5 10 0 0 270 0 1
device=RESISTOR
T 53900 62000 5 10 1 1 270 0 1
refdes=R8
T 53700 62000 5 10 1 1 270 0 1
value=10k
T 53400 62200 5 10 0 0 270 0 1
footprint=0603
}
C 52600 62200 1 270 0 resistor-2.sym
{
T 52950 61800 5 10 0 0 270 0 1
device=RESISTOR
T 53100 62000 5 10 1 1 270 0 1
refdes=R9
T 52900 62000 5 10 1 1 270 0 1
value=10k
T 52600 62200 5 10 0 0 270 0 1
footprint=0603
}
C 51800 62200 1 270 0 resistor-2.sym
{
T 52150 61800 5 10 0 0 270 0 1
device=RESISTOR
T 52300 62000 5 10 1 1 270 0 1
refdes=R10
T 52100 62000 5 10 1 1 270 0 1
value=10k
T 51800 62200 5 10 0 0 270 0 1
footprint=0603
}
T 49100 66000 9 10 1 0 0 0 1
ANALOG2 is an internal ADC input