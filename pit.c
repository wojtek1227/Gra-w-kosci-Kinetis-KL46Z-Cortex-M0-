#include "pit.h"
#include "slcd.h"

void PIT_IRQHandler(void)
{
	//kosc+=1;
	PIT->CHANNEL[0].TFLG |= PIT_TFLG_TIF_MASK;
}

void PITInit(void)
{
	SIM->SCGC6 |= SIM_SCGC6_PIT_MASK;
	
	//turn on PIT
	PIT->MCR = 0x00;
	PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TIE_MASK | PIT_TCTRL_TEN_MASK;
	NVIC_ClearPendingIRQ(PIT_IRQn);
	NVIC_EnableIRQ(PIT_IRQn);
}
