# Introduction #

In the OSD graphics core, you can find this code in the draw horizontal lines routine (as of revision 86cc02d54e):

```
            and     W0, #15, W5
            and     W1, #15, W6
            add     W6, #1, W6
            ; Compute first mask.
            mov     #1, W7
            sl      W7, W5, W7
            sub     W7, #1, W7
            ; Compute second mask.
            mov     #1, W8
            sl      W8, W6, W8
            sub     W8, #1, W8
            ; XOR the masks together to get the final, super-mask (W8).
            xor     W8, W7, W8
            ; Call the word writer. The word writer will set or clear
            ; appropriately and allows for future expansion e.g. toggling bits.
            mov     W4, W5
            call    dhvwrite        ; dhwrite always uses W8 for the word and W5 for the addr
```

This code comes after the case determination routine, and is a very clever algorithm for drawing a horizontal line of up to 16 pixels from any two points in the same word. This is used extensively for the interface.

# How it works #

First of all, we must remember the assignments of the W array:

**W0** = x0 coordinate

**W1** = x1 coordinate

**W2** = y coordinate (not used)

**W3** = fill mode (0, 1 or 2)

**W4** = addr

**W5** = same as addr, later clobbered as bit #A

**W6** = bit #B

**W7** = temp store #1

**W8** = temp store #2

For the next few examples assume the word position is irrelevant. We want to 'draw' a line from bit #12 to bit #6. Remember the dsPIC is little endian, like the x86 processor in many desktop computers, but unlike the AVR series, which is big endian.

To solve this problem we could consider XORing two masks together:

**Mask 1:**
```
FEDCBA9876543210
----------------
0001111111111111
```

**Mask 2:**
```
FEDCBA9876543210
----------------
0000000000111111
```

**XOR result:**
```
FEDCBA9876543210
----------------
0001111111000000
```

The challenge of this is to generate the two masks.

The dsPIC processors do not have an opcode to generate a string one of ones (some other more advanced processors do; the dsPIC also has an arithmetic shift right, which when loaded with $8000h would do this.) Since we do not have this function, we instead notice that one minus a power of two is always a string of ones. And a power of two can be easily created using a left shift. So, generating the masks goes like this; for bit #12:

**Initial number:**
```
FEDCBA9876543210
----------------
0000000000000001
```

**Shifted left 12+1 times (left mask):**
```
FEDCBA9876543210
----------------
0010000000000000
```

**Subtract one:**
```
FEDCBA9876543210
----------------
0001111111111111
```

This is repeated for the second mask, and the two masks are XOR'd together. The masks are then NAND'd, OR'd or XOR'd with the word to produce the appropriate drawing. Note shifting needs to be done one more than the pixel position for the first mask only.

# Implemented in pseudo-C #
```
int LeftBit, RightBit, LeftMask, RightMask, FinalMask;
LeftBit = x0 & 15;
RightBit = (x1 & 15) + 1; // note +1 for this only
LeftMask = (1 << LeftBit) - 1;
RightMask = (1 << RightBit) - 1;
FinalMask = LeftMask ^ RightMask;
LogicalOpOnWord(LeftAddr, FinalMask, DrawMode);
```

# Cycles #
For the short algorithm, 11 cycles. Note this is independent of the number of pixels which need to be set, and doesn't include setup or write time. Overall however, the time is usually less than 90 cycles to draw any short horizontal lines, and plans exist to optimise this even further.

# More advanced cases #
Not all lines are short. For lines which extend further than 16 pixels, the edges are drawn in a similar manner, and the middle is NAND'd, OR'd or XOR'd with $FFFFh repeatedly.

# Bugs #
A rare bug sometimes occurs with the horizontal line drawing which causes it to be off-by-one. I am still investigating this, but it only effects lines crossing two words.