/*
 * Buzzer.h
 *
 * Created: 7/11/2023 5:17:38 PM
 *  Author: Khaled_Waleed_Samir_Metwally
 */ 


#ifndef BUZZER_H_
#define BUZZER_H_

// Includes
#include "BuzzerCfg.h"
#include "Dio.h"
#define F_CPU 16000000UL
#include <util/delay.h>

// Functions ProtoTypes
void H_Buzzer_Init(void);
void H_Buzzer_On(void);
void H_Buzzer_Off(void);
void H_Buzzer_Loop(void);


#endif /* BUZZER_H_ */