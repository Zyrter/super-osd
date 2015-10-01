# Goals #
  * A basic entry level OSD module.
  * Small in size (target met: 62mm (l) x 42mm (h).
  * Price target $71 to $90 for first versions. Plans to drop the price later.
  * Support for games and virtual challenges. Future support for radio add-on.
  * Basic datalogging capability (a 128KB EEPROM, 112KB rolling log datalogging plus 16KB misc. memory.)

# Preview of current design #

![http://super-osd.googlecode.com/hg/hardware/V3%20Lite/pcb-v3-lite.small.png](http://super-osd.googlecode.com/hg/hardware/V3%20Lite/pcb-v3-lite.small.png)

# Design files #

See here for design files: http://code.google.com/p/super-osd/source/browse/#hg/hardware/V3%20Lite

# Connector #

Several connectors are used around the board. Connectors are placed near the parts they interface to, in an effort to reduce trace length and to make the board smaller.

![http://super-osd.googlecode.com/hg/hardware/V3%20Lite/pcb-connectors.png](http://super-osd.googlecode.com/hg/hardware/V3%20Lite/pcb-connectors.png)

# Typical Parameters #

| **Parameter** | **Conditions** | **Min** | **Typ** | **Max** | **Units** |
|:--------------|:---------------|:--------|:--------|:--------|:----------|
| Supply voltage |                | 4.75    |         | 20      | V         |
| Regulated 3.3V supply | T<sub>A</sub> = 25°C, I<sub>L</sub> = 100mA | 3.257   | 3.3214  | 3.385   | V         |
| Precision 3V reference| T<sub>A</sub> = 25°C, I<sub>L</sub> = 100mA | 2.97971 | 2.99409 | 3.00847 | V         |
| Regulated supply noise (3.3V line) | T<sub>A</sub> = 25°C, I<sub>L</sub> = 100mA |         | 120     |         | mVp-p     |
| Onboard temperature sensor accuracy |                |         | ±0.5    |         | °C        |

# Absolute Maximum Ratings #

| **Parameter** | **Conditions** | **Min** | **Typ** | **Max** | **Units** |
|:--------------|:---------------|:--------|:--------|:--------|:----------|
| Supply voltage |                | -55     |         | 20      | V         |
| Supply voltage | Transient event, t < 500ms | -60     |         | 24      | V         |
| Operating temperature |                | -40     |         | +85     | °C        |
| Storage temperature |                | -55     |         | +165    | °C        |
| Any analog input |                | -45     |         | +45     | V         |

**Note:** Exceeding any of these ratings may cause permanent damage! The nodule may not operate in any of these conditions.

# I<sup>2</sup>C™ interface #

| **Parameter** | **Conditions** | **Min** | **Typ** | **Max** | **Units** |
|:--------------|:---------------|:--------|:--------|:--------|:----------|
| Clock speed   |                |         | 400     |         | kHz       |
| Maximum data rate |                |         | 50      |         | KB/s      |
| Typical data rate (incl. protocol overhead) |                |         | 25      |         | KB/s      |
| Pull-up resistance (to 3.3V) |                | 3.267   | 3.3     | 3.333   | kΩ        |

I²C is a trademark of Philips/NXP Semiconductors.