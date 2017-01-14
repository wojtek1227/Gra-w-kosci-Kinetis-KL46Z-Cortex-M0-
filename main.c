#include "MKL46Z4.h"
#include "slcd.h"
#include "pit.h"
#include "buttons.h"
#include "leds.h"

//volatile uint16_t kosc;

int main(void)
{
	//kosc = 0;
	slcdInitialize();
	ledsInit();
	redLEDOn();
	PITInit();
	buttonsInit();
	slcdDisplay(1234,10);
	while(1)
	{
		
		//slcdDisplay((uint16_t)ReadPIT,10);
	}
}

