/*
 * Lcd.h
 *
 * Created: 7/16/2023 9:30:07 AM
 *  Author: Khaled_Waleed_Samir_Metwally
 */ 


#ifndef LCD_H_
#define LCD_H_

// Includes
#include "LcdCfg.h"
#include "StdTypes.h"
#include "Dio.h"
#define F_CPU 16000000UL
#include <util/delay.h>

// Macros
#define _8_BIT_MODE                 1
#define _4_BIT_MODE                 2
#define LCD_DISPLAY_ON_CURSOR_OFF 0x0C
#define LCD_CLEAR                 0x01
#define LCD_RETURN_HOME           0x02
#define LCD_8BIT_MODE             0x38
#define LCD_4BIT_MODE_1           0x33
#define LCD_4BIT_MODE_2           0x32
#define LCD_4BIT_MODE_3           0x28
#define NULL_ '\0'

// Functions Prototypes
void H_Lcd_Init(void);
void H_Lcd_WriteChar(u8);
void H_Lcd_WriteCommand(u8);
void H_Lcd_WriteString(u8*);
void H_Lcd_WriteNumber(s32);
void H_Lcd_Clear(void);



#endif /* LCD_H_ */