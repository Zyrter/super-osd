; Graphics core of the on screen display.
;
; Handles the display, video sync, scaling and
; graphics primitives.
;
; Copyright (C) 2010 Thomas Oldbury.
;
; This code is licensed under the GPL, version 2.
; For information, visit http://www.gnu.org/licenses/gpl-2.0.html

; TODOs
;  - Implement Bresenham's line drawing algorithm for arbitrary lines,
;    including optimisations for certain lines. Investigate repeated
;    pixel optimisations and how to implement them.
;  - Add a circle drawing algorithm.
;  - Consider I2C interface.;  - Consider adding toggle function to _drawpix.

.include "p33FJ128GP802.inc"

.equ	WIDTH, 256
.equ	HEIGHT, 192
.equ	FSIZE, ((WIDTH / 8) * HEIGHT)
.equ	FSIZEHALF, ((WIDTH / 8) * (HEIGHT / 2))
.equ	HBPIN, 15		; bit 15, port B
.equ	CTSPIN, 14		; bit 14, port B
.equ	FPSPIN, 13		; bit 13, port B

; CONST SECTION.
.section rdonly,psv

; Text/strings.
HWORLD:		.asciz	"Hello, world!"
LIPSUM1:	.ascii	"Lorem ipsum dolor sit amet, consectetur adipiscing elit. Donec id "
        	.ascii	"odio in risus pulvinar vehicula non at tortor. Nullam at urna "
        	.ascii	"velit, a adipiscing neque. Pellentesque tellus mauris, rhoncus " 
        	.ascii	"in volutpat in, iaculis quis arcu. Suspendisse at turpis lacus. "
        	.ascii	"Integer scelerisque, ipsum sit amet feugiat molestie, metus " 
        	.ascii	"tellus scelerisque dolor, blandit pharetra magna nunc sit amet "
        	.ascii	"turpis. Nunc vitae sem nulla. Sed sed enim non risus rhoncus "
        	.ascii	"molestie at a magna. Aliquam iaculis suscipit suscipit. Nunc "
        	.ascii	"iaculis ipsum et nisi tincidunt nec ullamcorper elit varius. "
        	.ascii	"Praesent pharetra cursus enim vitae tempus. Curabitur tincidunt "
        	.ascii	"tempus diam, vitae vehicula tortor rutrum vitae. Ut vitae urna "
        	.asciz	"lorem. Suspendisse pulvinar sagittis magna vel tempus."
STARTUP:	.asciz	"SuperOSD v2.0"

; DMA DATA SECTION
.section	dma

; Sound buffer (8 bit; 625 samples - rounded to 626 bytes)
; It is no mistake that the number of samples in this is equal
; to the number of lines in PAL. Less, more compacted samples
; are used in NTSC.
; TODO
SNDBUFF:	.space	626

; DATA SECTION
.bss
.align(0x800)	; start address of dsPIC memory

; Stack pointer
STACK:		.space 	256
; Line memory.
LINE:		.space	(WIDTH / 8)
; Video memory: two buffers 256x192 pixels (6KB) each.
VIDEO: 		.space	((WIDTH / 8) * HEIGHT * 2)
; Linear feedback shift register (PRNG).
LFSR:		.space	2
; Current draw and display video buffers.
.global		_BDRAW
_BDRAW:		.space	2
.global		_BDISP
_BDISP:		.space	2
; Horizontal offset
VID_HOFF:	.space	2
; Current vertical scale factor. 
; If PAL = 0.4444f * 64 = 29.
; If NTSC = 0.3f * 64 = 20.
; Rounded up.
VSF:		.space	2
; Definition of VBI. That is, the first visible line on a field.
; This value is usually 21; avoid changing this.
VBI:		.space	2
; Vertical offset. -25 to +25. In visible/drawn pixels.
VOFF:		.space	2
; If the video is interlaced, we need to compensate for this.
; This value is subtracted from the video line if it is equal
; to this count.
; This value is usually half the frame height, so 262 for NTSC
; or 312 for PAL.
INTLCOMP:	.space	2
; Runtime. 32 bit counter.
.global		_TIME
.align		
_TIME:		.space	4
TICKED:		.space	2		; whether or not we have ticked in current field
; Number of fields per second.
FIELDSSEC:	.space	2
; Skip odd lines (0 = no, 1 = yes.) Improves speed at expense of readability.
; NOT YET IMPLEMENTED
SKIP_ODD:	.space	2
; TV stuff.
TV_LINE:	.space	2
TV_GFX_Y:	.space	2
TV_SEQ:		.space	2
; Text sizing struct.
TSZ_WIDTH:	.space	2
TSZ_HEIGHT:	.space	2

; EXECUTABLE CODE & MACROS
.text

_save4:		.macro
			; Save W0..W3 and SR.
			; Similar to the push.s instruction, but can be nested.
			push.d	W0
			push.d	W2
			push	SR
			.endm

_res4:		.macro
			; Restore W0..W3.
			; Similar to the push.s instruction, but can be nested.
			pop		SR
			pop.d	W2
			pop.d	W0
			.endm

_abs:		.macro Wa, Wb
			btsc	\Wa, #15 
			subr	\Wa, #0, \Wb
			.endm

_skpix:		.macro Wa, Wb, k
			; skip drawing (slow) if pixel not visible
			mov		\k, \Wb
			cpslt	\Wa, \Wb
			return
			.endm

_hb:		.macro
			bset	PORTB, #HBPIN
			bclr	PORTB, #HBPIN
			.endm

			; Output a single pixel.
			; Use this for bits #0-#14, the last bit is an exception.
_pbit:		.macro	Wn, Bn
			bset	TRISB, #5	; clear for last pixel
			btsc	\Wn, \Bn	; test Wn bit
			bclr	TRISB, #5	; make output (or skipped over)
			bset	PORTB, #5	; write bit; this is effectively a NOP if pin not output
			nop					; scale pixel... processor is fast!
			nop					; scale again
			nop					; scale again
			.endm
		
			; Output a single pixel for the last bit.
			; This routine does not contain any stretch pixel parts so has two cycles free.
_plbit:		.macro	Wn, Bn
			bset	TRISB, #5	; clear for last pixel
			btsc	\Wn, \Bn	; test Wn bit
			bclr	TRISB, #5	; make output (or skipped over)
			bset	PORTB, #5	; write bit; this is effectively a NOP if pin not output
			.endm

.global		__reset

__reset:	; Call initialization routine
			call	init
			; Call main routine
			call	_main
			reset

