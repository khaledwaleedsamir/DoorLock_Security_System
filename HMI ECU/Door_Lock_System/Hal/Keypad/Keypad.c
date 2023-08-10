/*
 * Keypad.c
 *
 * Created: 7/16/2023 11:21:28 AM
 *  Author: Khaled_Waleed_Samir_Metwally
 */ 
#include "Keypad.h"
void H_Keypad_Init(void)
{
	//Keypad rows set as output
	M_Dio_PinMode(KEYPAD_R0_PIN,OUTPUT);
	M_Dio_PinMode(KEYPAD_R1_PIN,OUTPUT);
	M_Dio_PinMode(KEYPAD_R2_PIN,OUTPUT);
	M_Dio_PinMode(KEYPAD_R3_PIN,OUTPUT);
	//Keypad columns set as input
	M_Dio_PinMode(KEYPAD_C0_PIN,INPUT);
	M_Dio_PinMode(KEYPAD_C1_PIN,INPUT);
	M_Dio_PinMode(KEYPAD_C2_PIN,INPUT);
	M_Dio_PinMode(KEYPAD_C3_PIN,INPUT);
	//rows pins set to high
	M_Dio_PinWrite(KEYPAD_R0_PIN,HIGH);
	M_Dio_PinWrite(KEYPAD_R1_PIN,HIGH);
	M_Dio_PinWrite(KEYPAD_R2_PIN,HIGH);
	M_Dio_PinWrite(KEYPAD_R3_PIN,HIGH);
	//columns pins pull up resistors enabled
	M_Dio_PinPullUpResistor(KEYPAD_C0_PIN,ENABLE);
	M_Dio_PinPullUpResistor(KEYPAD_C1_PIN,ENABLE);
	M_Dio_PinPullUpResistor(KEYPAD_C2_PIN,ENABLE);
	M_Dio_PinPullUpResistor(KEYPAD_C3_PIN,ENABLE);
}
u8 H_Keypad_Read(void)
{
	u8 Local_u8_Arr[4][4] = {{ '7' , '8' , '9' , '/' },
	                         { '4' , '5' , '6' , '*' },
	                         { '1' , '2' , '3' , '-' },
	                         { 'C' , '0' , '=' , '+' }};
	
	while(1)
	{
		u8 Local_u8_Reading = KEYPAD_RELEASED;
		u8 Local_u8_Value = 0;
		u8 Local_u8_Row = 0;
		u8 Local_u8_Col = 0;
		for (Local_u8_Row=KEYPAD_R0_PIN;Local_u8_Row<=KEYPAD_R3_PIN;Local_u8_Row++)
		{
			M_Dio_PinWrite(Local_u8_Row,LOW);
			for (Local_u8_Col=KEYPAD_C0_PIN;Local_u8_Col<=KEYPAD_C3_PIN;Local_u8_Col++)
			{
				Local_u8_Reading = M_Dio_PinRead(Local_u8_Col);
				if(Local_u8_Reading == KEYPAD_PRESSED)
				{
					_delay_ms(KEYPAD_DEBOUNCING_TIME);
					if(M_Dio_PinRead(Local_u8_Col) == KEYPAD_PRESSED)
					{
						while(M_Dio_PinRead(Local_u8_Col) == KEYPAD_PRESSED);
						Local_u8_Value =  Local_u8_Arr[Local_u8_Row - KEYPAD_R0_PIN][Local_u8_Col - KEYPAD_C0_PIN];
					}
				}
			}
			M_Dio_PinWrite(Local_u8_Row,HIGH);
		}
		if(Local_u8_Value != 0)
		{
			return Local_u8_Value;
		}
	}
}