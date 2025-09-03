#include "types.h"
void delayUs(u32 Us) {
	Us*=12;
	while(Us) {
		Us--;
	}
}

void delayMs(u32 Ms) {
	Ms = Ms*12*1000;
	while(Ms) {
		Ms--;
	}
}

void delayS(u32 S) {
	S = S*12*1000*1000;
	while(S) {
		S--;
	}
}
