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

// UART Registers
#define UDR      *(volatile u8*)0x2C
#define UCSRA    *(volatile u8*)0x2B
#define UCSRB    *(volatile u8*)0x2A
#define UCSRC    *(volatile u8*)0x40
#define UBRRL    *(volatile u8*)0x29
#define UBRRH    *(volatile u8*)0x40

// Status Register
#define SREG    *(volatile u8*)0x5F

// Timer0 Registers
#define TCCR0    *(volatile u8*)0x53
#define TIMSK    *(volatile u8*)0x59
#define TCNT0    *(volatile u8*)0x52
#define OCR0     *(volatile u8*)0x5C

#endif /* REG_H_ */