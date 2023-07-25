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
	M_Uart_Init();
	u8 msg;
	u8 Rmsg;
	int counter = 0;
	int trials = 0;
	H_Lcd_WriteString("Init Done !");
	_delay_ms(1000);
	H_Lcd_Clear();
	H_Lcd_WriteString("Enter Password!");
	_delay_ms(2000);
	H_Lcd_Clear();
    /* Replace with your application code */
    while (1) 
    {   
		if(counter == 4){
			Rmsg = M_Uart_Receive();
			if(Rmsg == 'T'){
				H_Lcd_Clear();
				H_Lcd_WriteString("Opening !");
			}
			if(Rmsg == 'F'){
				trials++;
				if (trials < 3){
					H_Lcd_Clear();
					H_Lcd_WriteString("Wrong Pass!");
					_delay_ms(2000);
					H_Lcd_Clear();
					H_Lcd_WriteString("Enter Password");
					_delay_ms(2000);
					H_Lcd_Clear();
					counter = 0;
				}
				if (trials == 3)
				{
					H_Lcd_Clear();
					H_Lcd_WriteString("THEIF !");
					}
			}
		}
		msg = H_Keypad_Read();
		if(msg != 0){
			H_Lcd_WriteChar(msg);
			M_Uart_Transmit(msg);
			counter++;
		}
	}
}

