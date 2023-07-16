/*
 * Door_Lock_System.c
 *
 * Created: 7/9/2023 5:18:50 PM
 * Author : Khaled_Waleed_Samir_Metwally
 */ 

//#include <avr/io.h>
#include "Leds.h"
#include "PushButtons.h"
#include "Buzzer.h"
#define F_CPU 16000000UL
#include <util/delay.h>


int main(void)
{
	    /* Replace with your application code */
    while (1) 
    {    
		if(H_PushButtons_Read(PUSH_BUTTON1) == PRESSED)
		{
			H_Leds_On(LED0);
			_delay_ms(100);
			H_Leds_Off(LED0);
		}
		if(H_PushButtons_Read(PUSH_BUTTON2) == PRESSED)
		{
			H_Buzzer_On();
			_delay_ms(1000);
			H_Buzzer_Off();
		}
		
		
		
    }
}

