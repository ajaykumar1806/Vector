/* Write an ECP to display below mentioned patterns on 8-led’s (4-active high led’s and
4-active low led’s)
a. Switch ON one by one led from left to right at the rate of 1 second
b. Switch ON one by one led from right to left at the rate of 1 second
*/

#include <lpc21xx.h>
#include "types.h"
#include "delays.h"
#define AL_LED_START 8 //P0.8
#define AH_LED_START 12 //p0.12
#define SW_AL 4 
#define SW_AH 5
main() {
	while(1) {
		u32 i;
		for(i = 0;i<8;i++) {
			IODIR0 |= 1 << AL_LED_START+i;
		}
		// for active low led's
		for(i = 0;i<=3;i++) {
			IOSET0 = 1<<AL_LED_START+i;
			delayMs(200);
			IOCLR0 = 1<<AL_LED_START+i;
			delayMs(800);
		}
		
		// for active high led's
		for(i = 0;i<=3;i++) {
			IOSET0 = 1 << AH_LED_START+i;
		}
		delayS(1);
		for(i = 0;i<=3;i++) {
			IOCLR0 = 1<<AH_LED_START+i;
			delayMs(200);
			IOSET0 = 1<<AH_LED_START+i;
			delayMs(800);
		}
		for(i = 0;i<=3;i++) {
			IOCLR0 = 1 << AH_LED_START+i;
		}
	}
}
