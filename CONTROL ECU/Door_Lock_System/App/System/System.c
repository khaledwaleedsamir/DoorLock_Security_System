/*
 * System.c
 *
 * Created: 7/28/2023 4:39:29 PM
 *  Author: Khaled_Waleed_Samir_Metwally
 */ 

#include "System.h"

// Global System Variables
u8  Global_u8_Password[PASSWORD_SIZE] = {'1','2','3','4'};
u8  Global_u8_EnteredPassword[PASSWORD_SIZE];		
u16 Global_u16_CharCounter = 0;
u16 Global_u16_Check = 0;
u16 Global_u16_Trials = 0;

// System Functions
void A_System_Init(void)
{
	H_ServoMotor_Init();
	M_Uart_Init();
	H_Leds_Init();
	H_Buzzer_Init();
}
void A_System_GetPassword(void)
{
	u8 Local_u8_Msg = 0;
	Local_u8_Msg = M_Uart_Receive();
	if(Local_u8_Msg != 0)
	{
		Global_u8_EnteredPassword[Global_u16_CharCounter] = Local_u8_Msg;
		Global_u16_CharCounter++;
	}
}
void A_System_CheckPassword(void)
{
	if (Global_u16_CharCounter == PASSWORD_SIZE)
	{
		for(int i = 0; i<PASSWORD_SIZE; i++)
		{
			if(Global_u8_EnteredPassword[i] == Global_u8_Password[i])
			{
				Global_u16_Check++;
			}
		}
		if(Global_u16_Check == PASSWORD_SIZE)
		{
			M_Uart_Transmit('T');
			H_ServoMotor_SetAngle(5);
			H_ServoMotor_Start();
		}
		if(Global_u16_Check < PASSWORD_SIZE)
		{
			M_Uart_Transmit('F');
			Global_u16_Trials++;
			Global_u16_CharCounter = 0;
			H_Leds_On(Global_u16_Trials);
		}
		if(Global_u16_Trials >= MAX_TRIALS)
		{
			H_Buzzer_On();
		}	
	}	
}