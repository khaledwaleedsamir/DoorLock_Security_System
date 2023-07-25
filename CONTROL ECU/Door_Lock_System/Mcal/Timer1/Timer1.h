/*
 * Timer1.h
 *
 * Created: 7/25/2023 5:51:02 PM
 *  Author: Khaled_Waleed_Samir_Metwally
 */ 


#ifndef TIMER1_H_
#define TIMER1_H_

// Includes
#include "Timer1Cfg.h"
#include "StdTypes.h"
#include "BitMaths.h"
#include "Reg.h"

// Macros
#define NORMAL_MODE           1
#define CTC_MODE              2

#define NON_INVERTED          0
#define INVERTED              1

#define FAST_PWM0              1
#define PHASE_CORRECT_PWM0     2

// Functions Prototypes
void M_Timer1_Pwm1Init(void);
void M_Timer1_Pmw1SetFrequency(u32);
void M_Timer1_Pwm1DutyCycle(u8);
void M_Timer1_Pwm1Start(void);
void M_Timer1_Pwm1Stop(void);




#endif /* TIMER1_H_ */