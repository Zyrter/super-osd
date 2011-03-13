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

.global	_osd_out_192

_osd_out_192:	
			; OSD output, assembly, for 192 pixel scanline
			; Expects the pointer to the set/clear scanline in W0. 
			; Expects the pointer to the black/white scanline in W1.
			; Expects the number of words (16 bits) to be output in W2.
			;
			; These are the order of the C arguments, so its prototype 
			; should be:
			; 
			;   int _osd_output_192(short *ptr_set_clear, short *ptr_black_white, short num_words); 
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
			; Use a DO loop for the output. We loop over each word.
			; I love DO loops!! :)
			sub		W11, #1, W11
			do		W11, next_word
            nop
            nop
			output_pix		; -- 1st bit
			output_pix
			output_pix
			output_pix		; -- 4th bit
            nop
            nop
			output_pix
			output_pix
			output_pix
			output_pix		; -- 8th bit
            nop
            nop
			output_pix
			output_pix
			output_pix
			output_pix		; -- 12th bit
            nop
            nop
			output_pix
			output_pix
			output_pix
			output_pix_last	; -- 16th & last bit
           	nop
            nop
            mov     [++W9], W0
next_word:	mov     [++W10], W1
			; Done! Restore W8..W11.
done:		pop.d	W10
			pop.d	W8
			; Return 1.
			mov		#1, W0
			return

.macro output_pix2
            rlnc    W0, W0
            rlnc    W1, W1
            and     W0, W7, W2
            ior     W2, W8, W2
            mov     W1, PORTB			; set PORT before TRIS - gives cleaner look
            mov     W2, TRISB
.endm

.macro output_pix_last2
            rlnc    W0, W0
            rlnc    W1, W1
            and     W0, W7, W2
            ior     W2, W8, W2
            mov     W1, PORTB
            mov     W2, TRISB
.endm

.global	_osd_out_256

_osd_out_256:	
			; OSD output, assembly, for 256 pixel scanline
			; Expects the pointer to the set/clear scanline in W0. 
			; Expects the pointer to the black/white scanline in W1.
			; Expects the number of words (16 bits) to be output in W2.
			;
			; These are the order of the C arguments, so its prototype 
			; should be:
			; 
			;   int _osd_output_256(short *ptr_set_clear, short *ptr_black_white, short num_words); 
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
			; Use a DO loop for the output. We loop over each word.
			; I love DO loops!! :)
			sub		W11, #1, W11
			do		W11, next_word2
            nop
            nop
			output_pix2			; -- 1st bit
			output_pix2
			nop
			output_pix2
			output_pix2			; -- 4th bit
			nop
			nop
			output_pix2
			output_pix2
			;nop
			output_pix2
			output_pix2			; -- 8th bit
			nop
			nop
			output_pix2
			output_pix2
			nop
			output_pix2
			output_pix2			; -- 12th bit
			nop
			nop
			output_pix2
			output_pix2
            nop
			output_pix2
			output_pix_last2	; -- 16th & last bit
			nop
            nop
            mov     [++W9], W0
next_word2:	mov     [++W10], W1
			; Done! Restore W8..W11.
done2:		pop.d	W10
			pop.d	W8
			; Return 1.
			mov		#1, W0
			return

