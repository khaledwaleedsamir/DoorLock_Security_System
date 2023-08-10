/*
 * Motor.c
 *
 * Created: 8/9/2023 7:14:31 PM
 *  Author: Khaled_Waleed_Samir_Metwally
 */ 

#include "Motor.h"

void H_Motor_Init(void)
{
	M_Dio_PinMode(MOTOR_PIN1,OUTPUT);
	M_Dio_PinMode(MOTOR_PIN1,OUTPUT);
	M_Dio_PinWrite(MOTOR_PIN1,HIGH);
	M_Dio_PinWrite(MOTOR_PIN2,HIGH);
}
void H_Motor_CW(void)
{
	M_Dio_PinWrite(MOTOR_PIN1,LOW);
	M_Dio_PinWrite(MOTOR_PIN2,HIGH);
	
}
void H_Motor_CCW(void)
{
	M_Dio_PinWrite(MOTOR_PIN1,HIGH);
	M_Dio_PinWrite(MOTOR_PIN2,LOW);
}
void H_Motor_Stop(void)
{
	M_Dio_PinWrite(MOTOR_PIN1,HIGH);
	M_Dio_PinWrite(MOTOR_PIN1,HIGH);
}