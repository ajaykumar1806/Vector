//adc.c

#include <lpc21xx.h>
#include "types.h"
#include "pin_connect_block.h"
#include "pin_func_defines.h"
#include "adc_defines.h"

void init_ADC(void) {
	//CFG ADCR SFR
	ADCR |= ((1<<PDN_BIT) | (CLKDIV << CLKDIV_BITS));
	//CFG P0.27 PIN AS ANALOG INPUT PIN ie.. (AINO)
	cfgportpinfunc(0,27,PIN_FUNC2);
}

void read_ADC(u32 chno,u32 *adcDval,f32 *eAR) {
	//clear any previous channel selection
	ADCR &= ~(255);
	//update req channel selection
	//stae=rt analog sampling & conversion
	ADCR |= 1<<chno | 1<<ADC_START_BIT ;
	delayUs(3);
	while(((ADDR >> DONE_BIT) & 1) == 0);
	ADCR &= (1 << ADC_START_BIT); // to off adc
	*adcDval = (ADDR >> RESULT_BITS) & 1023 ;
	*eAR = (*adcDval * (3.3/1023)); //3.3 is ref and 1023 is resolution bits
}