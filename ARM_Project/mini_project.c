#include <lpc21xx.h>
#include "types.h"
#include "rtc.h"
#include "lcd.h"
#include "interrupt.h"
#include "interrupt_defines.h"
#include "kpm.h"

s32 hour,min,sec,date,month,year,day,alarm_hour_set = -1,alarm_min_set = -1;

// Main function
int main()
{
	// Initialize RTC 
	Init_RTC();
	// Initialize the LCD
	Init_LCD();
	//Initialize the KPM
	Init_KPM();
	// Initialize the Interrupt
	switches_configuration();
	interrupt_configuration();
	
	// Set the initial time (hours, minutes, seconds)
	SetRTCTimeInfo(14,47,50);
	SetRTCDateInfo(21,10,2025);
	SetRTCDay(2);
	
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
		menu_display(&alarm_hour_set,&alarm_min_set);
		ring_alarm(&alarm_hour_set,&alarm_min_set,HOUR,MIN);
	}
}
