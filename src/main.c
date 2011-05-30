/**
 * OSD entry point.
 */

#include "osd.h"
#include "demo.h"

/* Configuration bits. */
// Fast RC oscillator with divide & PLL, two-speed oscillator startup disabled
_FOSCSEL(FNOSC_FRCPLL & IESO_OFF);
// No clock monitor/failsafe, remappable I/O, clock out enabled, primary oscillator disabled.
_FOSC(FCKSM_CSDCMD & IOL1WAY_ON & OSCIOFNC_OFF & POSCMD_NONE);
// Watchdog enabled.
_FWDT(FWDTEN_OFF);
// JTAG off, ICD using PGD1/PGC1.
_FICD(JTAGEN_OFF & ICS_PGD1);

// Buffer; some other files use this.
char buff[50];
// Temporary store. Some files use this.
int tmp_swap;

int main()
{
	BDISP = 0;
	BDRAW = 0;
	fill_mem(0x0000);
	fill_mem(0xffff);
	BDISP = 0;
	BDRAW = 1;
	hud_init();
	while(1)
	{
		hud_rc_plane_single_frame();
	//	demo();
	}
	return 0;
}