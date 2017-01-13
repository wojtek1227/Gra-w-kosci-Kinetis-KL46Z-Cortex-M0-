#include "buttons.h"
#include "leds.h"

void PORTC_PORTD_IRQHandler(void)
{
	if (button1Read())
	{
		redLEDToggle();
	}
	if (button3Read())
	{
		greenLEDToggle();
	}
	PORTC->PCR[SW1_PIN] |= PORT_PCR_ISF_MASK;
	PORTC->PCR[SW3_PIN] |= PORT_PCR_ISF_MASK;
}



void buttonsInit(void)
{
	SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;
	PORTC->PCR[3] |= PORT_PCR_MUX(1);
	PORTC->PCR[12] |= PORT_PCR_MUX(1);
	
	PTC->PDDR &= ~button_mask[button1];
	PTC->PDDR &= ~button_mask[button3];
	PORTC->PCR[SW1_PIN] |= PORT_PCR_PE_MASK | PORT_PCR_PS_MASK | PORT_PCR_IRQC(0xA);
	PORTC->PCR[SW3_PIN] |= PORT_PCR_PE_MASK | PORT_PCR_PS_MASK | PORT_PCR_IRQC(0xA);
	
	NVIC_ClearPendingIRQ(PORTC_PORTD_IRQn);
	NVIC_EnableIRQ(PORTC_PORTD_IRQn);
}

int32_t button1Read(void)
{
	return PTC->PDIR & button_mask[button1];
}

int32_t button3Read(void)
{
	return PTC->PDIR & button_mask[button3];
}
