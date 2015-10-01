# Typical Parameters #

| **Parameter** | **Conditions** | **Min** | **Typ** | **Max** | **Units** |
|:--------------|:---------------|:--------|:--------|:--------|:----------|
| Supply voltage |                | 5.5     |         | 25      | V         |
| Nominal supply current | T<sub>A</sub> = 25°C, active mode | 60      | 85      | 150     | mA        |
| Nominal supply current | T<sub>A</sub> = 25°C, OSD off | 10      | 15      | 35      | mA        |
| Nominal supply current | T<sub>A</sub> = 25°C, OSD+datalogging off | 8       | 10      | 15      | mA        |
| Regulated 3.3V supply | T<sub>A</sub> = 25°C, I<sub>L</sub> = 100mA | 3.267   | 3.300   | 3.333   | V         |
| Regulated 5.0V supply | T<sub>A</sub> = 25°C, I<sub>L</sub> = 100mA | 4.950   | 5.000   | 5.050   | V         |
| Regulated supply noise (5V line) | T<sub>A</sub> = 25°C, I<sub>L</sub> = 100mA |         | 50      | 80      | mVp-p     |
| Regulated supply noise (3.3V line) | T<sub>A</sub> = 25°C, I<sub>L</sub> = 100mA |         | 20      | 50      | mVp-p     |


# Operating Ranges #
Exceeding any of these parameters may cause erratic operation!

| **Parameter** | **Conditions** | **Min** | **Typ** | **Max** | **Units** |
|:--------------|:---------------|:--------|:--------|:--------|:----------|
| Minimum RAM retention supply voltage<sup>(1)</sup> | T<sub>A</sub> = 25°C | 2.353   |         |         | V         |
| Minimum datalogging supply voltage<sup>(2)</sup> | T<sub>A</sub> = 25°C | 3.253   |         |         | V         |
| Minimum OSD+datalogging supply voltage<sup>(3)</sup> | T<sub>A</sub> = 25°C | 5.375   |         |         | V         |

**Note 1**: This is the minimum voltage that the module can be brought down to before the video and data memory is lost.

**Note 2**: This is the minimum voltage that the module can be brought down to before datalogging stops or becomes unreliable.

**Note 3**: This is the minimum voltage that the module can be brought down to before it stops overlaying graphics on a video signal, or the graphics become unreliable.

# Absolute Maximum Ratings<sup>(4)</sup> #

| **Parameter** | **Conditions** | **Min** | **Typ** | **Max** | **Units** |
|:--------------|:---------------|:--------|:--------|:--------|:----------|
| Supply voltage |                | -3      |         | 30      | V         |
| Supply voltage | Transient event, t < 500ms | -20     |         | 60      | V         |
| Operating temperature |                | 0       |         | +70     | °C        |
| Operating temperature (OSD off) |                | -15     |         | +85     | °C        |
| Storage temperature |                | -65     |         | +150    | °C        |
| Output current<sup>(5)</sup>: 5V | T<sub>A</sub> = 25°C |         |         | 250     | mA        |
| Output current<sup>(5)</sup>: 3.3V | T<sub>A</sub> = 25°C |         |         | 150     | mA        |
| Output power<sup>(5)</sup>: 5V | T<sub>A</sub> = 25°C |         |         | 1.25    | W         |
| Output power<sup>(5)</sup>: 3.3V | T<sub>A</sub> = 25°C |         |         | 495     | mW        |
| Combined power<sup>(5)</sup>: 3.3V & 5V | T<sub>A</sub> = 25°C |         |         | 1.25    | W         |

**Note 4**: Exceeding any of these parameters may cause damage to the module.

**Note 5**: Overcurrent and overtemperature protection on all regulators.

# I<sup>2</sup>C interface #

| **Parameter** | **Conditions** | **Min** | **Typ** | **Max** | **Units** |
|:--------------|:---------------|:--------|:--------|:--------|:----------|
| Clock speed   |                |         | 400     |         | kHz       |
| Maximum data rate |                |         | 50      |         | KB/s      |