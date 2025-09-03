//show_bin_eq1.c
#include <lpc21xx.h>
#include "types.h"
#include "delays.h"
#include "arduino_api_defines.h"
#include "arduino_api.h"
#define LED_AL_START 8 //p0.8
#define SW_AL 4 //p0.4
u32 seed = 0;
int main() {
	u32 num,i;
	//configure the pins p0.8 to p0.15 as output
	for(i = 8;i<=15;i++) {
		setPinMode(i,OUTPUT);
	}
	srand(seed++);
	while(1) {
		if(digitalRead(SW_AL)) {
			for(i = 8;i<=15;i++) {
				digitalWrite(i,0);
			}
		}
		else {
			delayMs(100);
			num = (rand() % 255) + 1;
			for(i = 8;i<=15;i++) {
				digitalWrite(i,0);
			}
			for(i = 8;i<=15;i++) {
				digitalWrite(i,1);
			}
		}
	}
}
