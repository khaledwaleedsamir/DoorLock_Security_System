/*
 * ExternalEeprom.h
 *
 * Created: 8/9/2023 5:03:36 PM
 *  Author: Khaled_Waleed_Samir_Metwally
 */ 


#ifndef EXTERNALEEPROM_H_
#define EXTERNALEEPROM_H_

// Includes
#include "StdTypes.h"
#include "Twi.h"
#define F_CPU 16000000UL
#include <util/delay.h>

// Functions Prototypes
void H_Eeprom_Init(void);
void H_Eeprom_Write(u8,u16);
u8   H_Eeprom_Read(u16);

#endif /* EXTERNALEEPROM_H_ */