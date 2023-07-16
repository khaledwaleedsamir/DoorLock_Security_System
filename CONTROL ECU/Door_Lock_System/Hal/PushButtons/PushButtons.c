/*
 * PushButtons.c
 *
 * Created: 7/11/2023 5:48:45 PM
 *  Author: Khaled_Waleed_Samir_Metwally
 */ 
#include "PushButtons.h"
void H_PushButtons_Init(u8 Local_u8_ButtonNum)
{
	switch(Local_u8_ButtonNum)
	{
		case PUSH_BUTTON0: M_Dio_PinMode(PUSH_BUTTON0_PIN,INPUT); break;
		case PUSH_BUTTON1: M_Dio_PinMode(PUSH_BUTTON1_PIN,INPUT); break;
		case PUSH_BUTTON2: M_Dio_PinMode(PUSH_BUTTON2_PIN,INPUT); break;
		default:                                                  break;
	}
}
u8   H_PushButtons_Read(u8 Local_u8_ButtonNum)
{
	u8 Local_u8_Value = RELEASED;
	switch(Local_u8_ButtonNum)
	{
		case PUSH_BUTTON0:
		if(M_Dio_PinRead(PUSH_BUTTON0_PIN) == PRESSED)
		{
			_delay_ms(DEBOUNCING_TIME);
			if(M_Dio_PinRead(PUSH_BUTTON0_PIN) == PRESSED)
			{
				while(M_Dio_PinRead(PUSH_BUTTON0_PIN) == PRESSED);
				Local_u8_Value = PRESSED;
			}
		} break;
		case PUSH_BUTTON1:
		if(M_Dio_PinRead(PUSH_BUTTON1_PIN) == PRESSED)
		{
			_delay_ms(DEBOUNCING_TIME);
			if(M_Dio_PinRead(PUSH_BUTTON1_PIN) == PRESSED)
			{
				while(M_Dio_PinRead(PUSH_BUTTON1_PIN) == PRESSED);
				Local_u8_Value = PRESSED;
			}
		} break;
		case PUSH_BUTTON2:
		if(M_Dio_PinRead(PUSH_BUTTON2_PIN) == PRESSED)
		{
			_delay_ms(DEBOUNCING_TIME);
			if(M_Dio_PinRead(PUSH_BUTTON2_PIN) == PRESSED)
			{
				while(M_Dio_PinRead(PUSH_BUTTON2_PIN) == PRESSED);
				Local_u8_Value = PRESSED;
			}
		} break;
		default: break;
	}
	return Local_u8_Value;
}