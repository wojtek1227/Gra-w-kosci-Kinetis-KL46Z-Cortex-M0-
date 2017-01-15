#ifndef leds_h
#define leds_h

#include "MKL46Z4.h"


#define ledGreen 0
#define ledRed 1

const static uint32_t led_mask[] = {1UL<<5, 1UL<<29};


void ledsInit(void);
void redLEDOn(void);
void greenLEDOn(void);
void ledsOff(void);
void ledsOn(void);
void redLEDToggle(void);
void greenLEDToggle(void);

#endif
