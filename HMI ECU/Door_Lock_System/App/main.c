/*
 * Door_Lock_System.c
 *
 * Created: 7/9/2023 5:18:50 PM
 * Author : Khaled_Waleed_Samir_Metwally
 */ 

/* This is the main file for the Human Machine Interface ECU */

//#include <avr/io.h>
#include "Lcd.h"
#include "Keypad.h"
#include "Uart.h"
#define F_CPU 16000000UL
#include <util/delay.h>


int main(void)
{
	H_Keypad_Init();
	H_Lcd_Init();
	H_Lcd_WriteString("Init Done !");
	M_Uart_Init();
	u8 msg;
	u8 msgR;
	H_Lcd_Clear();

	
    /* Replace with your application code */
    while (1) 
    {    
		msg = H_Keypad_Read();
		H_Lcd_WriteChar(msg);
		M_Uart_Transmit(msg);
		msgR = M_Uart_Receive();
		if(msgR == 'T'){
		H_Lcd_WriteString("PASS");
		}
		else if(msgR == 'F'){
			H_Lcd_WriteString("Incorrect Pass!");
		}
		
    }
}

