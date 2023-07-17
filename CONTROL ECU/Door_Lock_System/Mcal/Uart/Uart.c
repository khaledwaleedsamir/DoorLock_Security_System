/*
 * Uart.c
 *
 * Created: 7/16/2023 5:48:34 PM
 *  Author: Khaled_Waleed_Samir_Metwally
 */ 

#include "Uart.h"
void M_Uart_Init(void)
{
	ClrBit(DDRD,0); //to enable input circuit for RX pin
	SetBit(DDRD,1); //to enable output circuit for TX pin
	
	u8 Local_u8_UCSRC = 0b10000000;
	//to select char size = 8-bits
	SetBit(Local_u8_UCSRC,2);
	SetBit(Local_u8_UCSRC,1);
	ClrBit(UCSRB,2);
	//to select A sync mode
	ClrBit(Local_u8_UCSRC,6);
	#if   PARITY_MODE == PARITY_DISABLED
	ClrBit(Local_u8_UCSRC,4);
	ClrBit(Local_u8_UCSRC,5);
	#elif PARITY_MODE == PARITY_ODD
	SetBit(Local_u8_UCSRC,4);
	SetBit(Local_u8_UCSRC,5);
	#elif PARITY_MODE == PARITY_EVEN
	ClrBit(Local_u8_UCSRC,4);
	SetBit(Local_u8_UCSRC,5);
	#endif
	//to select stop bit -> 1 bit
	ClrBit(Local_u8_UCSRC,3);
	
	UBRRL = ((u32)F_OSC * 1000000 / ((u32)16 * BAUD_RATE)) - 1;
	
	UCSRC = Local_u8_UCSRC;
	
	SetBit(UCSRB,4); //to enable receive circuit  RX
	SetBit(UCSRB,3); //to enable transmit circuit TX
}
void M_Uart_Transmit(u8 Local_u8_Data)
{
	UDR = Local_u8_Data;
	while((GetBit(UCSRA,6)) == 0);
}
u8   M_Uart_Receive(void)
{
	while((GetBit(UCSRA,7)) == 0);
	return UDR;
}