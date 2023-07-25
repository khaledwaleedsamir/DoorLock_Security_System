/*
 * Servo.c
 *
 * Created: 7/25/2023 5:47:54 PM
 *  Author: Khaled_Waleed_Samir_Metwally	
 */ 

#include "Servo.h"
void H_ServoMotor_Init(void)
{
	M_Timer1_Pwm1Init();
	M_Timer1_Pmw1SetFrequency(50);
}
void H_ServoMotor_SetAngle(u8 Local_u8_Angle)
{
	u8 Local_u8_DutyCycle = (((Local_u8_Angle*5)/180) + 5);
	M_Timer1_Pwm1DutyCycle(Local_u8_DutyCycle);
}
void H_ServoMotor_Start(void)
{
	M_Timer1_Pwm1Start();
}
void H_ServoMotor_Stop(void)
{
	M_Timer1_Pwm1Stop();
}