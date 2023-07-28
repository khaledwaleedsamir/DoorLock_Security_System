/*
 * System.h
 *
 * Created: 7/28/2023 4:01:55 PM
 *  Author: Khaled_Waleed_Samir_Metwally
 */ 


#ifndef SYSTEM_H_
#define SYSTEM_H_

// Includes
#include "SystemCfg.h"
#include "Lcd.h"
#include "Keypad.h"
#include "Uart.h"
#define F_CPU 16000000UL
#include <util/delay.h>
// Macros

// Functions Prototypes
void A_System_Init(void);
void A_System_EnterPassword(void);
void A_System_CheckPassword(void);


#endif /* SYSTEM_H_ */