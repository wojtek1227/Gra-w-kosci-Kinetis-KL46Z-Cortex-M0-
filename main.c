// Author: Kopel, Caputa
// Date: 15.01.2016

#include "MKL46Z4.h"
#include "slcd.h"
#include "pit.h"
#include "buttons.h"
#include "leds.h"
#include "game.h"

volatile uint16_t random;

volatile player * current_player;

int main(void)
{
	volatile player Players[NUMBEROFPLAYERS];
	Players[0].ledOn = redLEDOn;
	Players[0].ledOff = ledsOff;
	Players[1].ledOn = greenLEDOn;
	Players[1].ledOff = ledsOff;
	slcdInitialize();
	ledsInit();
	PITInit();
	buttonsInit();

	Game(Players);

	//slcdDotsOff();
	while(1)
	{
		//slcdDisplay(current_player->iterator,10);
		//slcdDisplay((uint16_t)ReadPIT,10);
	}
}

