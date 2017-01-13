#ifndef buttons_h
#define buttons_h

#include "MKL46Z4.h"
#define button3 0
#define button1 1
#define SW1_PIN 3
#define SW3_PIN 12

const static uint32_t button_mask[] = {1UL << SW1_PIN, 1UL << SW3_PIN};

void  buttonsInit(void);
int32_t button1Read(void);
int32_t button3Read(void);

#endif
