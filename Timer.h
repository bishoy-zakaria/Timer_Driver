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
#define PWM_Phase_Correct_Mode     2
#define Fast_PWM_Mode              3

#define PWM_NON_Inverted_Mode      0
#define PWM_Inverted_Mode          1

#define interrupt_Disable          0
#define interrupt_Enable           1

void timer0_init(void);

void timer0_start(void);

void timer0_stop(void);

void timer0_delay(uint32);

void timer0_Set_CallBack(void (*ptr)(void));

/* ************************** PWM ***************************** */

void PWM_Value(uint16 );

void PWM_Set_CallBack(void (*ptr)(void));

/* ************************** TIMER1 *************************** */

void timer1_init(void);

void timer1_start(void);

void timer1_stop(void);

void timer1_delay(uint32);

void timer1_Set_CallBack(void (*ptr)(void));




#endif /* TIMER_H_ */