init:		; Initialization routine. Called on reset and bootup.
			; Setup SPLIM, 256 byte stack.
			mov		#0x800+256, W0
			mov		W0, SPLIM
			; Setup HBPIN, CTSPIN and FPSPIN as output
			bclr	TRISB, #HBPIN
			bclr	TRISB, #CTSPIN
			bclr	TRISB, #FPSPIN
			; Signal a heartbeat.
			_hb
			; Setup RB6, RB7 as inputs.
			bset	TRISB, #6
			bset	TRISB, #7
			; Setup CN interrupt priority (level 5, 101)
			bset	IPC4, #12
			bclr	IPC4, #13
			bset	IPC4, #14
			; Set CNIE, enabling change interrupts.
			bset	IEC1, #3
			; Clear CNIF.
			bclr	IFS1, #3
			; Setup change notify on CN23, CN24; bits 7 and 6
			clr		CNEN1
			clr		CNEN2
			bclr	CNEN2, #7
			bset	CNEN2, #8
			; Setup CPU IPL.
			disi	#4				; interrupts disabled for next 4 cycles
			bclr	SR, #7
			bclr	SR, #6
			bclr	SR, #5
			bclr	CORCON, #IPL3
			; Enable PSV. So we can read const data.
			bset	CORCON, #PSV
			; Clear watchdog.
			clrwdt
			; Setup PLL. I don't understand these values, but they work.
			; PLLFBD=41 is based on trial and error, it gives about 39.7 MIPS,
			; just within the rated 40 MIPS (may overclock this later.)
			mov		#41, W0			; setup the PLL feedback(?)
			mov		W0, PLLFBD
			mov		CLKDIV, W0		; mask CLKDIV so we can set PLLPRE=0,PLLPOST=0
			mov		#0xff20, W1		; 1111 1111 0010 0000
			and		W0, W1, W0
			mov		W0, CLKDIV
			; We are now running at 39.7 MIPS... fast!
			; Vertical offset works best at +12 for now. 
			mov		#12, W0
			mov		W0, VOFF
			; Clear h offset. W0 = 0, as above.
			mov		W0, VID_HOFF
			; Setup all parameters for PAL TV.
			mov		#44, W0
			mov		W0, VSF
			mov		#22, W0
			mov		W0, VBI
			mov		#312, W0
			mov		W0, INTLCOMP
			mov		#50, W0
			mov		W0, FIELDSSEC
			; Use first buffer for both drawing and output.
			; Also clear the buffers while we're doing this.
			mov		#1, W0
			mov		W0, _BDRAW
			mov		W0, _BDISP
			mov		#0x0000, W0
			call	_fill_mem
			mov		#0, W0
			mov		W0, _BDRAW
			mov		W0, _BDISP
			mov		#0x0000, W0
			call	_fill_mem
			; Clear time to zero.
			mov		#0, W0
			mov		W0, _TIME
			mov		W0, _TIME+2
			; Turn on CTS pin.
			bset	PORTB, #CTSPIN
			; Setup LFSR with the initial value.
			mov		#0xACE1, W0
			mov		W0, LFSR
			return

.global __CNInterrupt

__CNInterrupt:
			; Turn off CTS pin.
			bset	PORTB, #CTSPIN	
			; If CSYNC high, return.
			;btsc	PORTB, #6
			;bra		exit1
			; Push all important vars to stack
			push.s
			push.d	W4
			push.d	W6
			push.d	W8
			push.d	W10
			push.d	W12
			push	W14
			push	RCOUNT
			push	DCOUNT
			push	DOSTARTL
			push	DOSTARTH
			push	DOENDL
			push	DOENDH
			; Clear CN mismatch by reading PORTB and discarding.
			mov		PORTB, W0
			clr		W0
			; Call the line handler. In a separate routine so we can have multiple
			; sources of video trigger.
			call	lineproc
			; Pop all important vars
			pop		DOENDH
			pop		DOENDL
			pop		DOSTARTH
			pop		DOSTARTL
			pop		DCOUNT
			pop		RCOUNT
			pop		W14
			pop.d	W12
			pop.d	W10
			pop.d	W8
			pop.d	W6
			pop.d	W4
			pop.s
			; IFS1.CNIF = 0, clear change notify interrupt flag
			bclr	IFS1, #3
			; Turn on CTS pin.
exit1:		bclr	PORTB, #CTSPIN
			retfie

lineproc:	; Handle a line.
			; Start TMR1.
			bset	T1CON, #15		; T1CON.TON = 1
			clr		TMR1
			; If VSYNC low, call new frame processor.
			btss	PORTB, #7
			rcall	newframe
			; If line = 5, tick the RTC. (5 is arbitrary.)
			mov		TV_LINE, W0
			cp		W0, #5
			bra		nz, continueln
			; If we get here, we need to tick the RTC.
			mov		_TIME, W2
			mov		_TIME+2, W3
			add		W2, #1, W2
			addc	W3, #0, W3
			mov		W2, _TIME
			mov		W3, _TIME+2
			; Increment the line counter. 
			; Why does "INC" not work?
continueln:	mov		TV_LINE, W0
			add		W0, #1, W0
			; Deinterlacer.
			mov		INTLCOMP, W1	; move interlace compensation into W3
			cpslt	W0, W1			; run deinterlacer if greater than
			subr	W0, #1, W0
			mov		W0, TV_LINE
			; If we are in the VBI, we shouldn't display anything.
			mov		VBI, W1
			cpsgt	W0, W1			; W0 contains TV_LINE as above
			bra		exit
			; If line is odd, and we are set to skip odd lines, don't draw anything.
			; FIXME/TODO
			;btss	SKIP_ODD, #0
			;bra		calcy
			;btss	TV_LINE, #0
			;return
			; Calculate the Y row for the current field.
			; This is calculated using fixed point math.
			; Y = (TV_line * MultFactor) / 64
			;
			; where MultFactor is the multiplication factor 
			; in decimal times 64. Division is accomplished using
			; a barrel shift divide.
			; W0 contains current TV line as above.
calcy:		mov		VSF, W1			; move vertical scale factor (VSF) to W1
			mov		VBI, W2			; move VBI to W2
			sub		W0, W2, W0		; offset video position by VBI
			mul.uu	W0, W1, W2		; W2,W3 = u(W0) * u(W1)
			; We only care about W2, because the result should fit in 16 bits.
			asr		W2, #6, W2		; shift right 6 times (arithmetic), equivalent to divide by 64 unsigned
			mov		W2, TV_GFX_Y	; Move W2 to Y
			; Wait for CSYNC (RB6) to go low. 
			; FUTURE: we could sleep here or do some drawing
