/*
 * Door_Lock_System.c
 *
 * Created: 7/9/2023 5:18:50 PM
 * Author : Khaled_Waleed_Samir_Metwally
 */ 

/* This is the main file for the Human Machine Interface ECU */

#include "System.h"

int main(void)
{
	A_System_Init();
	while (1)
	{
		A_System_EnterPassword();
		A_System_CheckPassword();
	}
}
