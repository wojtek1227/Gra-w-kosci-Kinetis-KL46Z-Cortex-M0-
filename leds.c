#include "leds.h"

void ledsInit(void)
{
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK | SIM_SCGC5_PORTE_MASK;
	PORTD->PCR[5] |= PORT_PCR_MUX(1UL);
	PORTE->PCR[29] |= PORT_PCR_MUX(1UL);
	PTD->PDDR |= led_mask[ledGreen];
	PTE->PDDR |= led_mask[ledRed];
	
	PTD->PSOR |= led_mask[ledGreen];
	PTE->PSOR |= led_mask[ledRed];
}

void redLEDOn(void)
{
	PTE->PCOR |= led_mask[ledRed];
}

void greenLEDOn(void)
{
	PTD->PCOR |= led_mask[ledGreen];
}

void ledsOff(void)
{
	PTD->PSOR |= led_mask[ledGreen];
	PTE->PSOR |= led_mask[ledRed];
}

void ledsOn(void)
{
	PTD->PCOR |= led_mask[ledGreen];
	PTE->PCOR |= led_mask[ledRed];
}

void redLEDToggle(void)
{
	PTE->PTOR |= led_mask[ledRed];
}

void greenLEDToggle(void)
{
	PTD->PTOR |= led_mask[ledGreen];
}