waitcs:		btss	PORTB, #6
			bra		waitcs
			; If TV_GFX_Y > HEIGHT, return, otherwise we risk an address exception.
			mov		TV_GFX_Y, W0
			mov		#HEIGHT, W1
			add		W0, #1, W0		; add 1 because we are checking for less than or equal
			cpslt	W0, W1
			bra		exit
			; Prepare the line buffer. Calculate addresses.
			; Code below to help line up video and OSD.
			;mov		#LINE, W0
			;mov		#0xcccc, W1		; 'error' pattern
			;mov		#HEIGHT, W2
			;mov		TV_GFX_Y, W3
			;cpsgt	W3, W2			; W3 > W2? If so, copy W3 to W1
			;mov		W3, W1
			; Calculate the pointer in W1 and store data into the pointer at W0.
			mov		#LINE, W0
			mov		#VIDEO, W1
			; Add display buffer pointer.
			mov		#FSIZE, W2
			mov		_BDISP, W3
			mul.uu	W2, W3, W2
			add		W1, W2, W1
			; Add 'Y' row.
			mov		TV_GFX_Y, W2
			mov		#(WIDTH / 8), W3
			mov		VOFF, W4		; move VOFF to W4
			sub		W2, W4, W2		; offset graphics by VOFF
			mul.uu	W2, W3, W2
			add		W1, W2, W1
			; Check address not out of bounds (due to VOFF being out of range for example.)
			; This code is preliminary; before it was causing some problems, but now it
			; seems to work. Have to keep an eye on it.
			mov		#VIDEO, W2
			cpsgt	W1, W2
			return
			mov		#(VIDEO+(FSIZE*2)), W2
			cpslt	W1, W2
			return
			; Copy the data. I love how this is fast! 16 cycles for the copy.
			repeat	#(WIDTH / 16)
			mov.w	[W1++], [W0++]
			;mov.w	W1, [W0++]
			; Calculate the value for TMR1.
			; We can add or subtract from this value to adjust the horizontal position.
			; FIXME, some glitch happens when we enable this!
			mov		#400, W0		; constant, from trial and error gets us in the right place
			;mov		VID_HOFF, W1
			;add		W0, W1, W0
			; Wait for TMR1 to reach calculated value.
waittmr:	cp		TMR1			; compare TMR1 with WREG (W0)
			bra		lt, waittmr
			; Signal a heartbeat.
			;bclr	TRISB, #5
			;bset	PORTB, #5
			;repeat	#30
			;nop
			;bset	TRISB, #5
			; Output each bit.
			mov		#0x900, W1
			mov		#0, W0
			; Clear watchdog.
			clrwdt
			; I love this processor for its DO loops.
			; This code would not be possible without them.
pixbegin:	do		#16, byteend
			_pbit	W0, #15
			_pbit	W0, #14
			_pbit	W0, #13
			_pbit	W0, #12
			_pbit	W0, #11
			_pbit	W0, #10
			_pbit	W0, #9
			_pbit	W0, #8
			_pbit	W0, #7
			_pbit	W0, #6
			_pbit	W0, #5
			_pbit	W0, #4
			_pbit	W0, #3
			_pbit	W0, #2
			_pbit	W0, #1
			_plbit	W0, #0
			mov		[W1++], W0
			nop
byteend:	nop
			bset	TRISB, #5
			; Stop TMR1.
exit:		bclr	T1CON, #15		; T1CON.TON = 1
			clr		TMR1
			return

newframe:	; TV_LINE = 0
			mov		#0, W0
			mov		W0, TV_LINE
			; Clear TICKED bit.
			bclr	TICKED, #0
			return

.global		_delay

			; Arbitrary delay function.
			; Uses a DO loop and REPEAT loop.
_delay:		; W0 = delay count.
			do		W0,	delayend
			repeat	#16383
			nop
			nop
delayend:	nop
			return

;			; Generate a random LFSR number. 
;			; Clobbers W0..W2.
;lfsr_rand:	; Result in W0.			
;			; Compute LSB (0 or 1.)
;			mov		LFSR, W0
;			and		W0, #1, W1		; LSB = W1 = W0 & 1
;			; Shift right once LFSR in W0.
;			lsr		W0, #1, W0
;			; If LSB = 1, then XOR with 0xB400.
;			mov		#0xA1A1, W2
;			btsc	W0, #1
;			xor		W0, W2, W0
;			; Move LFSR back.
;			mov		W0, LFSR
;			; Return. LFSR/W0 is our number.
;			return
;
;			; Get a random number W0..W1.
;			; Clobbers W0..W4.
;getrand:	; Result in W0.
;			; Calculate the random span and determine if we can use AND 
;			; instead of the slower modulo.
;			sub		W1, W0, W2
;			add		W2, #1, W2
;			; If x(W2) == 0 then span is zero so return W0 (first arg.)
;			cp0		W2
;			bra		nz, rand
;			return
;			; Get random number. W4 holds value.
;rand:		push.d	W0
;			push	W2
;			call	lfsr_rand
;			mov		W0, W4
;			pop		W2
;			pop.d	W0
;			; Decide which method to use.
;			; Power of two if x & (x - 1) == 0 for nonzero unsigned x.
;			sub		W2, #1, W3
;			and		W0, W3, W3
;			cp0		W3
;			bra		nz, modrand
;			; Use AND range limiter
;andrand:	sub		W2, #1, W2
;			and		W4, W2, W1
;			add		W0, W1, W0
;			return
;			; Or, use the hardware divider, which is slower.
;modrand:	push	W0
;			repeat	#17
;			div.u	W4, W2
;			; W0 holds quotient, which we don't need, W1 holds remainder, which we want.
;			; Pop W0 from stack (overwriting quotient.)
;			pop		W0
;			; Add W1 to W0 and done.
;			add		W0, W1, W0
;			return

.global		_clear_mem

			; Efficient clear mem routine.
_clear_mem:	mov		#0, W0
			call	_fill_mem
			return

.global		_fill_mem

			; Efficient fill mem routine.
			; Fills memory with a specific word.
			; W0 = word to use
			; 3083 cycles
_fill_mem:	; Which memory to clear?
			; Compute address of memory.
			mov		_BDRAW, W1
			mov		#FSIZE, W2
			mov		#VIDEO, W3
			btsc	W1, #0
			add		W2, W3, W3
			; Now clear each word FSIZEHALF times.
			; Note that we are writing two bytes (words) at a time, this is 2x faster!
			repeat	#FSIZEHALF
			mov		W0, [W3++]
			return

			; Copy the DRAW buffer to the DISP buffer.
