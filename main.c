/*
 * Timer.c
 *
 * Created: 7/17/2020 7:10:35 PM
 * Author : Bishoy
 */ 

#include "Timer.h"
#include "Timer_Cfg.h"
#include "avr/interrupt.h"

extern uint32 num_over_flow;
extern uint8  init_value;
volatile uint8 count=0;

int main(void)
{
    DDRC = 0b10000000;
	
	timer_init();
	timer_delay(500);
	timer_start();
	
    while (1) 
    {
    }
}

ISR (TIMER0_OVF_vect)
{
	count++;
	while (count == num_over_flow)
	{
		Toggle_BIT(PORTC,7);
		TCNT0 = init_value;
		count=0;
	}
	
	
}

ISR(TIMER0_COMP_vect)
{
	    count++;
		while (count == num_over_flow)
		{
			Toggle_BIT(PORTC,7);
			OCR0 = init_value;
			count=0;
		}
		
}