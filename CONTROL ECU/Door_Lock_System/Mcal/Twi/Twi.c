/*
 * Twi.c
 *
 * Created: 8/9/2023 4:45:36 PM
 *  Author: Khaled_Waleed_Samir_Metwally
 */ 

#include "Twi.h"

void M_Twi_Init(void)
{
	#if   TWI_MODE == TWI_MASTER
	TWBR = 12;         //to select FSCL = 400KHz
	#elif TWI_MODE == TWI_SLAVE
	TWAR = 0b00000010; //to select slave address 1, and disable general call recognition
	#endif
	
	SetBit(TWCR,2);    //to enable TWI circuit
}
void M_Twi_StartCondition(void)
{
	SetBit(TWCR,5);
	SetBit(TWCR,7);                //to clear the flag
	while ((GetBit(TWCR,7)) == 0);
	while ((TWSR & 0xF8) != START_ACK);   //F8 is 11111000 to make sure that the last 3 bits are 0
}
void M_Twi_SendSlaveAddressWrite(u8 Local_u8_Address)
{
	TWDR = (Local_u8_Address << 1); /*shift 1 left because 0000000 0 first 7 bits is the slave address and last bit is to select
	                                  either we want to read or write*/
	ClrBit(TWCR,5);
	SetBit(TWCR,7);                //to clear the flag
	while ((GetBit(TWCR,7)) == 0);
	while ((TWSR & 0xF8) != SLAVE_AD_AND_WR_ACK);
}
void M_Twi_SendSlaveAddressRead(u8 Local_u8_Address)
{
	TWDR = (Local_u8_Address << 1) | 1; //OR with 1 to make sure last bit is 1 to read and not write
	ClrBit(TWCR,5);
	SetBit(TWCR,7);                //to clear the flag
	while ((GetBit(TWCR,7)) == 0);
	while ((TWSR & 0xF8) != SLAVE_AD_AND_RD_ACK);
}
void M_Twi_SendByte(u8 Local_u8_Data)
{
	TWDR = Local_u8_Data;
	ClrBit(TWCR,5);              //as per data sheet this bit must be set to 0 via software
	SetBit(TWCR,7);                //to clear the flag
	while ((GetBit(TWCR,7)) == 0);
	while ((TWSR & 0xF8) != WR_BYTE_ACK);
}
u8   M_Twi_ReadByte(void)
{
	ClrBit(TWCR,5);
	ClrBit(TWCR,4);
	SetBit(TWCR,6);  
	SetBit(TWCR,7);       //to clear the flag
	while ((GetBit(TWCR,7)) == 0);
	while ((TWSR & 0xF8) != RD_BYTE_WITH_ACK);
	return TWDR;
}
void M_Twi_RepeatedStart(void)
{
	SetBit(TWCR,5);
	SetBit(TWCR,7);                //to clear the flag
	while ((GetBit(TWCR,7)) == 0);
	while ((TWSR & 0xF8) != REP_START_ACK);
}
void M_Twi_StopCondition(void)
{
	SetBit(TWCR,4);
	SetBit(TWCR,7);                //to clear the flag
	//while ((GetBit(TWCR,7))== 0);
}
void M_Twi_Ack(void)
{
	SetBit(TWCR,6);
	SetBit(TWCR,7);                //to clear the flag
	while ((GetBit(TWCR,7)) == 0);
}