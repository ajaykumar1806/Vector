#include <lpc21xx.h>
#define opin 7
int main() {
	//IODIR0 |= 1<<opin;
	while(1) {
		int delay1 = 100*12000;
		int delay2 = 100*12000;
		IOSET0 = 1<<opin;
		while(delay1--);
		IOCLR0 = 1<<opin;
		while(delay2--);
	}
}
