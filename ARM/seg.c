//seg.c
#include "types.h"
#include "arduino_api.h"
#include "arduino_api_defines.h"
#include "seg_defines.h"
#include "delays.h"
#include <LPC21xx.h>
#include "defines.h"

u8 segLUT[]=
{
	0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90
};

u32 dp1=0xFF,dp2=0xFF,dp3=0xFF;

void init_7seg(void)
{
	u32 i;
  //cfg p0.8 to p0.15 as gpio output pins
	for(i=0;i<8;i++)
	  setPinMode(CA7_SEGA_PIN+i,OUTPUT);
}

void dispSeg(u32 n)
{
	u32 j;
	for(j=0;j<8;j++)
	{
	 digitalWrite(CA7_SEGA_PIN+j,((segLUT[n]>>j)&1));
	}	
}

void init_2_mux_7segs(void)
{
	//cfg p0.8 to p0.17 as gpio output pins
	IODIR0|=0xFF<<CA7SEG_2_MUX|1<<DSEL1|1<<DSEL2;
}

void disp_2_mux_segs(u32 n)
{
	//write to data pins
	WRITEBYTE(IOPIN0,CA7SEG_2_MUX,segLUT[n/10]);
	//turn on digit 1
	IOSET0 = 1<<DSEL1;
	//switching /on time
	delayMs(1);
	//turn off digit 1
	IOCLR0 = 1<<DSEL1;
	
	//write to data pins
	WRITEBYTE(IOPIN0,CA7SEG_2_MUX,segLUT[n%10]);
	//turn on digit 2
	IOSET0 = 1<<DSEL2;
	//switching /on time
	delayMs(1);
	//turn off digit 2
	IOCLR0 = 1<<DSEL2;
}	
void init_4_mux_7segs(void)
{
	//cfg p0.8 to p0.19 as gpio output pins
	IODIR0|=0xFF<<CA7SEG_2_MUX|
	        1<<DSEL1|1<<DSEL2|1<<DSEL3|1<<DSEL4;
}

void disp_4_mux_segs(u32 n)
{
	//write to data pins
	WRITEBYTE(IOPIN0,CA7SEG_4_MUX,(segLUT[n/1000]&dp1));
	//turn on digit 1
	IOSET0 = 1<<DSEL1;
	//switching /on time
	delayMs(1);
	//turn off digit 1
	IOCLR0 = 1<<DSEL1;
	
	//write to data pins
	WRITEBYTE(IOPIN0,CA7SEG_4_MUX,(segLUT[(n/100)%10]&dp2));
	//turn on digit 2
	IOSET0 = 1<<DSEL2;
	//switching /on time
	delayMs(1);
	//turn off digit 2
	IOCLR0 = 1<<DSEL2;
	
	//write to data pins
	WRITEBYTE(IOPIN0,CA7SEG_4_MUX,(segLUT[(n%100)/10]&dp3));
	//turn on digit 3
	IOSET0 = 1<<DSEL3;
	//switching /on time
	delayMs(1);
	//turn off digit 3
	IOCLR0 = 1<<DSEL3;
	
	//write to data pins
	WRITEBYTE(IOPIN0,CA7SEG_4_MUX,segLUT[n%10]);
	//turn on digit 4
	IOSET0 = 1<<DSEL4;
	//switching /on time
	delayMs(1);
	//turn off digit 4
	IOCLR0 = 1<<DSEL4;
}

void dispf_4_mux_segs(f32 fn)
{
	u32 n;
	if(fn<10.0)
	{
		dp1=0x7F;
		n=fn*1000;
	}
	else if(fn>=10.0  && fn<100.0)
	{
		dp2=0x7F;
		n=fn*100;
	}
	else if(fn>=100.0 && fn<1000.0)
	{
		dp3=0x7F;
		n=fn*10;
	}
	disp_4_mux_segs(n);
	dp1=dp2=dp3=0xFF;
}

