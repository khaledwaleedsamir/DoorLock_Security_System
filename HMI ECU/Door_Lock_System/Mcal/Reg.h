/*
 * Reg.h
 *
 * Created: 7/10/2023 3:22:25 PM
 *  Author: Khaled_Waleed_Samir_Metwally
 */ 


#ifndef REG_H_
#define REG_H_

#include "StdTypes.h"

// Digital Input Output (DIO) Registers
#define DDRA    *(volatile u8*)0x3A
#define PORTA   *(volatile u8*)0x3B
#define PINA    *(volatile u8*)0x39
#define DDRB    *(volatile u8*)0x37
#define PORTB   *(volatile u8*)0x38
#define PINB    *(volatile u8*)0x36
#define DDRC    *(volatile u8*)0x34
#define PORTC   *(volatile u8*)0x35
#define PINC    *(volatile u8*)0x33
#define DDRD    *(volatile u8*)0x31
#define PORTD   *(volatile u8*)0x32
#define PIND    *(volatile u8*)0x30

#endif /* REG_H_ */