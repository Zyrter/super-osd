; This code handles the output stage of the OSD.
; It is written in assembly for optimal performance.

.macro output_pix
            rlnc    W0, W0
            rlnc    W1, W1
            and     W0, W7, W2
            ior     W2, W8, W2
            mov     W1, PORTB			; set PORT before TRIS - gives cleaner look
            mov     W2, TRISB
            nop
            nop
            nop
.endm

.macro output_pix_last
            rlnc    W0, W0
            rlnc    W1, W1
            and     W0, W7, W2
            ior     W2, W8, W2
            mov     W1, PORTB
            mov     W2, TRISB
.endm

.global	_osd_out

_osd_out:	; Expects the pointer to the set/clear scanline in W0. 
			; Expects the pointer to the black/white scanline in W1.
			; Expects the number of words (16 bits) to be output in W2.
			;
			; These are the order of the C arguments, so its prototype 
			; should be:
			; 
			;   int _osd_output(short *ptr_set_clear, short *ptr_black_white, short num_words); 
			;
			; It expects data to be rotated 5 bits right which simplifies
			; the output stage.
			; 
			; Return type is int. It should always return 1.
			; 
			; Scanline *MUST* be on an even address or a misaligned 
			; address exception will occur.
			;
			; Back up W8..W11 as required.
			push.d	W8
			push.d	W10
			; Prepare Wregs.
			mov		W0, W9		; copy pointers
			mov		W1, W10		;
			mov		[W9], W0	; load pointers
			mov		[W10], W1	;
			mov		W2, W11		; number of words to be written
			mov		#0, W2 		; temporary
			mov		#0, W3 		; temporary
			mov		#0, W4 		; unused (old code)
			mov		#TRISB, W5	; address of TRISB (for quick access), not currently used
			mov		#PORTB, W6	; address of PORTB (for quick access), not currently used
			mov		#0x0020, W7	; output mask, bit 5 set: 0000 0000 0010 0000
			com		W7, W8		; inverted mask (of W7)
			; Use a DO loop for the output. We loop over each word plus one.
			; I love DO loops!! :)
			sub		W11, #1, W11
			do		W11, next_word
			; We have to be VERY fast with this code.
			;
			; We only have 52 us / 192 = < 270 ns per pixel.
			;
			; This works out to around 10.8 instructions per pixel, rounding to 10.
			; This code is very optimised and uses several quirks of the processor
			; to achieve the desired output.
			;
			; Each pixel has 8 instructions plus 2 nops (approx 250 ns per pixel)
			; The last has the two nops spare, which allows us to increment the
			; address pointers.
            nop
			output_pix		; -- 1st bit
			output_pix
			output_pix
			output_pix		; -- 4th bit
            nop
			output_pix
			output_pix
			output_pix
			output_pix		; -- 8th bit
            nop
			output_pix
			output_pix
			output_pix
			output_pix		; -- 12th bit
            nop
			output_pix
			output_pix
			output_pix
			output_pix_last	; -- 16th & last bit
           	; Clock stretching for I2C interface.
            ; If I2C buffer full, turn on clock stretching until
            ; we get a decent amount of time to handle it.
            btsc	I2C1STAT, #1	; RBF (receive buffer full) = bit 1
            bclr	I2C1CON, #12 	; SCLREL = bit 12 - clearing this bit turns on clock stretching
            ; NOP is here because DO doesn't want the last few instructions 
            ; to have branches/skips/etc.
            nop
            mov     [++W9], W0
next_word:	mov     [++W10], W1
			; Done! Restore W8..W11.
done:		pop.d	W10
			pop.d	W8
			; Return 1.
			mov		#1, W0
			return

