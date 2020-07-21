/*
 * LED.c
 *
 * Created: 7/18/2020 10:38:56 AM
 *  Author: 20112
 */ 

#include "LED.h"

void LED_Toggel (void)
{
	Toggle_BIT(PORTC,7);
}