/*
 * Timer.c
 *
 * Created: 7/17/2020 7:12:18 PM
 *  Author: 20112
 */ 
#include "Timer.h"
#include "Timer_Cfg.h"
#include <avr/interrupt.h>
uint32 num_over_flow;
uint8  init_value;
uint32 Compare_Match;
volatile uint8 count=0;
static void (*Timer0_Ptr)(void);

void timer_init(void)
{
	CLR_BIT(TCCR0,7);
	
	#if     Timer_Mode    ==       Normal_Mode
	{
		CLR_BIT(TCCR0,6);
		CLR_BIT(TCCR0,3);
		
		#if interrupt_state  ==    interrupt_Enable 
		{
			SET_BIT(SREG ,7);
			SET_BIT(TIMSK,0);
		}
		#endif
	}
	#elif   Timer_Mode    ==       CTC_Mode
	{
		CLR_BIT(TCCR0,6);
		SET_BIT(TCCR0,3);
		
		#if interrupt_state  ==    interrupt_Enable
		{
			SET_BIT(SREG ,7);
			SET_BIT(TIMSK,1);
		}
		#endif
	}
	
	#elif   Timer_Mode    ==       Fast_PWM_Mode 
	{
		SET_BIT(TCCR0,6);
		SET_BIT(TCCR0,3);
		
		#if   PWM_Mode    ==   PWM_NON_Inverted_Mode
		{
			SET_BIT(TCCR0,5);
			CLR_BIT(TCCR0,4);
		}
		#elif PWM_Mode    ==   PWM_Inverted_Mode
		{
			SET_BIT(TCCR0,5);
			SET_BIT(TCCR0,4);
		}
		#endif
	}
	#elif   Timer_Mode    ==       PWM_Phase_Correct_Mode
	{
		SET_BIT(TCCR0,6);
		CLR_BIT(TCCR0,3);
		
		#if   PWM_Mode    ==   PWM_NON_Inverted_Mode
		{
			SET_BIT(TCCR0,5);
			CLR_BIT(TCCR0,4);
		}
		#elif PWM_Mode    ==   PWM_Inverted_Mode
		{
			SET_BIT(TCCR0,5);
			SET_BIT(TCCR0,4);
		}
		#endif
	}
	#endif
	
}



void timer_start(void)
{
	
	  #if  Timer_CLK     ==       Pres_CLK   
  {
	  SET_BIT(TCCR0,0);
	  CLR_BIT(TCCR0,1);
	  CLR_BIT(TCCR0,2);
  } 
  #elif  Timer_CLK     ==       Pres_CLK_8 
  {
	  CLR_BIT(TCCR0,0);
	  SET_BIT(TCCR0,1);
	  CLR_BIT(TCCR0,2);
  }
  #elif  Timer_CLK     ==       Pres_CLK_64
  {
      SET_BIT(TCCR0,0);
      SET_BIT(TCCR0,1);
	  CLR_BIT(TCCR0,2);
  }
 #elif  Timer_CLK     ==       Pres_CLK_256
 {
	 CLR_BIT(TCCR0,0);
	 CLR_BIT(TCCR0,1);
	 SET_BIT(TCCR0,2);
 } 
 #elif  Timer_CLK     ==      Pres_CLK_1024
 {
	 SET_BIT(TCCR0,0);
	 CLR_BIT(TCCR0,1);
	 SET_BIT(TCCR0,2);
 }
 #endif
 
}

void timer0_stop(void)
{
	CLR_BIT(TCCR0,0);
	CLR_BIT(TCCR0,1);
	CLR_BIT(TCCR0,2);
	
}


void timer_delay(uint32 delay_ms )
{
	#if Timer_Mode     ==      Normal_Mode
	{		
	  uint8 tick_time = Timer_CLK /Freq;    // micro second
		
	  uint32 num_tick = (delay_ms*1000)/tick_time;
		
	  num_over_flow = num_tick/256;
		
	  init_value = 256 -(   (  (float32) num_tick/256 - num_over_flow  ) * 256  );
		
	  TCNT0 = init_value;
	
	  num_over_flow++;
	}
	
	#elif Timer_Mode     ==      CTC_Mode 
	{
		 uint8 tick_time = Timer_CLK /Freq;    // micro second
		 
		 uint32 num_tick = (delay_ms*1000)/tick_time;
		 
		 Compare_Match = num_tick/255;
		 
		 init_value =    ((  (float32) num_tick/255 - Compare_Match  ) * 255)-1;
		 
		 OCR0 = init_value;
		 
		 Compare_Match++;
	}
	#endif
}

void timer0_Set_CallBack(void (*ptr)(void))
{
	Timer0_Ptr = ptr;
}

/* ************************** PWM ************************ */

void PWM_Value(uint16 Duty_Cycle)
{
	#if Timer_Mode    ==       Fast_PWM_Mode 
	{
		#if PWM_Mode    ==   PWM_NON_Inverted_Mode
		{
			OCR0 = (Duty_Cycle * 256 / 100) - 1;
		}
		
		#elif PWM_Mode    ==   PWM_Inverted_Mode
		{
			OCR0 = 255-(Duty_Cycle * 256 /100);
		}
		#endif 
	}
	
	#elif Timer_Mode    ==       PWM_Phase_Correct_Mode
	{
		#if PWM_Mode    ==   PWM_NON_Inverted_Mode
		{
			OCR0 = (Duty_Cycle * 256 / 100);
		}
		
		#elif PWM_Mode    ==   PWM_Inverted_Mode
		{
			OCR0 = 255-(Duty_Cycle * 255 /100);
		}
		#endif
	}
	#endif
}

/* **************************** ISR ************************ */

ISR (TIMER0_OVF_vect)
{
	count++;
	while (count == num_over_flow)
	{
		(*Timer0_Ptr)();
		TCNT0 = init_value;
		count=0;
	}
}

ISR(TIMER0_COMP_vect)
{
	count++;
	while (count == Compare_Match)
	{
		(*Timer0_Ptr)();
		OCR0 = init_value;
		count=0;
	}
	
}