#ifndef pit_h
#define pit_h

#include "MKL46Z4.h"
#include "slcd.h"


extern volatile uint16_t random;

void PITInit(void);
uint8_t Random(void);
#endif
