/*
 * Timer0.h
 *
 * Created: 8/9/2023 6:37:32 PM
 *  Author: Khaled_Waleed_Samir_Metwally
 */ 


#ifndef TIMER0_H_
#define TIMER0_H_

// Includes
#include "Timer0Cfg.h"
#include "StdTypes.h"
#include "Reg.h"
#include "BitMaths.h"
#include <avr/interrupt.h>

// Macros
#define NORMAL_MODE           1
#define CTC_MODE              2

#define NON_INVERTED          0
#define INVERTED              1

#define FAST_PWM0              1
#define PHASE_CORRECT_PWM0     2

// Functions Prototypes
void M_Timer0_Init(void);
void M_Timer0_SetTime(u32);
void M_Timer0_Start(void);
void M_Timer0_Stop(void);
void M_Timer0_SetCallBack(void(*)(void));

void M_Timer0_Pwm0Init(void);
void M_Timer0_Pwm0SetDutyCycle(u8);
void M_Timer0_Pwm0Start(void);
void M_Timer0_Pwm0Stop(void);

#endif /* TIMER0_H_ */