/*
 * Keypad.h
 *
 * Created: 7/16/2023 11:21:42 AM
 *  Author: Khaled_Waleed_Samir_Metwally
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_
// Includes
#include "KeypadCfg.h"
#include "StdTypes.h"
#include "Dio.h"
#define F_CPU 16000000UL
#include <util/delay.h>

// Macros
#define KEYPAD_PRESSED   0
#define KEYPAD_RELEASED  1

// Functions ProtoTypes
void H_Keypad_Init(void);
u8 H_Keypad_Read(void);




#endif /* KEYPAD_H_ */