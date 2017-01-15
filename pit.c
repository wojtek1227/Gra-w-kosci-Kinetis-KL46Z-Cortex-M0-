#include "pit.h"


void PIT_IRQHandler(void)
{
	random += 1;
	random %= 1003; 
	
	PIT->CHANNEL[0].TFLG |= PIT_TFLG_TIF_MASK;
}

void PITInit(void)
{
	//turn on clock
	SIM->SCGC6 |= SIM_SCGC6_PIT_MASK;
	
	//turn on PIT
	PIT->MCR = 0x00;
	PIT->CHANNEL[0].LDVAL = PIT_LDVAL_TSV(1000000);
	PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TIE_MASK | PIT_TCTRL_TEN_MASK;
	//clear random
	random = 0;
	//turn on interrupt
	NVIC_ClearPendingIRQ(PIT_IRQn);
	NVIC_EnableIRQ(PIT_IRQn);
}

uint8_t Random(void)
{
	return (uint8_t)(random % 6 + 1);
}
