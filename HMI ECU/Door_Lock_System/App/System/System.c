/*
 * System.c
 *
 * Created: 7/28/2023 4:01:42 PM
 *  Author: Khaled_Waleed_Samir_Metwally
 */ 

#include "System.h"

//System Global Variables 
u8  Global_u8_SentMsg = 0;
u8  Global_u8_RecievedMsg = 0;
u16 Global_u16_CharCounter = 0;
u16 Global_u16_Trials  = 0;

// System Functions
void A_System_Init(void)
{
	H_Lcd_Init();
	H_Keypad_Init();
	M_Uart_Init();
	H_Lcd_WriteString("Welcome !");
	_delay_ms(1000);
	H_Lcd_Clear();
}
void A_System_EnterPassword(void)
{
	Global_u8_SentMsg = H_Keypad_Read();
	if(Global_u8_SentMsg != 0)
	{
		H_Lcd_WriteChar(Global_u8_SentMsg);
		M_Uart_Transmit(Global_u8_SentMsg);
		Global_u16_CharCounter++;
	}
}
void A_System_CheckPassword(void)
{
	if(Global_u16_CharCounter == PASSWORD_SIZE)
	{
		Global_u8_RecievedMsg = M_Uart_Receive();
		if(Global_u8_RecievedMsg == 'T')
		{
			H_Lcd_Clear();
			H_Lcd_WriteString("Opening !");
		}
		if(Global_u8_RecievedMsg == 'F')
		{
			Global_u16_Trials++;
			if(Global_u16_Trials < MAX_TRIALS)
			{
				H_Lcd_Clear();
				H_Lcd_WriteString("Wrong Password");
				_delay_ms(2000);
				H_Lcd_Clear();
				H_Lcd_WriteString("Enter Password");
				_delay_ms(2000);
				H_Lcd_Clear();
				Global_u16_CharCounter = 0;
			}
			if (Global_u16_Trials >= MAX_TRIALS)
			{
				H_Lcd_Clear();
				H_Lcd_WriteString("DOOR LOCKED!");
			}
		}
	}
}