/*
 * Timer.c
 *
 * Created: 7/17/2020 7:12:18 PM
 *  Author: 20112
 */ 
#include "Timer.h"
#include "Timer_Cfg.h"

uint32 num_over_flow;
uint8  init_value;

void timer_init(void)
{
	
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
	#endif
	
	#if    CTC_Output  ==   CTC_Output_ENABLE
	{
		SET_BIT(TCCR0,7);
		
	   #if  CTC_Output_Mode      ==     CTC_Output_Mode_Toggel
	   {
		   CLR_BIT(TCCR0,5);
		   SET_BIT(TCCR0,4);
	   }
	   #elif  CTC_Output_Mode      ==     CTC_Output_Mode_Clear
	   {
		   SET_BIT(TCCR0,5);
		   CLR_BIT(TCCR0,4);
	   }
	   #elif  CTC_Output_Mode      ==     CTC_Output_Mode_Set
	   {
		   SET_BIT(TCCR0,5);
		   SET_BIT(TCCR0,4);
	   }
	   #endif
	   
   }
   
   #elif    CTC_Output  ==   CTC_Output_DISABLE
   {
	   CLR_BIT(TCCR0,7);
	   CLR_BIT(TCCR0,5);
	   CLR_BIT(TCCR0,4);
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

void timer_stop(void)
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
		 
		 num_over_flow = num_tick/255;
		 
		 init_value =    ((  (float32) num_tick/255 - num_over_flow  ) * 255)-1;
		 
		 OCR0 = init_value;
		 
		 num_over_flow++;
	}
	#endif
}