/*
 * Lcd.c
 *
 * Created: 7/16/2023 9:29:52 AM
 *  Author: Khaled_Waleed_Samir_Metwally
 */ 
#include "Lcd.h"
void H_Lcd_Init(void)
{
	#if LCD_MODE == _8_BIT_MODE
	M_Dio_PinMode(LCD_DATA0_PIN,OUTPUT);
	M_Dio_PinMode(LCD_DATA1_PIN,OUTPUT);
	M_Dio_PinMode(LCD_DATA2_PIN,OUTPUT);
	M_Dio_PinMode(LCD_DATA3_PIN,OUTPUT);
	M_Dio_PinMode(LCD_DATA4_PIN,OUTPUT);
	M_Dio_PinMode(LCD_DATA5_PIN,OUTPUT);
	M_Dio_PinMode(LCD_DATA6_PIN,OUTPUT);
	M_Dio_PinMode(LCD_DATA7_PIN,OUTPUT);

	M_Dio_PinMode(LCD_RS_PIN,OUTPUT);
	M_Dio_PinMode(LCD_RW_PIN,OUTPUT);
	M_Dio_PinMode(LCD_EN_PIN,OUTPUT);
	M_Dio_PinWrite(LCD_RW_PIN,LOW);
	_delay_ms(1000); //delay because uC is much faster than the uC in LCD
	H_Lcd_WriteCommand(LCD_8BIT_MODE);
	H_Lcd_WriteCommand(LCD_DISPLAY_ON_CURSOR_OFF);
	H_Lcd_WriteCommand(LCD_CLEAR);
	H_Lcd_WriteCommand(LCD_RETURN_HOME);

	#elif LCD_MODE == _4_BIT_MODE
	M_Dio_PinMode(LCD_DATA0_PIN,OUTPUT);
	M_Dio_PinMode(LCD_DATA1_PIN,OUTPUT);
	M_Dio_PinMode(LCD_DATA2_PIN,OUTPUT);
	M_Dio_PinMode(LCD_DATA3_PIN,OUTPUT);
	M_Dio_PinMode(LCD_DATA4_PIN,OUTPUT);
	M_Dio_PinMode(LCD_DATA5_PIN,OUTPUT);
	M_Dio_PinMode(LCD_DATA6_PIN,OUTPUT);
	M_Dio_PinMode(LCD_DATA7_PIN,OUTPUT);

	M_Dio_PinMode(LCD_RS_PIN,OUTPUT);
	M_Dio_PinMode(LCD_RW_PIN,OUTPUT);
	M_Dio_PinMode(LCD_EN_PIN,OUTPUT);
	M_Dio_PinWrite(LCD_RW_PIN,LOW);
	_delay_ms(1000); 
	H_Lcd_WriteCommand(LCD_4BIT_MODE_1);
	H_Lcd_WriteCommand(LCD_4BIT_MODE_2);
	H_Lcd_WriteCommand(LCD_4BIT_MODE_3);
	H_Lcd_WriteCommand(LCD_DISPLAY_ON_CURSOR_OFF);
	H_Lcd_WriteCommand(LCD_CLEAR);
	H_Lcd_WriteCommand(LCD_RETURN_HOME);

	#endif
}
void H_Lcd_WriteChar(u8 Local_u8_Char)
{
	#if LCD_MODE == _8_BIT_MODE
	M_Dio_PinWrite(LCD_RS_PIN,HIGH);
	LCD_DATA_PORT = (Local_u8_Char & 0b11110000) | (LCD_DATA_PORT & 0b00001111);
	M_Dio_PinWrite(LCD_EN_PIN,HIGH);
	_delay_ms(1);
	M_Dio_PinWrite(LCD_EN_PIN,LOW);
	_delay_ms(5);
	#elif LCD_MODE == _4_BIT_MODE
	M_Dio_PinWrite(LCD_RS_PIN,HIGH);
	LCD_DATA_PORT = (Local_u8_Char & 0b11110000) | (LCD_DATA_PORT & 0b00001111);
	M_Dio_PinWrite(LCD_EN_PIN,HIGH);
	_delay_ms(1);
	M_Dio_PinWrite(LCD_EN_PIN,LOW);
	_delay_ms(5);
	LCD_DATA_PORT = (Local_u8_Char << 4) | (LCD_DATA_PORT & 0b00001111);
	M_Dio_PinWrite(LCD_EN_PIN,HIGH);
	_delay_ms(1);
	M_Dio_PinWrite(LCD_EN_PIN,LOW);
	_delay_ms(5);
	#endif
}
void H_Lcd_WriteCommand(u8 Local_u8_Command)
{
	 #if LCD_MODE == _8_BIT_MODE
	 M_Dio_PinWrite(LCD_RS_PIN,LOW);
	 LCD_DATA_PORT = (Local_u8_Command & 0b11110000) | (LCD_DATA_PORT & 0b00001111);
	 M_Dio_PinWrite(LCD_EN_PIN,HIGH);
	 _delay_ms(1);
	 M_Dio_PinWrite(LCD_EN_PIN,LOW);
	 _delay_ms(5);
	 #elif LCD_MODE == _4_BIT_MODE
	 M_Dio_PinWrite(LCD_RS_PIN,LOW);
	 LCD_DATA_PORT = (Local_u8_Command & 0b11110000) | (LCD_DATA_PORT & 0b00001111);
	 M_Dio_PinWrite(LCD_EN_PIN,HIGH);
	 _delay_ms(1);
	 M_Dio_PinWrite(LCD_EN_PIN,LOW);
	 _delay_ms(5);
	 LCD_DATA_PORT = (Local_u8_Command << 4) | (LCD_DATA_PORT & 0b00001111);
	 M_Dio_PinWrite(LCD_EN_PIN,HIGH);
	 _delay_ms(1);
	 M_Dio_PinWrite(LCD_EN_PIN,LOW);
	 _delay_ms(5);
	 #endif
}
void H_Lcd_WriteString(u8* Local_u8_Ptr)
{
	u8 Local_u8_Counter = 0;
	while(Local_u8_Ptr[Local_u8_Counter] != NULL_)
	{
		H_Lcd_WriteChar(Local_u8_Ptr[Local_u8_Counter]);
		Local_u8_Counter++;
	}
}
void H_Lcd_WriteNumber(s32 Local_s32_Number)
{
	u8 Local_u8_Arr [10] = {0};
	s8 Local_s8_Counter  = 0;
	u8 Local_u8_Digit    = 0;
	if(Local_s32_Number == 0)
	{
		H_Lcd_WriteChar('0');
	}
	else
	{
		if(Local_s32_Number < 0)
		{
			H_Lcd_WriteChar('-');
			Local_s32_Number = Local_s32_Number * -1;
		}
		while(Local_s32_Number != 0)
		{
			Local_u8_Digit = Local_s32_Number % 10;
			Local_u8_Arr[Local_s8_Counter] = Local_u8_Digit;
			Local_s8_Counter++;
			Local_s32_Number = Local_s32_Number / 10;
		}
		Local_s8_Counter--;
		while(Local_s8_Counter >= 0)
		{
			H_Lcd_WriteChar(Local_u8_Arr[Local_s8_Counter] + 48);
			Local_s8_Counter--;
		}
	}
}
void H_Lcd_Clear(void)
{
	H_Lcd_WriteCommand(LCD_CLEAR);
}