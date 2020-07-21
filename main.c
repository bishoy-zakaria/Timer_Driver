/*
 * Timer.c
 *
 * Created: 7/17/2020 7:10:35 PM
 * Author : Bishoy
 */ 

#include "Timer.h"
#include "Timer_Cfg.h"
#include "LED.h"
#define F_CPU 16000000
#include <util/delay.h>

int main(void)
{
    DDRB = 0b00001000;
	timer_init();
	while (1)
	{
   static uint8 counter=0;
   PWM_Value(counter);
   timer_start();
   _delay_ms(50);
   timer0_stop();
   counter++;
   if (counter==100)
    {
	   while(counter>0)
	   { 
		   counter--;
		   PWM_Value(counter);
		   timer_start();
		   _delay_ms(100);
		   timer0_stop();
		  
		   
       }
   
    }
		
    }
}

