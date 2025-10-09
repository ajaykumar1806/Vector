//Flash an LED connected to any port line at the rate of 1 second for 10 times and stop.
#include <lpc21xx.h>
#include "types.h"
#include "delays.h"
#define OUT 4
main() {
	u32 count = 0;
	IODIR0 |= 1<<OUT;
	while(1) {
		if(count < 10) {
			IOSET0 = 1<<OUT;
			delayMs(500);
			IOCLR0 = 1<<OUT;
			delayMs(500);
			count++;
		}
	}
}
