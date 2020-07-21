/*
 * Timer_Cfg.h
 *
 * Created: 7/17/2020 7:11:51 PM
 *  Author: 20112
 */ 


#ifndef TIMER_CFG_H_
#define TIMER_CFG_H_

#include "Timer.h"

#define Freq                16    // MEGA HERTEZ
 
 #define Timer_CLK            Pres_CLK

#define Timer_Mode          PWM_Phase_Correct_Mode 

#define PWM_Mode             PWM_NON_Inverted_Mode

#define interrupt_state      interrupt_Enable 


#endif /* TIMER_CFG_H_ */