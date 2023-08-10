/*
 * Door_Lock_System.c
 *
 * Created: 7/9/2023 5:18:50 PM
 * Author : Khaled_Waleed_Samir_Metwally
 */ 

/* This is the main file for the control ECU */

// Includes
#include "Buzzer.h"
#include "Leds.h"
#include "Twi.h"
#include "ExternalEeprom.h"
#include "Motor.h"
#include "Timer0.h"
#include "Uart.h"
#include "StdTypes.h"
#define F_CPU 16000000UL
#include <util/delay.h>

// System Macros
#define PASSWORD_SIZE 5
#define HMI_READY 0x20
#define C_READY 0x10
#define NUMBER_OF_OVERFLOWS_PER_SECOND 32
#define SUCCESS 1
#define ERROR 0
#define MAX_TRIALS 3

// System Timer Variables
u32 volatile Global_u32_MS= 0;


// System State Variable 
u8 volatile Global_u8_SystemState = 0;

//Timer 0 callback function

/* Function Name : A_Timer0_Execution
 * Description   : This is the call back function for timer0 (ISR). 
 * Parameters    : void. 
 * Return        : void.
 */

void A_Timer0_Execution(void)
{
	H_Motor_Stop();
	H_Buzzer_Off();
	M_Timer0_Stop();
	Global_u8_SystemState = 2;
}

// System Functions

/* Function Name : A_Main_ConfirmPassword
 * Description   : Checks if the 2 passwords entered are matched.
 * Parameters    : 2 pointer to characters (2 strings to compare).
 * Return        : u8 value
 */
u8 A_Main_ConfirmPassword(u8 * Local_u8_Str1, u8* Local_u8_Str2)
{
	for(int i = 0; i<PASSWORD_SIZE; i++)
	{
		if(Local_u8_Str1[i] != Local_u8_Str2[i])
		{
			return ERROR;
		}
	}
	return SUCCESS;
}

/* Function Name : A_Main_CheckPasswordEeprom
 * Description   : Checks if the entered password matches the saved
 *                 password in the EEPROM.
 * Parameters    : 2 pointer to characters (2 strings to compare).
 * Return        : u8 value
 */
u8 A_Main_CheckPasswordEeprom(u8 * Local_u8_Str1, u8* Local_u8_Str2)
{
	for (int i = 0; i<PASSWORD_SIZE; i++)
	{
		Local_u8_Str1 [i]= H_Eeprom_Read(1,1+i); // reads the saved password in the EEPROM page 1 byte 1
		if(Local_u8_Str1[i] != Local_u8_Str2[i])
		{
			return ERROR;
		}
	}
	return SUCCESS;
}


