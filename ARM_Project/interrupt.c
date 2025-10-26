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
		"MENU           ",
		"1.EDT_RTC_INF  ",
		"2.SET_ALM_TM   ",
		"3.EXIT         "
};

void switches_configuration(void) {
	IODIR0 |= 1 << EINT_REQUEST;
	IOCLR0  = 1 << EINT_REQUEST;
	IODIR0 |= 1 << ALARM_STOP_SWAL;
	IOSET0  = 1 << ALARM_STOP_SWAL;
	IODIR0 |= 1 << ALARM_START_SWAL;
}

void eint1_isr(void)__irq {
	IOSET0 = 1 << EINT_REQUEST;
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

void menu_display(s32 *alarm_hour_set,s32 *alarm_min_set) {
	s32 flag = 1;
	u8 kpm_key;

	if (((IOPIN0 >> EINT_REQUEST) & 1)) {
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
						set_alarm_time(alarm_hour_set,alarm_min_set);
						kpm_key = '+';
						goto loop;
					}
					break;
				case '3':
					if(index >= 2 && index <= 3) {
						IOCLR0 = 1 << EINT_REQUEST;
						flag = 0;
					}
					break;
				default:
					break;
				}
		}
		CmdLCD(CLEAR_LCD);
	} 
	else return;
}

//void menu_display_common_lines(u32 index) {
//	StrLCD(menu_options[index++]);
//	CmdLCD(GOTO_LINE2_POS0);
//	StrLCD(menu_options[index]);
//}

//void menu_display(s32 *alarm_hour_set,s32 *alarm_min_set) {
//	s32 flag = 1;
//	u8 kpm_key;
//	if (((IOPIN0 >> EINT_REQUEST) & 1)) {
//		s32 index = 0;
//		CmdLCD(CLEAR_LCD);
//		while (flag) {
//			if(index == 0) {
//				menu_display_common_lines(index);
//			}
//			kpm_key = KeyScan();
//			loop:switch(kpm_key) {
//							case '+':
//								// Scroll Down
//								CmdLCD(CLEAR_LCD);
//								while(kpm_key == '+') {
//									index = 2;
//									menu_display_common_lines(index);
//									kpm_key = KeyScan();
//									goto loop;
//								}
//								break;
//							case '-':
//								// Scroll Up
//								CmdLCD(CLEAR_LCD);
//								while(kpm_key == '-') {
//									index = 0;
//									CmdLCD(CLEAR_LCD);
//									menu_display_common_lines(index);
//									kpm_key = KeyScan();
//									goto loop;
//								}
//							case '1':
//								if(index <= 1) {
//									edit_rtc_info();
//									kpm_key = '-';
//									goto loop;
//								}
//								break;
//							case '2':
//								if(index >= 2 && index <= 3) {
//									set_alarm_time(alarm_hour_set,alarm_min_set);
//									kpm_key = '+';
//									goto loop;
//								}
//								break;
//							case '3':
//								if(index >= 2 && index <= 3) {
//									IOCLR0 = 1 << EINT_REQUEST;
//									flag = 0;
//								}
//								break;
//							default:
//								break;
//				}
//		}
//		CmdLCD(CLEAR_LCD);
//	} 
//	else return;
//}

