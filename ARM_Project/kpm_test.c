#include <lpc21xx.h>
#include "kpm.h"
#include "lcd.h"
#include "lcd_defines.h"

main() {
	Init_LCD();
	Init_KPM();
	while(1){
		u8 key = KeyScan();
		CmdLCD(GOTO_LINE1_POS0);
		CharLCD(key);
		}
}
