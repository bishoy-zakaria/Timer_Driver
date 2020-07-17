/*
 * Timer.h
 *
 * Created: 7/17/2020 7:12:03 PM
 *  Author: 20112
 */ 


#ifndef TIMER_H_
#define TIMER_H_

#include "ATMEGA32_Regs.h"
#include "BIT_Math.h"
#include "STD.h"

#define Pres_CLK                   1
#define Pres_CLK_8                 8
#define Pres_CLK_64                64
#define Pres_CLK_256               256
#define Pres_CLK_1024              1024

#define Normal_Mode                0
#define CTC_Mode                   1

#define CTC_Output_ENABLE          0
#define CTC_Output_DISABLE         1

#define CTC_Output_Mode_Toggel     0
#define CTC_Output_Mode_Clear      1
#define CTC_Output_Mode_Set        2

#define interrupt_Disable          0
#define interrupt_Enable           1

void timer_init(void);

void timer_start(void);

void timer_stop(void);

void timer_delay(uint32);


#endif /* TIMER_H_ */