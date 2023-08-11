/*
 * ExternalEeprom.c
 *
 * Created: 8/9/2023 5:03:18 PM
 *  Author: Khaled_Waleed_Samir_Metwally
 */ 

#include "ExternalEeprom.h"
#include "Leds.h"

void H_Eeprom_Init(void)
{
	M_Twi_Init();
	//_delay_ms(1000);
}
void H_Eeprom_Write(u8 Local_u8_Data, u16 Local_u16_ByteAddress)
{
	M_Twi_StartCondition();
	M_Twi_SendByte((u8)(0xA0 | ((Local_u16_ByteAddress & 0x0700)>>7)));
	M_Twi_SendByte((u8)Local_u16_ByteAddress);
	M_Twi_SendByte(Local_u8_Data);
	M_Twi_StopCondition();
}
u8   H_Eeprom_Read(u16 Local_u16_ByteAddress)
{
	u8 Local_u8_Data = 0;
	M_Twi_StartCondition();
	M_Twi_SendByte((u8)((0xA0) | ((Local_u16_ByteAddress & 0x0700)>>7)));
	M_Twi_SendByte((u8)Local_u16_ByteAddress);
	M_Twi_StartCondition();
	M_Twi_SendByte((u8)((0xA0) | ((Local_u16_ByteAddress & 0x0700)>>7) | 1));
	Local_u8_Data = M_Twi_ReadByte();
	M_Twi_StopCondition();
	return Local_u8_Data;
}