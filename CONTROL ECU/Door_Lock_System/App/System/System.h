/*
 * System.h
 *
 * Created: 7/28/2023 4:39:42 PM
 *  Author: Khaled_Waleed_Samir_Metwally
 */ 


#ifndef SYSTEM_H_
#define SYSTEM_H_

// Includes 
#include "SystemCfg.h"
#include "Leds.h"
#include "Buzzer.h"
#include "Uart.h"
#include "Servo.h"
#include "Timer1.h"
#include <stdbool.h>
#define F_CPU 16000000UL
#include <util/delay.h>

// Macros

// Functions Prototypes
void A_System_Init(void);
void A_System_GetPassword(void);
void A_System_CheckPassword(void);




#endif /* SYSTEM_H_ */