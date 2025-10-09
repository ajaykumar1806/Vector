#include <lpc21xx.h>
#define OUT_PORT 8
#define LED_START 8

void delayS(unsigned int dly) {
        dly *= 12000000;
        while(dly--);
}

int main() {
        int i;
        for(i = 0; i < 8; i++) {
                IODIR0 |= 1 << (OUT_PORT + i);
        }
        while(1) {
                for(i = 0; i < 4; i++) {
                        IOPIN0 |= 1 << (LED_START + i);
                }
                delayS(1);
                for(i = 0; i < 8; i++) {
                        if(i < 4) {
                                IOPIN0 &= ~(1 << (LED_START + i));
                                delayS(1);
                                IOPIN0 |= 1 << (LED_START + i);
                        }
                        else {
                                IOPIN0 |= 1 << (LED_START + i);
                                delayS(1);
                                IOPIN0 &= ~(1 << (LED_START + i));
                        }
                }
                delayS(1);
                for(i = 7; i >= 0; i--) {
                        if(i < 4) {
                                IOPIN0 &= ~(1 << (LED_START + i));
                                delayS(1);
                                IOPIN0 |= 1 << (LED_START + i);
                        }
                        else if(i >= 4 && i <= 7) {
                                IOPIN0 |= 1 << (LED_START + i);
                                delayS(1);
                                IOPIN0 &= ~(1 << (LED_START + i));
                        }
                }
        }
}
