/*
 * Buzzer.c
 *
 * Created: 7/11/2023 5:17:24 PM
 *  Author: Khaled_Waleed_Samir_Metwally
 */ 
#include "Buzzer.h"

void H_Buzzer_Init(void)
{
	M_Dio_PinMode(BUZZER_PIN,OUTPUT);
}
void H_Buzzer_On(void)
{
	M_Dio_PinWrite(BUZZER_PIN,HIGH);
}
void H_Buzzer_Off(void)
{
	M_Dio_PinWrite(BUZZER_PIN,LOW);
}
void H_Buzzer_Loop(void)
{
	while(1){
		H_Buzzer_On();
		_delay_ms(DELAY_TIME);
		H_Buzzer_Off();
	}
}
