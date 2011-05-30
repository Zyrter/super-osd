/**
 * Super OSD, software revision 3
 * Copyright (C) 2010 Thomas Oldbury
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include <p33fj128gp802.h>
#include <uart.h>
#include <pps.h>

#include "useful.h"
#include "interface.h"

// Private DMA structures.
char uart_buffA[UART_BUFFSZ] __attribute__((space(dma)));
char uart_buffB[UART_BUFFSZ] __attribute__((space(dma)));
char uart_buff_done[UART_BUFFSZ];

// for UART/DMA
int UART_RX_DMA_last;

/*
 * This code handles the external interface over a very high
 * speed UART connection. It manages the UART receive and 
 * transmit buffer, DMA, the hardware API as well as parsing
 * the received commands. 
 */

/**
 * interface_init_uart: Initialize UART module including
 * PPS. Does not set baud rate and module must be enabled
 * after this function is run.
 */
void interface_init_uart()
{
	// Setup PPS (use pps.h macros.)
	PPSUnLock;
	iPPSInput(IN_FN_PPS_U1RX, IN_PIN_PPS_RP9);
	iPPSInput(IN_FN_PPS_U1CTS, 31); // always clear to send to PIC24F (tie internally to Vss)
	iPPSOutput(OUT_PIN_PPS_RP11, OUT_FN_PPS_U1RTS);
	iPPSOutput(OUT_PIN_PPS_RP8, OUT_FN_PPS_U1TX);
	// Setup UART1.
	U1MODEbits.UARTEN = 0;							// Disable UART1 for now
	U1MODEbits.USIDL = 0;							// Don't stop in idle mode(?)
	U1MODEbits.IREN = 0;							// Disable IrDA mode
	U1MODEbits.RTSMD = 0;							// Flow control mode - automatically control U1RTS
	U1MODEbits.UEN = 0b10;							// UxTX, UxRX and UxRTS pins are enabled and used; UxCTS pin is controlled by port latches
	U1MODEbits.WAKE = 0;							// Disable wake-up
	U1MODEbits.LPBACK = 0;						    // Disable loop-back
	//U1MODEbits.LPBACK = 1;						    // Enable loop-back (testing)
	U1MODEbits.ABAUD = 0;							// Disable auto-baud for now
	U1MODEbits.URXINV = 0;							// Disable receive invert
	U1MODEbits.BRGH = 1;							// High-speed mode
	U1MODEbits.PDSEL = 0b00;						// 8-bit, no parity (consider odd/even parity?)
	U1MODEbits.STSEL = 0;							// 1 stop bit
	U1STAbits.UTXEN = 0;							// Disable transmit (for now)
	// Setup interrupts (required for DMA)
	U1STAbits.URXISEL = 0b00;						// "Interrupt" on each byte
	// Disable interrupts on the CPU side, so the processor doesn't get interfered with.
	IEC0bits.U1RXIE = 0; 
	IPC2bits.U1RXIP = 0; 
	// Setup DMA for RX side.
	DMA5CONbits.CHEN = 0;							// Disable channel for now
	DMA5CONbits.SIZE = 1;							// Byte transfers
	DMA5CONbits.DIR = 0;							// Read from peripheral to DPSRAM
	DMA5CONbits.HALF = 0;							// Don't interrupt on half written
	DMA5CONbits.NULLW = 0;							// Don't do a null write
	DMA5CONbits.AMODE = 0b00;						// Peripheral indirect addressing mode, post-increment
	DMA5CONbits.MODE = 0b10;						// Continuous, ping pong buffer
	DMA5REQbits.FORCE = 0;							// Don't force transfer yet (peripheral control only)
	DMA5REQbits.IRQSEL = 0b0001011;					// UART1RX IRQ
	DMA5STA = __builtin_dmaoffset(uart_buffA);		// Buffer A
	DMA5STB = __builtin_dmaoffset(uart_buffB);		// Buffer B
	DMA5CNT = UART_BUFFSZ - 1;						// Maximum UART_BUFFSZ bytes per transaction
	DMA5PAD = (volatile unsigned int) &U1RXREG;		// DMA peripheral address
	U1MODEbits.UARTEN = 1;							// Enable UART
	DMA5CONbits.CHEN = 1;							// Turn channel on
	// Set channel tracker up.
	UART_RX_DMA_last = DMACS1bits.PPST5;
	// Kick-start the first transfer.
	DMA5REQbits.FORCE = 1;
	// Lock PPS & OSCCON.
	PPSLock;
}

/**
 * interface_test_uart: Loop n times (a long int), repeating the
 * character 'U' on the UART tx pin.
 */
void interface_test_uart(long int n)
{
	// Enable transmit.
	U1STAbits.UTXEN = 1;
	while(n--)
	{
		while(BusyUART1());
		WriteUART1('U');
	}
}

/**
 * interface_check_uart: Check UART (this is run in a loop) for 
 * new data. We need to investigate making this faster in future.
 */
void interface_check_uart()
{
	char *ptr, nullread;
	int i = 0;
	if(DMA5CONbits.CHEN == 0)
	{
		con_puts("Got data", 0);
		if(DMACS1bits.PPST5 == 0)
			ptr = uart_buffA;
		else
			ptr = uart_buffB;
		// Copy the data.
		for(i = 0; i < UART_BUFFSZ; i++)
			uart_buff_done[i] = ptr[i];
		// Handle the data. For now, we just print it on the console.
		con_puts(uart_buff_done, 0);
		// Force 1 transfer.
		//DMA5REQbits.FORCE = 1;
		// Enable the channel again.
		DMA5CONbits.CHEN = 1;
		// Clear the OERR bit.
		U1STAbits.OERR = 0;
	}
	else
	{
		//con_puts("No data", 0);
	}
}

/**
 * interface_set_baudrate: Set the baudrate or return an
 * error if the baud rate cannot be set (for example, it is
 * unsupported.)
 */
unsigned int interface_set_baudrate(long int baudrate)
{
	// Fcy = 36.35 MHz, BRGH = 1.
	unsigned int brg;
	// Generated using uart-brg.py - a simple Python script to calculate all of these BRGs.
    switch(baudrate) // Fcy: 36.850 MHz
    {
        case 9600: brg = 959; break; 	// actual rate 9596 (error -4/0.04%) 
        case 19200: brg = 479; break; 	// actual rate 19192 (error -8/0.04%) 
        case 28800: brg = 319; break; 	// actual rate 28789 (error -11/0.04%) 
        case 38400: brg = 239; break; 	// actual rate 38385 (error -15/0.04%) 
        case 57600: brg = 159; break; 	// actual rate 57578 (error -22/0.04%) 
        case 115200: brg = 79; break; 	// actual rate 115156 (error -44/0.04%) 
        case 128000: brg = 71; break; 	// actual rate 127951 (error -49/0.04%) 
        case 153600: brg = 59; break; 	// actual rate 153541 (error -59/0.04%) 
        case 230400: brg = 39; break; 	// actual rate 230312 (error -88/0.04%) 
        case 256000: brg = 35; break; 	// actual rate 255902 (error -98/0.04%) 
        case 460800: brg = 19; break; 	// actual rate 460625 (error -175/0.04%) 
        case 921600: brg = 9; break; 	// actual rate 921250 (error -350/0.04%) 
        case 1843200: brg = 4; break; 	// actual rate 1842500 (error -700/0.04%) 
        default: return -1; break; 
    }
	U1BRG = brg;
	return brg;
}
