/*
 * Door_Lock_System.c
 *
 * Created: 7/9/2023 5:18:50 PM
 * Author : Khaled_Waleed_Samir_Metwally
 */ 

/* This is the main file for the Human Machine Interface ECU */

// Includes
#include "StdTypes.h"
#include "Lcd.h"
#include "Keypad.h"
#include "Uart.h"
#include "Timer0.h"
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
u32 volatile Global_u32_MS = 0;

// System State Variable
u8 volatile Global_u8_SystemState = 0;

// Timer 0 ISR callback function.

/* Function Name : A_Timer0_Execution
 * Description   : This is the call back function for timer0 (ISR). 
 * Parameters    : void. 
 * Return        : void.
 */
void A_Timer0_Execution(void)
{
	M_Timer0_Stop();
	Global_u8_SystemState = 2;
}

int main(void)
{
	/* Initialization of Keypad, LCD and UART. */
	H_Keypad_Init();
	H_Lcd_Init();
	M_Uart_Init();
	
	/*Local Main Variables*/
	u8 Local_u8_Password[PASSWORD_SIZE];
	u8 Local_u8_Check = 0;
	u8 Local_u8_SendPassword = 0;
	u8 Local_u8_SendKey = 0;
	
	M_Uart_Transmit(HMI_READY); // sending to the Control ECU ready signal.
	Global_u8_SystemState = M_Uart_Receive(); // Receiving the system state from the control ECU.
	
	
	while (1)
	{
		switch(Global_u8_SystemState)
		{
			/* This case is the case of running the program for the first time with no password set before in the EEPROM */
			case 0:
			H_Lcd_WriteString("Create Password");
			_delay_ms(1000);
			H_Lcd_Clear();
			H_Lcd_WriteString("Enter Password");
			H_Lcd_NextLine();
			for (int i = 0; i<PASSWORD_SIZE; i++)
			{
				Local_u8_Password[i] = H_Keypad_Read(); // while 1 loop inside the keypad driver until a key is pressed.
				H_Lcd_WriteChar('*');
				
				/* The next if condition is for clearing the screen if the user presses the C button*/
				if(Local_u8_Password[i] == 'C')
				{
					H_Lcd_Clear();
					H_Lcd_WriteString("Enter Password");
					H_Lcd_NextLine();
					i = -1; // setting the loop counter to -1 to start from 0 again in the next iteration.
				}
			}
			H_Lcd_Clear();
			
			/* The following do while loop is done to send the entered password when the user presses the '=' key.*/
			do 
			{
				H_Lcd_WriteString("Press '=' To");
				H_Lcd_NextLine();
				H_Lcd_WriteString("Confirm Password");
				Local_u8_SendPassword = H_Keypad_Read();
			} while (Local_u8_SendPassword != '=');
			
			/*Sending the password after the user presses '=' key.*/
			for (int i = 0; i<PASSWORD_SIZE; i++)
			{
				_delay_ms(1);
				M_Uart_Transmit(Local_u8_Password[i]);
			}
			H_Lcd_Clear();
			H_Lcd_WriteString("Password Sent!");
			_delay_ms(500);
			H_Lcd_Clear();
			
			/* Password Confirmation Step */
			H_Lcd_WriteString("  Confirmation");
			H_Lcd_NextLine();
			H_Lcd_WriteString("Enter Password");
			_delay_ms(500);
			H_Lcd_Clear();
			H_Lcd_WriteString("Enter Password");
			H_Lcd_NextLine();
			for (int i = 0; i<PASSWORD_SIZE; i++)
			{
				Local_u8_Password[i] = H_Keypad_Read(); // while 1 loop inside the keypad driver until a key is pressed.
				H_Lcd_WriteChar('*');
				
				/* The next if condition is for clearing the screen if the user presses the C button*/
				if(Local_u8_Password[i] == 'C')
				{
					H_Lcd_Clear();
					H_Lcd_WriteString("Enter Password");
					H_Lcd_NextLine();
					i = -1; // setting the loop counter to -1 to start from 0 again in the next iteration.
				}
			}
			H_Lcd_Clear();
			
			/* The following do while loop is done to send the entered password when the user presses the '=' key.*/
			do
			{
				H_Lcd_WriteString("Press '=' To");
				H_Lcd_NextLine();
				H_Lcd_WriteString("Confirm Password");
				Local_u8_SendPassword = H_Keypad_Read();
			} while (Local_u8_SendPassword != '=');
			
			/*Sending the password after the user presses '=' key.*/
			for (int i = 0; i<PASSWORD_SIZE; i++)
			{
				_delay_ms(1);
				M_Uart_Transmit(Local_u8_Password[i]);
			}
			H_Lcd_Clear();
			H_Lcd_WriteString("Password Sent!");
			
			
			/* Waiting for confirmation from the control ECU that the password is entered twice successfully. */
			Global_u8_SystemState = M_Uart_Receive();
			H_Lcd_Clear();
			if(Global_u8_SystemState == 0)
			{
				H_Lcd_WriteString(" Not Matched !");
				_delay_ms(1000);
				H_Lcd_Clear();
			}
			break;
			
			
			/*This case is for displaying that the entered passwords are matched and the password is saved in EEPROM. */
			case 1:
			H_Lcd_WriteString("    Matched!");
			H_Lcd_NextLine();
			H_Lcd_WriteString(" Password Saved");
			_delay_ms(1000);
			H_Lcd_Clear();
			Global_u8_SystemState = 2;
			break;
			
			/* This case is for displaying to the user the options available and it is the main case.
			                option 1 --> [Enter Password] option 2 --> [Reset Password]                    */
			case 2:
			while(M_Uart_Receive() != C_READY);  // wait until Control ECU is ready.
			H_Lcd_Clear();
			
			/* Displaying the options available on the LCD */
			H_Lcd_WriteString("  *: OPEN DOOR");
			H_Lcd_NextLine();
			H_Lcd_WriteString("+:Reset Password");
			
			/*Do while loop until user selects an option.*/
			do 
			{
				Local_u8_SendKey = H_Keypad_Read();
			} while ((Local_u8_SendKey != '*') && (Local_u8_SendKey != '+'));
			
			/*Sending The chosen option to the control ECU. */
			M_Uart_Transmit(Local_u8_SendKey);
			H_Lcd_Clear();
			H_Lcd_WriteChar(Local_u8_SendKey);
			_delay_ms(500);
			
			/* The system state is changed based on the chosen symbol. */
			if(Local_u8_SendKey == '*')
			{
				Global_u8_SystemState = 3;
			}
			else if(Local_u8_SendKey == '+')
			{
				Global_u8_SystemState = 4;
			}
			break;
			
			
			
			/*This case is for entering the password to open the door.*/
			case 3:
			H_Lcd_WriteString(" Enter Password");
			H_Lcd_NextLine();
			
			/*Taking password from the user.*/
			for (int i = 0; i<PASSWORD_SIZE; i++)
			{
				Local_u8_Password[i] = H_Keypad_Read();
				H_Lcd_WriteChar('*');
				
				/* The next if condition is for clearing the screen if the user presses the C button*/
				if(Local_u8_Password[i] == 'C')
				{
					H_Lcd_Clear();
					H_Lcd_WriteString("Enter Password");
					H_Lcd_NextLine();
					i = -1; // setting the loop counter to -1 to start from 0 again in the next iteration.
				}
			}
			H_Lcd_Clear();
			H_Lcd_WriteString("  Checking....");
			/*Sending the entered password to the control ECU to check if it is correct. */
			for(int i = 0; i<PASSWORD_SIZE; i++)
			{
				_delay_ms(1);
				M_Uart_Transmit(Local_u8_Password[i]);
			}
			H_Lcd_Clear();
			
			/*waiting for the check byte to confirm that the entered password is correct. */
			Local_u8_Check = M_Uart_Receive();
			
			/*Based on check and the data sent from the Control ECU system state will be determined. */
			if(Local_u8_Check == ERROR)
			{
				H_Lcd_WriteString(" Wrong Password");
				_delay_ms(1000);
				H_Lcd_Clear();
				Global_u8_SystemState = M_Uart_Receive();
			}
			else if(Local_u8_Check == SUCCESS)
			{
				H_Lcd_WriteString("Correct Password");
				_delay_ms(1000);
				H_Lcd_Clear();
				
				while(M_Uart_Receive() != C_READY); // wait until the control ECU is ready.
				
				/* Initializing Timer 0 to wait for the door opening duration (15 seconds) */
				M_Timer0_Init();
				M_Timer0_SetCallBack(A_Timer0_Execution);
				M_Timer0_SetTime(15000); // setting timer0 in ms.
				H_Lcd_WriteString("   Opening!..");
				M_Timer0_Start();
				while(Global_u8_SystemState != 2); // wait for timer0 ISR.
			}
			break;
			
			
			/* This case is for Changing the current password by entering the old password then changing it. */
			case 4:
			H_Lcd_WriteString(" Enter Password");
			H_Lcd_NextLine();
			for (int i = 0; i<PASSWORD_SIZE; i++)
			{
				Local_u8_Password[i] = H_Keypad_Read();
				H_Lcd_WriteChar('*');
				
				/* The next if condition is for clearing the screen if the user presses the C button*/
				if(Local_u8_Password[i] == 'C')
				{
					H_Lcd_Clear();
					H_Lcd_WriteString("Enter Password");
					H_Lcd_NextLine();
					i = -1; // setting the loop counter to -1 to start from 0 again in the next iteration.
				}
			}
			H_Lcd_Clear();
			H_Lcd_WriteString("  Checking....");
			/*Sending the entered password to the control ECU to check if it is correct. */
			for(int i = 0; i<PASSWORD_SIZE; i++)
			{
				_delay_ms(1);
				M_Uart_Transmit(Local_u8_Password[i]);
			}
			H_Lcd_Clear();
			
			Local_u8_Check = M_Uart_Receive();
			
			if(Local_u8_Check == ERROR)
			{
				H_Lcd_WriteString("Wrong Password");
				_delay_ms(1000);
				H_Lcd_Clear();
				Global_u8_SystemState = M_Uart_Receive();
			}
			else if(Local_u8_Check == SUCCESS)
			{
				H_Lcd_WriteString("Correct Password");
				_delay_ms(1000);
				H_Lcd_Clear();
				Global_u8_SystemState = M_Uart_Receive();
			}
			break;
			
			/* This case is executed if the user entered wrong password for the maximum trials allowed. */
			case 5:
			H_Lcd_WriteString("*Wrong Passwords");
			H_Lcd_WriteString(" Limit Reached!");
			_delay_ms(1000);
			
			/*Timer 0 initialization to wait for 60 seconds before the user it allowed to enter passwords again */
			M_Timer0_Init();
			M_Timer0_SetCallBack(A_Timer0_Execution);
			M_Timer0_SetTime(60000);
			H_Lcd_Clear();
			H_Lcd_WriteString("Wait 60 Seconds!");
			M_Timer0_Start();
			while(Global_u8_SystemState != 2);
			break;
		}
			   
	}
}