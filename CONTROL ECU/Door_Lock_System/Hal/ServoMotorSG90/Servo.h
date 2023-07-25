/*
 * Servo.h
 *
 * Created: 7/25/2023 5:48:08 PM
 *  Author: Khaled_Waleed_Samir_Metwally
 */ 


#ifndef SERVO_H_
#define SERVO_H_

// Includes
#include "Timer1.h"
#include "StdTypes.h"

// Functions Prototypes
void H_ServoMotor_Init(void);
void H_ServoMotor_SetAngle(u8);
void H_ServoMotor_Start(void);
void H_ServoMotor_Stop(void);




#endif /* SERVO_H_ */