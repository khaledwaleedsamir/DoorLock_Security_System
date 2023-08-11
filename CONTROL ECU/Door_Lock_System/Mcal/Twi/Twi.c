/*
 * Twi.c
 *
 * Created: 8/9/2023 4:45:36 PM
 *  Author: Khaled_Waleed_Samir_Metwally
 */ 

#include "Twi.h"
#include <avr/io.h>

void M_Twi_Init(void)
{
	#if   TWI_MODE   ==   TWI_MASTER
	TWBR = 12;                      // to select fscl = 400 khz
	#elif TWI_MODE   ==   TWI_SLAVE
	TWAR = 0b00000010;             // to select the slave add. = 1 , and disable general call rec.
	#endif
	SetBit(TWCR,2);                // to enable TWI circuit
}
void M_Twi_StartCondition(void)
{
	/*
	 * Clear the TWINT flag before sending the start bit TWINT=1
	 * send the start bit by TWSTA=1
	 * Enable TWI Module TWEN=1
	 */
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

	/* Wait for TWINT flag set in TWCR Register (start bit is send successfully) */
	while(GetBit(TWCR,TWINT) == 0);

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
	/* Put data On TWI data Register */
	TWDR = Local_u8_Data;
	/*
	 * Clear the TWINT flag before sending the data TWINT=1
	 * Enable TWI Module TWEN=1
	 */
	TWCR = (1 << TWINT) | (1 << TWEN);
	/* Wait for TWINT flag set in TWCR Register(data is send successfully) */
	while(GetBit(TWCR,TWINT) == 0);
	
}
u8   M_Twi_ReadByte(void)
{
	/*
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable TWI Module TWEN=1
	 */
	TWCR = (1 << TWINT) | (1 << TWEN);
	/* Wait for TWINT flag set in TWCR Register (data received successfully) */
	while(GetBit(TWCR,TWINT) == 0);
	/* Read Data */
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
	/*
	 * Clear the TWINT flag before sending the stop bit TWINT=1
	 * send the stop bit by TWSTO=1
	 * Enable TWI Module TWEN=1
	 */
	TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}
void M_Twi_Ack(void)
{
	SetBit(TWCR,6);
	SetBit(TWCR,7);                //to clear the flag
	while ((GetBit(TWCR,7)) == 0);
}