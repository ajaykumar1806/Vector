#include <lpc21xx.h>
#include "types.h"
#include "delays.h"
#define SW_AL 4
#define LEDS_4_AH 8
main() {
	IODIR0 |= (0XF << LEDS_4_AH);
	u32 count = 0,delay = 500;
	while(