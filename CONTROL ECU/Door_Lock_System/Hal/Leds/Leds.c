/*
 * Leds.c
 *
 * Created: 7/11/2023 5:35:30 PM
 *  Author: Khaled_Waleed_Samir_Metwally
 */ 
#include "Leds.h"

void H_Leds_Init(void)
{
	M_Dio_PinMode(LED0_PIN,OUTPUT);
	M_Dio_PinMode(LED1_PIN,OUTPUT);
	M_Dio_PinMode(LED2_PIN,OUTPUT);
}
void H_Leds_On(u8 Local_u8_LedNum)
{
	switch(Local_u8_LedNum)
	{
		case LED0: M_Dio_PinWrite(LED0_PIN,HIGH);  break;
		case LED1: M_Dio_PinWrite(LED1_PIN,HIGH);  break;
		case LED2: M_Dio_PinWrite(LED2_PIN,HIGH);  break;
		default:                                   break;
	}
}
void H_Leds_Off(u8 Local_u8_LedNum)
{
	switch(Local_u8_LedNum)
	{
		case LED0: M_Dio_PinWrite(LED0_PIN,LOW);  break;
		case LED1: M_Dio_PinWrite(LED1_PIN,LOW);  break;
		case LED2: M_Dio_PinWrite(LED2_PIN,LOW);  break;
		default:                                  break;
	}
}