copybuff:	; Clobbers W0..W6.
			; Add display buffer pointer into W1.
			; Calculate addresses for each buffer, W0 and W3.
			mov		#VIDEO, W0
			mov		#FSIZE, W1
			mov		_BDRAW, W2
			mul.uu	W2, W1, W4		; W4,W5 = W2 * W1
			add		W4, W0, W6		; use W4 lower word		
			mov		_BDISP, W2
			mul.uu	W2, W1, W4
			add		W4, W0, W7
			; Copy, word at a time. Wow, this is fast.
			repeat	#FSIZEHALF
			mov		[W6++], [W7++]
			return
	
			; Calculate address of x,y.
			; x (W0) as a word index from 0..(WIDTH / 16).
			; y (W1) as a row pointer from 0..HEIGHT.
			; Result in W2.
			; Clobbers W0..W7.
calcaddr:	; Draw buffer always used.
			; Calculate buffer offset.
			mov		#VIDEO, W2
			mov		#FSIZE, W3
			mov		_BDRAW, W4
			mul.uu	W3, W4, W4		; W4, W5 clobbered
			add		W2, W4, W2
			; Add 'Y' row.
			mov		#(WIDTH / 8), W3
			mul.uu	W3, W1, W4
			add		W2, W4, W2
			; Add X. Add it twice because we are word aligned.
			add		W2, W0, W2
			add		W2, W0, W2
			;; Align to word(?)
			;mov		#0xfffe, W0
			;and		W2, W0, W2
			; Return; answer is in W2.
			return

			; Calculate address of x,y.
			; x (W0) as a word index from 0..(WIDTH / 16).
			; y (W1) as a row pointer from 0..HEIGHT.
			; Result in W2.
			; Clobbers W0..W5.
calcaddr2:	; Display buffer always used.
			; Calculate buffer offset.
			mov		#VIDEO, W2
			mov		#FSIZE, W3
			mov		_BDISP, W4
			mul.uu	W3, W4, W4		; W4, W5 clobbered
			add		W2, W4, W2
			; Add 'Y' row.
			mov		#(WIDTH / 8), W3
			mul.uu	W3, W1, W4
			add		W2, W4, W2
			; Add X. Add it twice because we are word aligned.
			add		W2, W0, W2
			add		W2, W0, W2
			;; Align to word(?)
			;mov		#0xfffe, W0
			;and		W2, W0, W2
			; Return; answer is in W2.
			return

			; Write byte at x,y.
			; x (W0) as a word index from 0..(WIDTH / 16).
			; y (W1) as a row pointer from 0..HEIGHT.
			; W2 holds byte to write.
			; Clobbers W0..W6.
wword:		; Draw buffer used.
			; Calculate pointer.
			exch	W2, W6
			call	calcaddr
			; Write word & done.
			mov		W6, [W2]
			return

			; Read byte at x,y.
			; x (W0) as a word index from 0..(WIDTH / 16).
			; y (W1) as a row pointer from 0..HEIGHT.
			; W2 contains result.
			; Clobbers W0..W5.
rword:		; Draw buffer used.
			; Calculate pointer.
			call	calcaddr
			; Read word & done.
			mov		[W2], W2
			return

.global		_setpix

			; PIXEL SET/CLEAR/TOGGLE ROUTINES
			; TODO: reduce code repetition
			; A lot of this code could go into macros or other functions
			
			; Draw a pixel (set) at x,y.
			; x (W0) from 0..WIDTH-1
			; y (W1) from 0..HEIGHT-1
			; Clobbers W0..W5.
_setpix:	; Ignore out of range pixels, or we could have a memory access violation.
			_skpix	W0, W2, #WIDTH
			_skpix	W1, W2, #HEIGHT
			; Calculate the word in which this pixel resides. 
			; Essentially a divide by 16, or barrel shift 4 times.
			asr		W0, #4, W3
			; Calculate the bit in which this pixel resides.
			; Essentially, AND it with 15 (1 less than 2^4 (16))
			and		W0, #15, W4
			; Calculate the address in W2.
			push	W3
			push	W4
			mov		W3, W0
			call	calcaddr
			pop		W4
			pop		W3
			; Create the mask to OR with.
			mov		#0x0001, W5
			subr	W4, #15, W4			; compute W4 = 15 - W4, effectively flipping the bits9
			sl		W5, W4, W5
			; Read pixel, OR mask, write back. Because of the frankly awesome 
			; dsPIC architecture, we can do this in ONE cycle! :)
			ior		W5, [W2], [W2]
			return

.global 	_clrpix

			; Clear a pixel at x,y.
			; x (W0) from 0..WIDTH-1
			; y (W1) from 0..HEIGHT-1
			; Clobbers W0..W5.
_clrpix:	; Ignore out of range pixels, or we could have a memory access violation.
			_skpix	W0, W2, #WIDTH
			_skpix	W1, W2, #HEIGHT
			; Calculate the word in which this pixel resides. 
			; Essentially a divide by 16, or barrel shift 4 times.
			asr		W0, #4, W3
			; Calculate the bit in which this pixel resides.
			; Essentially, AND it with 15 (1 less than 2^4 (16))
			and		W0, #15, W4
			; Calculate the address in W2.
			;push	W3
			push	W4
			mov		W3, W0
			call	calcaddr
			pop		W4
			;pop		W3
			; Create the mask to AND with.
			mov		#0x0001, W5
			subr	W4, #15, W4			; compute W4 = 15 - W4, effectively flipping the bits
			sl		W5, W4, W5
			com		W5, W5				; complement W5, so we can clear pixels by ANDing
			; Read pixel, AND mask, write back.
			and		W5, [W2], [W2]
			return	

.global		_togpix

			; Toggle a pixel (on/off) at x,y.
			; x (W0) from 0..WIDTH-1
			; y (W1) from 0..HEIGHT-1
			; Clobbers W0..W5.
_togpix:	; Ignore out of range pixels, or we could have a memory access violation.
			_skpix	W0, W2, #WIDTH
			_skpix	W1, W2, #HEIGHT
			; Calculate the word in which this pixel resides. 
			; Essentially a divide by 16, or barrel shift 4 times.
			asr		W0, #4, W3
			; Calculate the bit in which this pixel resides.
			; Essentially, AND it with 15 (1 less than 2^4 (16))
			and		W0, #15, W4
			; Calculate the address in W2.
			;push	W3
			push	W4
			mov		W3, W0
			call	calcaddr
			pop		W4
			;pop		W3
			; Create the mask to AND with.
			mov		#0x0001, W5
			subr	W4, #15, W4			; compute W4 = 15 - W4, effectively flipping the bits
			sl		W5, W4, W5
			; Read pixel, XOR mask, write back.
			xor		W5, [W2], [W2]
			return	

