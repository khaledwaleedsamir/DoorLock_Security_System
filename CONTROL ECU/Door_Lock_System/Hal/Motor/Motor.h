/*
 * Motor.h
 *
 * Created: 8/9/2023 7:14:43 PM
 *  Author: Khaled_Waleed_Samir_Metwally
 */ 


#ifndef MOTOR_H_
#define MOTOR_H_

// Includes
#include "MotorCfg.h"
#include "Dio.h"
#include "BitMaths.h"
#include "StdTypes.h"

// Functions Prototypes
void H_Motor_Init(void);
void H_Motor_CW(void);
void H_Motor_CCW(void);
void H_Motor_Stop(void);
#endif /* MOTOR_H_ */