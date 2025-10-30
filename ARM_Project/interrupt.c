#include <lpc21xx.h>
#include "types.h"
#include "defines.h"
#include "lcd.h"
#include "lcd_defines.h"
#include "pin_connect_block.h"
#include "delay.h"
#include "kpm.h"
#include "interrupt.h"
#include "interrupt_defines.h"
#include "rtc.h"
#include "rtc_defines.h"

s8 *menu_options[] = {
		" ****MENU****  ",
		"1.EDT_RTC_INF  ",
		"2.SET_ALM_TM   ",
		"3.EXIT         "
};

extern s32 eint_request;

void eint1_isr(void)__irq {
	eint_request = 1;
	EXTINT = 1 << 1;
	VICVectAddr = 0;
}


void interrupt_configuration(void) {
	CfgPortPinFunc(0,3,EINT0_0_3);
//	VICIntSelect = 0; //{default is always 0 and hence it acts for irq interrupt)
	VICIntEnable = 1 << EINT0_VIC_CHNO;
	VICVectCntl0 = 1 << 5 | EINT0_VIC_CHNO;
	VICVectAddr0 = (u32)eint1_isr;
//	VICVectAddr; //(Not required bcoz it will be internally done)
//	EXTINT = 1 << 0; //(0 bcoz we are using EINT0)
//	EXTMODE = 1 << 0;
//	EXTPOLAR = 0 << 0;
}

void menu_display(s32 *alarm_hour,s32 *alarm_min) {
	s32 flag = 1;
	u8 kpm_key;
	s32 index = 0;
	CmdLCD(CLEAR_LCD);
	while (flag) {
		if(index == 0) {
			StrLCD(menu_options[index++]);
			CmdLCD(GOTO_LINE2_POS0);
			StrLCD(menu_options[index]);
			WriteLCD(1);
		}

		kpm_key = KeyScan();
		loop:switch(kpm_key) {
			case '+':
				// Scroll Down
				CmdLCD(CLEAR_LCD);
				while(kpm_key == '+') {
					index = 2;
					StrLCD(menu_options[index++]);
					WriteLCD(0);
					CmdLCD(GOTO_LINE2_POS0);
					StrLCD(menu_options[index]);
					kpm_key = KeyScan();
					goto loop;
				}
				break;
			case '-':
				// Scroll Up
				CmdLCD(CLEAR_LCD);
				while(kpm_key == '-') {
					index = 0;
					CmdLCD(CLEAR_LCD);
					StrLCD(menu_options[index++]);
					CmdLCD(GOTO_LINE2_POS0);
					StrLCD(menu_options[index]);
					WriteLCD(1);
					kpm_key = KeyScan();
					if(kpm_key != '-')
					goto loop;
				}
			case '1':
				if(index <= 1) {
					edit_rtc_info();
					kpm_key = '-';
					goto loop;
				}
				break;
			case '2':
				if(index >= 2 && index <= 3) {
					set_alarm_time(alarm_hour,alarm_min);
					kpm_key = '+';
					goto loop;
				}
				break;
			case '3':
				if(index >= 2 && index <= 3) {
					eint_request = 0;
					flag = 0;
				}
				break;
			default:
				break;
			}
	}
	CmdLCD(CLEAR_LCD);
}
