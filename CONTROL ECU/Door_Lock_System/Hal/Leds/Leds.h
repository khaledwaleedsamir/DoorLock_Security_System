/*
 * Leds.h
 *
 * Created: 7/11/2023 5:35:03 PM
 *  Author: Khaled_Waleed_Samir_Metwally
 */ 


#ifndef LEDS_H_
#define LEDS_H_

// Includes
#include "LedsCfg.h"
#include "StdTypes.h"
#include "Dio.h"

// Macros
#define LED0 1
#define LED1 2
#define LED2 3

// Functions Prototypes
void H_Leds_Init(void);
void H_Leds_On(u8);
void H_Leds_Off(u8);

#endif /* LEDS_H_ */