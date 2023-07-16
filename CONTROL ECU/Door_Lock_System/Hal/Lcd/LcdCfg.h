/*
 * LcdCfg.h
 *
 * Created: 7/16/2023 9:30:19 AM
 *  Author: Khaled_Waleed_Samir_Metwally
 */ 


#ifndef LCDCFG_H_
#define LCDCFG_H_

// Lcd Pins Selection
#define LCD_DATA_PORT PORTA

#define LCD_DATA0_PIN PA0
#define LCD_DATA1_PIN PA1
#define LCD_DATA2_PIN PA2
#define LCD_DATA3_PIN PA3
#define LCD_DATA4_PIN PA4
#define LCD_DATA5_PIN PA5
#define LCD_DATA6_PIN PA6
#define LCD_DATA7_PIN PA7

#define LCD_RS_PIN PB1
#define LCD_RW_PIN PB2
#define LCD_EN_PIN PB3

// Lcd mode Selection 
/* Available modes are :
1) 4-Bits Mode
2) 8-Bits Mode        */
#define LCD_MODE  _4_BIT_MODE



#endif /* LCDCFG_H_ */