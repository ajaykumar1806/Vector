#include <lpc21xx.h>
#include "types.h"
#include "rtc.h"
#include "lcd.h"
#include "interrupt.h"
#include "interrupt_defines.h"
#include "kpm.h"
#include "adc.h"
#include "defines.h"
#include "rtc_defines.h"

s32 hour,min,sec,date,month,year,day,alarm_hour = -1,alarm_min = -1;
u32 temperature,chno = 0; //default is also 0
f32 eAR;
// Main function
int main()
{
	// Initialize RTC 
	Init_RTC();
	// Initialize the LCD
	Init_LCD();
	CGRAM_Symbols();
	//Initialize the KPM
	Init_KPM();
	//Initialize ADC
	Init_ADC();
	// Initialize the Interrupt
	switches_configuration();
	interrupt_configuration();
	
	// Set the initial time (hours, minutes, seconds)
	SetRTCTimeInfo(16,14,50);
	SetRTCDateInfo(22,10,2025);
	SetRTCDay(3);
	
	while (1) 
	{
		// Get and display the current time on LCD
		GetRTCTimeInfo(&hour,&min,&sec);
		GetRTCDay(&day);
		GetRTCDateInfo(&date,&month,&year);
//		DisplayRTCTime(HOUR,MIN,SEC);
//		DisplayRTCDay(DOW);
//		DisplayRTCDate(DOM,MONTH,YEAR);
		DisplayRTCTime(hour,min,sec);
		DisplayRTCDay(day);
		DisplayRTCDate(date,month,year);
		Read_ADC(chno,&temperature,&eAR);
		Display_temperature(temperature);
		if (((IOPIN0 >> EINT_REQUEST) & 1)) {
			menu_display(&alarm_hour,&alarm_min);
		}
		if(HOUR == alarm_hour && MIN == alarm_min && READBIT(IOPIN0,ALARM_STOP_SWAL)) {
			ring_alarm(alarm_hour,alarm_min);
		}
	}
}
