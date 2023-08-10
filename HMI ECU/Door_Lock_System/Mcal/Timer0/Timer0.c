/*
 * Timer0.c
 *
 * Created: 8/9/2023 6:37:20 PM
 *  Author: Khaled_Waleed_Samir_Metwally
 */ 

#include "Timer0.h"

// Required Global Variables
u32 Timer0_u32_NumOfOverFlows = 0;
u8  Timer0_u8_RemainderTicks = 0;
u32 Timer0_NumberOfCompareMatch = 0;

void (*CallBack)(void);

void M_Timer0_Init(void)
{  
	#if   TIMER0_MODE == NORMAL_MODE
	ClrBit(TCCR0,3);
	ClrBit(TCCR0,6);
	SetBit(TIMSK,0); //to enable timer0 overflow INT
	
	#elif TIMER0_MODE == CTC_MODE
	SetBit(TCCR0,3);
	ClrBit(TCCR0,6);
	SetBit(TIMSK,1); //to enable timer0 compare match INT
	
	#endif
	
	SetBit(SREG,7); //to enable global INT
	
	
}

void M_Timer0_SetTime(u32 Local_u32_DesiredTime)
{  
	#if TIMER0_MODE == NORMAL_MODE
	u32 Local_u32_TickTime        = TIMER_0_PRESCALER / F_OSC ; //result in micro seconds
	
	u32 Local_u32_TotalTicks      = (Local_u32_DesiredTime * 1000) / Local_u32_TickTime ; //desired time is in ms
	    Timer0_u32_NumOfOverFlows = Local_u32_TotalTicks / 256 ;
		
    Timer0_u8_RemainderTicks   = Local_u32_TotalTicks % 256; //to get any desired time
	
	/*Example: we want to M_Timer0_SetTime(1000);
	TickTime = 64 microsecond -> TotalTicks = 15625 -> Num of overflows = 61.03515625 thus only 61 overflow 
	to get the remaining 0.03515625 overflow we need the Remaining Ticks = 9 ticks
	to count those ticks we write on the timer TCNT0 register 256 - remaining ticks so the timer will get to the first
	overflow after 9 ticks only and then increment the number of overflows to do the rest 61 overflows so in total 62 
	overflows but first overflow is reached after 9 ticks only as we already wrote 247 on the register, and we use if 
	to make sure this happens if we have remaining ticks only (the ticks that sum up to less than 1 overflow i.e less than 256).
	*/
	
	if(Timer0_u8_RemainderTicks != 0)
	{
		TCNT0 = 256 - Timer0_u8_RemainderTicks; 
	    Timer0_u32_NumOfOverFlows++;
	}
	#elif TIMER0_MODE == CTC_MODE
	
	u32 Local_u32_TickTime        = TIMER_0_PRESCALER / F_OSC ; //result in micro seconds
	u32 Local_u32_TotalTicks      = (Local_u32_DesiredTime * 1000) / Local_u32_TickTime ; //desired time is in ms
	u8 Local_u8_DivisionFactor = 255;
	while (Local_u32_TotalTicks % Local_u8_DivisionFactor == 0)
	{
		Local_u8_DivisionFactor--;
	}
	Timer0_NumberOfCompareMatch  = Local_u32_TotalTicks / Local_u8_DivisionFactor ;
	OCR0 = Local_u8_DivisionFactor - 1;
	
	#endif
	
	
}
void M_Timer0_Start(void)
{  
	#if   TIMER_0_PRESCALER == 1024
	SetBit(TCCR0,0);
	ClrBit(TCCR0,1);
	SetBit(TCCR0,2);
	#elif TIMER_0_PRESCALER == 256
	ClrBit(TCCR0,0);
	ClrBit(TCCR0,1);
	SetBit(TCCR0,2);
	#endif
}
void M_Timer0_Stop(void)
{
	ClrBit(TCCR0,0);
	ClrBit(TCCR0,1);
	ClrBit(TCCR0,2);
}

void M_Timer0_Pwm0Init(void)
{ 
	SetBit(DDRB,3);     //to make PB3 output
	
	#if   PWM0_MODE == FAST_PWM0
	SetBit(TCCR0,3);
	SetBit(TCCR0,6);
	     #if   FAST_PWM0_MODE == NON_INVERTED
	     ClrBit(TCCR0,4);
	     SetBit(TCCR0,5);
	     
	     #elif FAST_PWM0_MODE == INVERTED
	     SetBit(TCCR0,4);
	     SetBit(TCCR0,5);
	     
	     #endif
	#elif PWM0_MODE == PHASE_CORRECT_PWM0
	ClrBit(TCCR0,3);
	SetBit(TCCR0,6);
	
	     #if   PHASE_CORRECT_PWM0MODE == NON_INVERTED
	     ClrBit(TCCR0,4);
	     SetBit(TCCR0,5);
	     
	     #elif PHASE_CORRECT_PWM0MODE == INVERTED
	     SetBit(TCCR0,4);
	     SetBit(TCCR0,5);
	     
	     #endif
	#endif
	

}
void M_Timer0_Pwm0SetDutyCycle(u8 Local_u8_DutyCycle)
{
	#if   PWM0_MODE == FAST_PWM0
	     #if   FAST_PWM0_MODE == NON_INVERTED
	        OCR0 = (((Local_u8_DutyCycle*256)/100)-1);
		 #elif FAST_PWM0_MODE == INVERTED
		    //another rule
		 #endif
	#elif PWM0_MODE == PHASE_CORRECT_PWM0	
	     #if   PHASE_CORRECT_PWM0MODE == NON_INVERTED
	        OCR0 = ((Local_u8_DutyCycle*255)/100);
	     #elif PHASE_CORRECT_PWM0MODE == INVERTED
	        //another rule
	     #endif
	#endif	 	
}
void M_Timer0_Pwm0Start(void)
{
	M_Timer0_Start();
}
void M_Timer0_Pwm0Stop(void)
{
	M_Timer0_Stop();
}


void M_Timer0_SetCallBack(void (*Ptr)(void))
{
	CallBack = Ptr;
}

#if TIMER0_MODE == NORMAL_MODE
ISR(TIMER0_OVF_vect)
{
	static u32 Local_u32_Counter = 0;
	           Local_u32_Counter++;
	if(Local_u32_Counter == Timer0_u32_NumOfOverFlows)
	{
		CallBack();
		Local_u32_Counter = 0;
		TCNT0 = 256 - Timer0_u8_RemainderTicks;
	}
	
}
#elif TIMER0_MODE == CTC_MODE
ISR(TIMER0_COMP_vect)
{
	static u32 Local_u32_Counter = 0;
	Local_u32_Counter++;
	if(Local_u32_Counter == Timer0_NumberOfCompareMatch)
	{
		CallBack();
		Local_u32_Counter = 0;
		
	}
	
}
#endif