.global		_testpix

			; Test a pixel at x,y.
			; x (W0) from 0..WIDTH-1
			; y (W1) from 0..HEIGHT-1
			; Clobbers W0..W5.
			; Result in W0 (0 = clear, 1 = set.)
_testpix:	; Ignore out of range pixels, or we could have a memory access violation.
			_skpix	W0, W2, #WIDTH
			_skpix	W1, W2, #HEIGHT
			; Calculate the word in which this pixel resides. 
			; Essentially a divide by 16, or barrel shift 4 times.
			asr		W0, #4, W3
			; Calculate the bit in which this pixel resides.
			; Essentially, AND it with 15 (1 less than 2^4 (16))
			and		W0, #15, W4
			; Calculate the address in W2.
			push	W4
			mov		W3, W0
			call	calcaddr
			pop		W4
			; Read pixel, test bit.
			; This is a bit long winded... could it be optimised?
			mov		#0, W0
			mov		[W2], W3
			btst.c	W3, W4
			mov		#0, W5
			bsw.c	W0, W5
			return	

.global		_drawpix

			; Draw a pixel (set or clear) at x,y, according to W2.
			; x (W0) from 0..WIDTH-1
			; y (W1) from 0..HEIGHT-1
			; W2 whether or not to draw (0 = don't draw, 1 = draw)
_drawpix:	; Clobbers W0..W5.
			cp		W2, #1
			bra		z, doset
			call	_clrpix
			return
doset:		call	_setpix
			return

.global		_swapbuffs

_swapbuffs:	; Swap the display and draw buffers.
			mov		_BDRAW, W0
			subr	W0, #1, W0
			mov		W0, _BDRAW
			mov		_BDISP, W0
			subr	W0, #1, W0
			mov		W0, _BDISP
			return

			; Toggle the neighbours of a pixel.
			; x (W0) from 0..WIDTH-1
			; y (W1) from 0..HEIGHT-1
togneigh:	; Clobbers W0..W6.
			push.d	W0
			; x-1, y-1
			sub		W0, #1, W0
			sub		W1, #1, W1
			call	_togpix
			; x, y-1
			pop.d	W0
			push.d	W0
			sub		W1, #1, W1
			call	_togpix
			; x+1, y-1
			pop.d	W0
			push.d	W0
			add		W0, #1, W0
			sub		W1, #1, W1
			call	_togpix
			; x-1, y
			pop.d	W0
			push.d	W0
			sub		W0, #1, W0
			call	_togpix
			; x, y not processed
			; x+1, y
			pop.d	W0
			push.d	W0
			add		W0, #1, W0
			call	_togpix
			; x-1, y+1
			pop.d	W0
			push.d	W0
			sub		W0, #1, W0
			add		W1, #1, W1
			call	_togpix
			; x, y+1
			pop.d	W0
			push.d	W0
			add		W1, #1, W1
			call	_togpix
			; x+1, y+1
			pop.d	W0
			push.d	W0
			add		W1, #1, W1
			call	_togpix
			; done!
			pop.d	W0
			return

			; Draw a vertical line.
			; x    (W0) from 0..WIDTH-1
			; y0   (W1) from 0..HEIGHT-1
			; y1   (W2) from 0..HEIGHT-1
			; mode (W3) from 0..2; 0 being clear, 1 being visible, 2 being toggle.
			;
			; Uses an optimised word writing algorithm, so is almost always 
			; faster than Bresenham's.
			;
			; Clobbers W0..W11.
			;
			; Similar to the _setpix routine, but repeats its write over however
			; many Y positions need to be written. It is always O(n).
			;
dvline:		; If X out of bounds, return.
			_skpix	W0, W5, #WIDTH
			; If either Y out of bounds, return.
			_skpix	W1, W5, #HEIGHT
			_skpix	W2, W5, #HEIGHT
			; If y0 > y1, exchange y0 and y1.
			cpslt	W1, W2
			exch	W1, W2
			; If y0 == y1, return; a line of zero length yields zero pixels.
			cpsne	W1, W2
			return
			; Calculate the word in which this pixel resides. 
			; Essentially a divide by 16, or barrel shift 4 times.
			asr		W0, #4, W4
			; Calculate the bit in which this pixel resides.
			; Essentially, AND it with 15 (1 less than 2^4 (16))
			and		W0, #15, W6
			; Calculate the address in W2.
			push	W1
			push.d	W2
			push	W6
			; W4 holds W0(x) / 16 (x word), so move that into W0.
			; W1 holds Y0, that's already in the right place so leave it.
			mov		W4, W0
			call	calcaddr
			mov		W2, W5		; copy W2(result) into W5, dhvline always uses W5 for addr
			pop		W6
			pop.d	W2
			pop		W1
			; Create the mask to OR/NAND/XOR with.
			mov		#0x0001, W8
			subr	W6, #15, W6
			sl		W8, W6, W8
			; Write in a DO loop; we need to loop W2 - W1 = W0 times.
			sub		W2, W1, W0
			do		W0, writeline
			push	W8			; NAND clobbers W8, so push it
			call	dhvwrite	; call it
			pop		W8			; then pop it
			add		#(WIDTH / 8), W5
writeline:	nop
			return

			; Draw a horizontal line.
			; x0   (W0) from 0..WIDTH-1
			; x1   (W1) from 0..WIDTH-1
			; y    (W2) from 0..HEIGHT-1
			; mode (W3) from 0..2; 0 being clear, 1 being visible, 2 being toggle.
			;
			; Uses an optimised word writing algorithm, so is almost always 
			; faster than Bresenham's.
			;
dhline:		; Clobbers W0..W11.
			;
			; Horizontal line drawing algorithm is explained below.
			;
			; There are two possible cases for drawing a horizontal line:
			;  1) It resides entirely inside a single word.
			;  2) It resides in two or more words.
			;
			; One word = 16 bits.
			;
			; The first case is handled by writing the middle using a complicated
			; bit-banging algorithm which takes advantage of the barrel shifter.
			; It is typically O(1).
			;
			; The second case is handled by writing the two edges, then writing
			; all the words between the two. It is an O(n) algorithm.
			;
			; Each of the cases is documented individually.
			
			; Determine which case this falls in to.
			;
			; If x0 == x1, don't draw anything. A line of zero length
			; is invisible because it is a infinitely small point.
			cpsne	W0, W1
			return
			; If x0 > x1, flip the two around.
			cpslt	W0, W1
			exch	W0, W1
			; If x0 or x1 > video width, return.
			; FIXME: what about the _skpix macros(?)
			mov		#WIDTH+1, W4
			cpslt	W0, W4
			return
			mov		#WIDTH+1, W4
			cpslt	W1, W4
			return
			; If y > video height, return.
			; FIXME: what about the _skpix macros(?)
			mov		#HEIGHT+1, W4
			cpslt	W2, W4
			return
			; There's probably a better way than doing lots of push/pop operations
			; than this; we waste at least 18 cycles just on push/pop.
			push.d	W0
			push.d	W2
			asr		W0, #4, W0
			mov		W2, W1
			call	calcaddr
			mov		W2, W4
			pop.d	W2					; restore Wregs
			pop.d	W0
			push.d	W0					; push them again
			push.d	W2					; a more efficient way would be to advance the W15 stack 
			push	W4					; pointer 5 places, as the values would still be there.
			asr		W1, #4, W0
			mov		W2, W1
			call	calcaddr
			mov		W2, W5
			pop		W4
			pop.d	W2
			pop.d	W0
			; If the two parts reside in the same address, go to the first case,
			; otherwise, go to the second case.
			cp		W4, W5
			bra		z, _1stcase
			bra		nz, _2ndcase
