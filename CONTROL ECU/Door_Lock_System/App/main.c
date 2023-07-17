/*
 * Door_Lock_System.c
 *
 * Created: 7/9/2023 5:18:50 PM
 * Author : Khaled_Waleed_Samir_Metwally
 */ 

/* This is the main file for the control ECU */

//#include <avr/io.h>
#include "Leds.h"
#include "PushButtons.h"
#include "Buzzer.h"
#include "Uart.h"
#include <stdbool.h>
#define F_CPU 16000000UL
#include <util/delay.h>


int main(void)
{
	    M_Uart_Init();
		H_PushButtons_Init(PUSH_BUTTON0);
		H_Leds_Init();
		H_Leds_On(LED0);
		_delay_ms(1000);
		H_Leds_Off(LED0);
        u8 msg = 'x';
		u8 check;
		u8 Str [4];
		int counter = 0;
		bool CorrectPass = true;
    while (1) 
    {   check = msg;
		msg = M_Uart_Receive();
		if (msg != check){
			Str[counter]=msg;
			counter++;
		}
	
		
		if(counter == 3){
			for(int i = 0;i<4;i++){
				if(Str[i] != (i+49)){
				  CorrectPass = false;
				}
			}
			if(CorrectPass == true){
				M_Uart_Transmit('T');
			}
			else M_Uart_Transmit('F');
		}
	
		
    }
}

