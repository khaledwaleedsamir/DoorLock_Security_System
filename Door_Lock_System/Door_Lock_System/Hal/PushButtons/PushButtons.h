/*
 * PushButtons.h
 *
 * Created: 7/11/2023 5:48:58 PM
 *  Author: Khaled_Waleed_Samir_Metwally
 */ 


#ifndef PUSHBUTTONS_H_
#define PUSHBUTTONS_H_

// Includes
#include "PushButtonsCfg.h"
#include "StdTypes.h"
#include "Dio.h"
#define F_CPU 16000000UL
#include <util/delay.h>

// Macros
#define PUSH_BUTTON0 1
#define PUSH_BUTTON1 2
#define PUSH_BUTTON2 3

#define ACTIVE_HIGH 1
#define ACTIVE_LOW  2

#if PUSH_BUTTON_MODE == ACTIVE_HIGH
#define PRESSED  1
#define RELEASED 0
#elif PUSH_BUTTON_MODE == ACTIVE_LOW
#define PRESSED  0
#define RELEASED 1
#endif

// Functions Prototypes
void H_PushButtons_Init(u8);
u8   H_PushButtons_Read(u8);


#endif /* PUSHBUTTONS_H_ */