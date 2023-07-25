/*
 * Timer1.c
 *
 * Created: 7/25/2023 5:51:26 PM
 *  Author: Khaled_Waleed_Samir_Metwally
 */ 
#include "Timer1.h"

void M_Timer1_Pwm1Init(void)
{
	//to make PD5 --> output
	SetBit(DDRD,5);
	//to select fast PWM mode with top ICR1 (MODE 14 in Data Sheet Table 47.)
	ClrBit(TCCR1A,0);
	SetBit(TCCR1A,1);
	SetBit(TCCR1B,3);
	SetBit(TCCR1B,4);
	//to select non inverted mode and generate PWM at OC1A pin
	ClrBit(TCCR1A,6);
	SetBit(TCCR1A,7);
}
void M_Timer1_Pmw1SetFrequency(u32 Local_u32_Frequency)
{
	ICR1 = (((F_OSC * 1000000) / TIMER1_PRESCALER) / Local_u32_Frequency);
}
void M_Timer1_Pwm1DutyCycle(u8 Local_u8_DutyCycle)
{
	//fast PWM non inverted
	OCR1A = (((Local_u8_DutyCycle*ICR1)/100)-1);
}
void M_Timer1_Pwm1Start(void)
{
	#if   TIMER1_PRESCALER == 256
	ClrBit(TCCR1B,0);
	ClrBit(TCCR1B,1);
	SetBit(TCCR1B,2);
	#elif TIMER1_PRESCALER == 1024
	SetBit(TCCR1B,0);
	ClrBit(TCCR1B,1);
	SetBit(TCCR1B,2);
	#endif
}
void M_Timer1_Pwm1Stop(void)
{
	ClrBit(TCCR1B,0);
	ClrBit(TCCR1B,1);
	ClrBit(TCCR1B,2);
}