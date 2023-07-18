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
		H_Leds_Init();
		H_Buzzer_Init();
		u8 Str [4];
		u8 Password[4] = {'1','2','3','4'};
		int counter = 0;
		int check = 0;
		int trials = 0;
    while (1) 
    {   u8 msg = 0;
		msg = M_Uart_Receive();
		if (msg != 0){
			Str[counter]=msg;
			counter++;
		}
	
	       if(counter == 4){
			for(int i = 0;i<4;i++){
				if(Str[i] == Password[i]){
				  check++;
				}
			}
			if(check == 4){M_Uart_Transmit('T');}
			if(check  < 4){M_Uart_Transmit('F');
			trials++; counter = 0;}
		}
		if(trials == 1){H_Leds_On(LED0);}
		if(trials == 2){H_Leds_On(LED1);}
		if(trials == 3){H_Leds_On(LED2);}
		if(trials == 4){H_Buzzer_On();}
		
	
		
    }
}