int main(void)
{
	// Initializing UART, LEDs, Buzzer, and Motor.
	M_Uart_Init();
	H_Buzzer_Init();
	H_Leds_Init();
	H_Motor_Init();
	H_Eeprom_Init();
	
	// Main Variables
	u8 Local_u8_StrPassword[PASSWORD_SIZE];
	u8 Local_u8_StrPasswordCheck[PASSWORD_SIZE];
	u8 Local_u8_CheckPassword;
	u8 Local_u8_TrialCounter = 0;
	u8 Local_u8_Result;
	
	while(M_Uart_ReceiveByte() != HMI_READY );   // this waits until the HMI MC is ready
	Local_u8_CheckPassword = H_Eeprom_Read(1,1); // check if there is a password already in the EEPROM.
	if (Local_u8_CheckPassword != 0xFF)          // Determine the system current state based on EEPROM.
	{
		Global_u8_SystemState = 2;
		M_Uart_SendByte(Global_u8_SystemState);
	}
	else
	{
		Global_u8_SystemState = 0;
		M_Uart_SendByte(Global_u8_SystemState);
	}
	
	
	
    while (1) 
    {  
		switch (Global_u8_SystemState)
		{
			/* This case is the case of running the program for the first time with no password set before in the EEPROM */
			case 0:
			for (int i = 0; i<PASSWORD_SIZE; i++)
			{
				Local_u8_StrPassword[i] = M_Uart_ReceiveByte(); // Receiving the password from the HMI ECU.
				_delay_ms(1);
			}
			for (int i = 0; i<PASSWORD_SIZE; i++)
			{
				Local_u8_StrPasswordCheck[i] = M_Uart_ReceiveByte(); // Receiving the password confirmation from the HMI ECU.
				_delay_ms(1);
			}
			/* SUCCESS = 1 and ERROR = 0 , System state will be determined based on whether the entered passwords match or not. */
			
			Local_u8_CheckPassword = A_Main_ConfirmPassword(Local_u8_StrPassword, Local_u8_StrPasswordCheck);
			M_Uart_SendByte(Local_u8_CheckPassword);
			Global_u8_SystemState = Local_u8_CheckPassword;
			break;
			
			/* This case is follows the first case to save the password to the EEPROM if password entered and confirmed successfully. */
			case 1:
			for (int i = 0; i<PASSWORD_SIZE; i++)
			{
				H_Eeprom_Write(Local_u8_StrPassword[i],1,1+i);
				_delay_ms(10);
			}
			Global_u8_SystemState = 2;
			break;
			
			
			/* This case is the normal case of running the system with a password saved */
			case 2:
			M_Uart_SendByte(C_READY); // sending to the HMI ECU that the control ECU is ready.
			
			u8 Local_u8_Symbol = M_Uart_ReceiveByte(); // determining system state based on received symbol.
			
			if(Local_u8_Symbol == '*')
			{
				Global_u8_SystemState = 3;
			}
			else if(Local_u8_Symbol == '+')
			{
				Global_u8_SystemState = 4;
			}
			else if(Local_u8_Symbol == '-')
			{
				Global_u8_SystemState = 6;
			}
			break;
			
			/* This case is the case of entering password to open the door. */
			case 3:
			for (int i = 0; i<PASSWORD_SIZE; i++)
			{
				Local_u8_StrPassword[i] = M_Uart_ReceiveByte();
				_delay_ms(1);
			}
			Local_u8_Result = A_Main_CheckPasswordEeprom(Local_u8_StrPasswordCheck, Local_u8_StrPassword); // comparing entered password to the saved password.
			M_Uart_SendByte(Local_u8_Result);
			
			/* Action will be taken based on the Result variable */
			
			if(Local_u8_Result == ERROR)
			{
				Local_u8_TrialCounter++;
				H_Leds_On(Local_u8_TrialCounter); // lights a red led on each wrong trial.
				
				if(Local_u8_TrialCounter == MAX_TRIALS)
				{
					Local_u8_TrialCounter = 0;
					Global_u8_SystemState = 5;
				}
			}
			_delay_ms(1);
			M_Uart_SendByte(Global_u8_SystemState);
			
			if(Local_u8_Result == SUCCESS)
			{
				Local_u8_TrialCounter = 0;
				H_Leds_Off(LED0); H_Leds_Off(LED1); H_Leds_Off(LED2); // turning off all LEDs. 
				M_Uart_SendByte(C_READY);
				Global_u32_MS = 15000; // seconds needed for timer 0 in ms.
				
				/* Timer0 initialization and setting the required time for motor to open the door */
				
				M_Timer0_Init();
				M_Timer0_SetCallBack(A_Timer0_Execution);
				M_Timer0_SetTime(Global_u32_MS);
				M_Timer0_Start();
				H_Motor_CW();
				
				/* next while loop is to wait until the door has opened and timer0 callback function is executed. */
				while(Global_u8_SystemState != 2);
				
			}
			break;
			
			
			/* This case is for doing the password reset */
			case 4:
			for(int i = 0; i<PASSWORD_SIZE; i++)
			{
				Local_u8_StrPassword[i] = M_Uart_ReceiveByte();
				_delay_ms(1);
			}
			Local_u8_Result = A_Main_CheckPasswordEeprom(Local_u8_StrPasswordCheck, Local_u8_StrPassword);
			M_Uart_SendByte(Local_u8_Result);
			
			/* Action will be taken based on the Result variable */
			if(Local_u8_Result == ERROR)
			{
				Local_u8_TrialCounter++;
				H_Leds_On(Local_u8_TrialCounter);
				
				if(Local_u8_TrialCounter == MAX_TRIALS)
				{
					Local_u8_TrialCounter = 0;
					Global_u8_SystemState = 5;
				}
				M_Uart_SendByte(Global_u8_SystemState);
			}
			
			else if(Local_u8_Result == SUCCESS)
			{
				Local_u8_TrialCounter = 0;
				H_Leds_Off(LED0); H_Leds_Off(LED1); H_Leds_Off(LED2);
				Global_u8_SystemState = 0;
				M_Uart_SendByte(Global_u8_SystemState);
			}
			break;
			
			
			/* This case is for when the user used the maximum amount of trials. */
			case 5:
			Global_u32_MS = 60000; // time for timer0 in ms.
			M_Timer0_Init();
			M_Timer0_SetCallBack(A_Timer0_Execution);
			M_Timer0_SetTime(Global_u32_MS);
			H_Buzzer_On();
			M_Timer0_Start();
			
			while(Global_u8_SystemState != 2); //to block waiting for timer0 ISR.
       }
    }
	return 0;
}