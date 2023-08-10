/*
 * ExternalEeprom.c
 *
 * Created: 8/9/2023 5:03:18 PM
 *  Author: Khaled_Waleed_Samir_Metwally
 */ 

#include "ExternalEeprom.h"


void H_Eeprom_Init(void)
{
	M_Twi_Init();
	_delay_ms(2000);
}
void H_Eeprom_Write(u8 Local_u8_Data ,u8 Local_u8_PageAddress ,u8 Local_u8_ByteAddress)
{
	M_Twi_StartCondition();
	M_Twi_SendSlaveAddressWrite(0x50 | Local_u8_PageAddress);
	M_Twi_SendByte(Local_u8_ByteAddress);
	M_Twi_SendByte(Local_u8_Data);
	M_Twi_StopCondition();
}
u8   H_Eeprom_Read(u8 Local_u8_PageAddress ,u8 Local_u8_ByteAddress)
{
	u8 Local_u8_Data = 0;
	M_Twi_StartCondition();
	M_Twi_SendSlaveAddressWrite(0x50 | Local_u8_PageAddress);
	M_Twi_SendByte(Local_u8_ByteAddress);
	M_Twi_RepeatedStart();
	M_Twi_SendSlaveAddressRead(0x50 | Local_u8_PageAddress);
	Local_u8_Data = M_Twi_ReadByte();
	M_Twi_StopCondition();
	return Local_u8_Data;
}