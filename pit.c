#include "pit.h"
#include "slcd.h"

void PIT_IRQHandler(void)
{
	//kosc+=1;
	//kosc = kosc % 6 + 1;
	//slcdDisplay(kosc,10);
	PIT->CHANNEL[0].TFLG |= PIT_TFLG_TIF_MASK;
}

void PITInit(void)
{
	SIM->SCGC6 |= SIM_SCGC6_PIT_MASK;
	
	//turn on PIT
	PIT->MCR = 0x00;
	PIT->CHANNEL[0].LDVAL = PIT_LDVAL_TSV(10000);
	PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TIE_MASK | PIT_TCTRL_TEN_MASK;
	NVIC_ClearPendingIRQ(PIT_IRQn);
	NVIC_EnableIRQ(PIT_IRQn);
}