_1stcase:	; First case. Use the word addresses in W4 and W5 (W5 == W4) to 
			; write a bit mask.
			;
			; What we need to do is 'fill' from two bit poistions.
			;
			; For example if we want to fill from bit 10 to bit 5, the intended
			; result is a mask like this (remember the dsPIC is a little-endian 
			; chip):
			;    
			;     1 1 1
			;     4 2 0 8 6 4 2 0 (bit #)
			;    0000011111100000
			; 
			; To do this, we observe that one less than a power of two is always
			; a string of '1's. We compute two powers of two and XOR them together.
			; 
			; This is a very fast operation (11 cycles, not including the time to 
			; write the data) and is constant in time.
			;
			; The dsPIC's barrel shifter is what makes this possible.
			
			; Compute bits to be set. Use W5 and W6 as stores.
			and		W0, #15, W5
			;add		W5, #1, W5
			and		W1, #15, W6
			add		W6, #1, W6
			; Compute first mask.
			mov		#1, W7
			sl		W7, W5, W7
			sub		W7, #1, W7
			; Compute second mask.
			mov		#1, W8
			sl		W8, W6, W8
			sub		W8, #1, W8
			; XOR the masks together to get the final, super-mask (W8).
			xor		W8, W7, W8
			; Call the word writer. The word writer will set or clear
			; appropriately and allows for future expansion e.g. toggling bits.
			mov		W4, W5
			call	dhvwrite		; dhwrite always uses W8 for the word and W5 for the addr
			return

_2ndcase:	; The second case is more of an extension of the first case. We 
			; write the edges and then we write the middle.
			; 
			; It is an O(n) algorithm; time varies depending on the number of 
			; words written.
			;
			; FIXMEs: the DO count sometimes may be wrong.

			; Compute bits to be set.
			and		W0, #15, W6
			sub		W6, #1, W6
			and		W1, #15, W7
			; Compute first mask.
			; W8 = ((1 << (15 - W5)) - 1);
			mov		#1, W8
			subr	W6, #15, W6
			sl		W8, W6, W8
			sub		W8, #1, W8
			push	W5				; hmm... consider an EXCH Ws,Wd instruction instead
			mov		W4, W5
			call	dhvwrite
			pop		W5
			; Compute second mask.
			; W8 = ~((1 << (15 - W6)) - 1);
			mov		#1, W8
			subr	W7, #15, W7
			sl		W8, W7, W8
			sub		W8, #1, W8
			com		W8, W8
			call	dhvwrite
			; Write blocks from W5+1 to W6-1.
			; Use a DO loop. The DO count (W9) is simply ((W5-W4) / 2) - 1.
			sub		W5, W4, W9		; W9 = W5 - W4
			asr		W9, #1, W9		; W9 = W9 asr 1		(W9 = W5 - W4); divide by two (asr = arithmetic shift right)
			sub		W9, #1, W9		; subtract 1 from W9 as do iterates +1 more than necessary
			; If current DO count <= 0, return. It could be less than
			; zero if the above SUB rolls over past zero (signed numbers.)
			mov		#0, W8
			cp		W9, W8
			bra		le, exit3
			; Write each word. We write 0xffff; this is then passed thru
			; a function such as IOR, NAND or XOR which sets, clears or 
			; toggles pixels appropriately.
			mov		#0xffff, W8
			add		W4, #2, W5		; word aligned, add 2
			sub		W9, #1, W9		; subtract 1 from W9 as do iterates +1 more than necessary
			do		W9, __wword
			rcall	dhvwrite
			add		W5, #2, W5		; word aligned, add 2
__wword:	nop
exit3:		return
			
			; Word writing routine designed for dhline/dvline.
			; W3 holds mode (0 = clear, 1 = write, 2 = toggle.)
			; W5 holds word address.
			; W8 holds word to write.
dhvwrite:	; W10, W11 reserved as temporaries.
			; Ensure we don't cause any trouble with an invalid mode.
			cp		W3, #3
			; If it is greater than, branch to the nearest return.
			; Don't change writeCLR without changing this; this way we don't need another return.
			bra		gt, writeCLR+2		
			; Branch to the right routine (computed branch.)
			; Blank parts of the routines should be filled with NOPs.
			mul.uu	W3, #4, W10
			bra		W10
writeCLR:	com		W8, W8
			and		W8, [W5], [W5]	
			return
			nop
writeSET:	ior		W8, [W5], [W5]
			return
			nop
			nop
writeTOGG:	xor		W8, [W5], [W5]
			return
			nop
			nop
			; Catch return. Hopefully.
			return

.global		_dvline

			; C entry point for dvline. 
_dvline:	; Backs up W8-W11 as required.
			push.d	W8
			push.d	W10
			call	dvline
			pop.d	W10
			pop.d	W8
			return

.global		_dhline

			; C entry point for dhline. 
_dhline:	; Backs up W8-W11 as required.
			push.d	W8
			push.d	W10
			call	dhline
			pop.d	W10
			pop.d	W8
			return

			; Draw a bitmap type 1.
			; Type 1 is uncompressed and always fills the screen (WIDTH x HEIGHT.)
			; ptr(W0) is the pointer to the bitmap. 
			;   Usually this falls into the const space.
drawbm1:	;   Remember to set PSVPAG, or unexpected results may occur.
			; Process each byte until we reach a Y of HEIGHT.
			mov		#VIDEO, W1
			mov		#FSIZE, W2
			mov		_BDRAW, W3
			mul.uu	W2, W3, W2
			add		W2, W1, W1
			repeat	#FSIZE
			mov.b	[W0++], [W6++]
			return

.global		_drawbm2

			; Draw a bitmap type 2.
			; Type 2 is RLE compressed and always fills the screen (WIDTH x HEIGHT.)
			; ptr(W0) is the pointer to the bitmap. 
			;   Usually this falls into the const space.
			;   Remember to set PSVPAG, or unexpected results may occur.
_drawbm2:	; Clobbers W0..W7
			; Process each byte until we reach a Y of HEIGHT.
			mov		#VIDEO, W1
			mov		#FSIZE, W2
			mov		_BDRAW, W3
			mul.uu	W2, W3, W2
			add		W2, W1, W1
			mov		W1, W6
			mov		#FSIZE, W2
			add		W6, W2, W6
			add		W2, W1, W2
byte2loop:	mov.b	[W0++], W4		; Copy repcount
			mov.b	[W0++], W5		; Copy repdigit
			; Check W4 > 0, otherwise, next block.
			cp0		W4
			bra		z, byte2loop
			sub		W4, #1, W4		; Subtract one from count; REPEAT executes +1 more than we want
			; Check that W1+W4+1 < W6 (effectively W1+W4 <= W6); if not, return.
			; TODO: instead of this perhaps we should clip the value?
			add		W1, W4, W7
			add		W7, #1, W7
			cpslt	W7, W6
			return
			; Copy bytes
			repeat	W4
			mov.b	W5, [W1++]
			; Branch back to byte1loop if W6 less than final position.
			cp		W1, W2
			bra		lt, byte2loop
			return

			; Draw a diffmap type 2.
			; Type 2 is RLE compressed and always fills the screen (WIDTH x HEIGHT.)
			; ptr(W0) is the pointer to the bitmap. 
			;   Usually this falls into the const space.
drawdf2:	;   Remember to set PSVPAG, or unexpected results may occur.
			; Process each byte until we reach a Y of HEIGHT.
			mov		#VIDEO, W1
			mov		#FSIZE, W2
			mov		_BDRAW, W3
			mul.uu	W2, W3, W2
			add		W2, W1, W1
			mov		W1, W6
			mov		#FSIZE, W2
			add		W6, W2, W6
			add		W2, W1, W2
byted2loop:	mov.b	[W0++], W4		; Copy repcount
			mov.b	[W0++], W5		; Copy repdigit
			; Check W4 > 0, otherwise, next block.
			cp0		W4
			bra		z, byte2loop
			; XOR with zero is a NOP, so check for that and skip if necessary.
			cp0		W5
			bra		gtu, notzero
			; If zero, offset W1 pointer and read next bytes.
			add		W1, W4, W1
			bra		byted2loop
			; We're not doing a zero XOR operation, so process the bytes.
notzero:	sub		W4, #1, W4		; Subtract one from count; DO executes +1 more than we want 
			; Check that W1+W4+1 < W6 (effectively W1+W4 <= W6); if not, return.
			; TODO: instead of this perhaps we should clip the value?
			add		W1, W4, W7
			add		W7, #1, W7
			cpslt	W7, W6
			return
			; XOR bytes. 2 cycles per byte... fast!
			; We can't use post increment here for some reason. :( Otherwise, we 
			; could have a one cycle per byte execution time.
			do		W4, xorloop
			xor.b	W5, [W1], [W1]
xorloop:	add		W1, #1, W1
			; Branch back to byte1loop if W6 less than final position.
			cp		W1, W2
			bra		lt, byted2loop
			return

			; Draw an ASCII character at a given absolute position on the display.
			; W0 (character) 	0 .. 255, upper byte ignored
			; W1 (x) 			0 .. WIDTH-1
			; W2 (y)			0 .. HEIGHT-1
			; W3 (mode)			0 (normal) or 1 (inverted) mode
			; W4 (font)			font number
			; Page 0 is always used for the fonts. All the fonts must fit in the first 32K.
			;	(this is usually not a problem.)
drawchar:	; Clobbers W0..W11.
			; TODO: Optimise Wreg usage.
			; Clamp W0 so it ranges from 0..255
			mov		#0xff, W5
			and		W0, W5, W0
			; Find the font info. A PSV pointer is placed into W5.
			mov		#fontinfo, W5
			mul.uu	W4, #10, W6			; 10 bytes per font info page
			add		W5, W6, W5
			; Copy pointer to font data into W6, so we can address it easily.
			add		W5, #8, W6
			mov		[W6], W6
			; Copy width to W7 and height to W8.
			add		W5, #2, W7
			mov		[W7], W7
			add		W5, #4, W8
			mov		[W8], W8
			; Retrieve mode into W9
			add		W5, #6, W9
			mov		[W9], W9
			; Offset our pointer by mode * height * charnum.
			; TODO: consider pre-calculating width * height in the structure info.
			add		W9, #1, W9			; add 1 to W9
			mul.uu	W7, W9, W10			; multiply height by W9(mode)
			sub		W9, #1, W9			; restore W9
			mul.uu	W10, W0, W10		; multiply W10 by char
			add		W6, W10, W6			; add to pointer
			; Inverted mode or normal mode? If inverted, we want to move the 0x01 
			; mask to W12, otherwise, we want to move the noninverting mask.
			mov		#0x01, W12
			cpseq	W3, W12
			mov		#0x00, W12
			; If it's an 8xN font jump to the 8xN handler, otherwise,
			; jump to the 16xN handler (which is a TODO.)
			cp		W9, #0
			bra		z, _8xN_font
			bra		nz, _16xN_font
			; 8xN font routine
_8xN_font:	; Run HEIGHT times in a DO loop.
			mov		W1, W10				; current X
			mov		W2, W11				; current Y
			sub		W7, #1, W7			; W7 = W7 - 1; do loop runs one more than necessary
			sub		W8, #1, W8			; W8 = W8 - 1; do loop runs one more than necessary
			do		W8, next8Nrow
			; Copy byte to W9.
			mov.b	[W6++], W9
			; Inside this loop, run WIDTH times and output each bit.
			do		W7, next8Ncol
			push	W1					; save the important Wregs
			push	W2					; we'll need them later in this loop
			; Copy the last bit (#7) and display that. Each loop, we shift the
			; bits left, so we progressively read a row and output it.
			rlnc.b	W9, W2				; rotate W9 into W2, copying MSB to LSB.
			and		W2, #1, W2			; mask only LSB
			xor		W2, W12, W2			; invert if necessary
			sl.b	W9, W9				; shift left once every column
			mov		W10, W0
			mov		W11, W1
			call	_drawpix			; call _drawpix, this sets or clears pixel appropriately
			pop		W2					; restore Wregs
			pop		W1
next8Ncol:	add		W10, #1, W10		; increment X.
			; end of X loop here
			mov		W1, W10				; move X back to original position.
next8Nrow:	add		W11, #1, W11		; increment Y.
			; end of Y loop here
			return						; done!
			; 16xN font routine
_16xN_font:	nop		 					; Not yet implemented!!
			return

.global		_drawchar

			; C30 compatible interface for drawchar.
			; Same parameters and function as drawchar.
_drawchar:	; Backs up W8-W11 (as required.)
			push.d	W8			; push W8, W9
			push.d	W10			; push W10, W11
			call	drawchar
			pop.d	W10			; restore W10, W11
			pop.d	W8			; restore W8, W9
			return

			; Draw a null-terminated single line ASCII string at an x,y position.
			; W0 (pointer)		pointer to string
			; W1 (x)			top left x of string
			; W2 (y)			top left y of string
			; W3 (mode)			fill mode
			; W4 (font)			font number
			; W5 (xs)			horizontal spacing
			; Clobbers W0..W11.
drawstr:	; TODO: fill the spacing between characters as well(?)
			; Find the font info. A PSV pointer is placed into W5.
			push	W5
			mov		#fontinfo, W5
			mul.uu	W4, #10, W6			; 10 bytes per font info page
			add		W5, W6, W5
			; Copy width to W7.
			add		W5, #2, W7
			mov		[W7], W7
			pop		W5
			add		W7, W5, W7
			; Current X in W6.
			mov		W1, W6
			; Run in a loop until [W0] = 0x00.
			; Each iteration, place a character.
charloop:	push	W0					; save W0
			push	W3					; save W3
			push.d	W4					; save W4, W5
			push.d	W6					; save W6, W7
			mov		W6, W1
			mov.b	[W0], W0
			call	drawchar			; draw the character
			pop.d	W6					; restore, as above, in reverse
			pop.d	W4
			pop		W3
			pop		W0
			add		W6, W7, W6			; add width to W6
			add		W0, #1, W0			; increment pointer
			cp0.b	[W0]
			bra		nz, charloop
			;bra		charloop
			return

.global		_drawstr

			; C30 compatible interface for drawstr.
			; Same parameters and function as drawstr.
_drawstr:	; Backs up W8-W11 (as required.)
			push.d	W8			; push W8, W9
			push.d	W10			; push W10, W11
			call	drawstr
			pop.d	W10			; restore W10, W11
			pop.d	W8			; restore W8, W9
			return

			; Draw a filled rectangle.
			; W0 = x
			; W1 = y
			; W2 = width
			; W3 = height
			; W4 = mode (0, 1 or 2 for clear, set or toggle)
dfrect:		; Clobbers W0..W12.
			; TODO: For now, this works by drawing vertical lines with the
			;       optimised vertical line writer.
			;       
			;       Consider horizontal lines, and adaptive behaviour; that
			;       is, drawing horizontal lines for long rectangles and 
			;       vertical lines for tall rectangles. But, what to do for
			;		squares? Hmm.
			
			; Calculate x1(W2) and y1(W3) for a rectangle.
			; This is easily calculated from width and height.
			add		W0, W2, W2		; x1 = x + width
			add		W1, W3, W3		; y1 = y + height
			; Run a DO loop from x = x0 to x = x1; DO count in W5 = x1(W2) - x0(W0).
			; Present x in x0, increment per column.
			sub		W2, W0, W5
			do		W5, nextcol
			; Save important Wregs.
			push.d	W0
			push.d	W2
			push	W4
			; Hmm, turns out we need to shift all these down...
			; FUTURE: perhaps move these out of the loop somehow.
			mov		W3, W2
			mov		W4, W3
			; W0 = x, W1 = y0, W2 = y1, W3 = mode
			call	dvline
			; Restore Wregs.
			pop		W4
			pop.d	W2
			pop.d	W0
			add		W0, #1, W0
nextcol:	nop
			return

.global		_dfrect

_dfrect:	; C30 interface for dfrect.
			; Pushes important Wregs W8-W12.
			push.d	W8			; push W8, W9
			push.d	W10			; push W10, W11
			push	W12			; push W12
			call	dfrect
			pop		W12			; pop W12
			pop.d	W10			; pop W11, W10
			pop.d	W8			; pop W9, W8
			return

.global		_textsize
		
			; Calculate the character size for a fixed font.
			; W0 = font number
			; W1 = ptr to store info in
_textsize:	; Clobbers W0..W4.
			; Find the font info. A PSV pointer is placed into W5.
			mov		#fontinfo, W2
			mul.uu	W0, #10, W4			; 10 bytes per font info page
			add		W2, W0, W2
			; Copy width to W1 and height to W2.
			add		W2, #2, W3
			mov		[W3], W3
			add		W2, #4, W4
			mov		[W4], W4
			; Move W3 to [W1], W4 to [W1+2].
			mov		W3, [W1]
			mov		W4, [++W1]
			return

			; Sharp Pixel Demo.
spdemo:		; Run it to find out what it does...
			; Iterate over each pixel.
			mov		#0, W8				; X ptr
			mov		#0, W9				; Y ptr
			do		#255, xend
			add		W8, #1, W8			; increment x	
			mov		#0, W9				; zero y
			do		#191, yend			; loop y
			add		W9, #1, W9			; increment y
			; Test the pixel. _BDRAW is used. Result in W0.
			mov		W8, W0
			mov		W9, W1
			call	_testpix
			; If pixel is off, then handle the next pixel.
			cp		W0, #1
			bra		nz, yend
			; Set neighbours.
			mov		W8, W0
			mov		W9, W1
			call	togneigh
			mov		W8, W0
			mov		W9, W1
			call	_clrpix
			nop
yend:		nop
xend:		nop

.end
