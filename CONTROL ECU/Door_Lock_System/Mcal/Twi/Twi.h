/*
 * Twi.h
 *
 * Created: 8/9/2023 4:45:51 PM
 *  Author: Khaled_Waleed_Samir_Metwally
 */ 


#ifndef TWI_H_
#define TWI_H_

// Includes
#include "TwiCfg.h"
#include "StdTypes.h"
#include "BitMaths.h"
#include "Reg.h"

// Macros
#define TWI_MASTER 1
#define TWI_SLAVE  2

#define START_ACK                     0x08		// start has been sent
#define REP_START_ACK                 0x10		// repeated start
#define SLAVE_AD_AND_WR_ACK           0x18		// master transmit [ slave address + write request ] ACK
#define SLAVE_AD_AND_RD_ACK           0x40		// master transmit [ slave address + read  request ] ACK
#define WR_BYTE_ACK                   0x28		// master transmit data ACK
#define WR_BYTE_NACK                  0x30		// master transmit data NACK
#define RD_BYTE_WITH_ACK			  0x50		// master received data with  ACK
#define RD_BYTE_WITH_NACK			  0x58		// master received data with NACK
#define SLAVE_ADD_REC_RD_REQ		  0xA8		// slave address received with write request
#define SLAVE_ADD_REC_WR_REQ          0x60		// slave address received with read  request
#define SLAVE_DATA_REC                0x80		// read  byte request received
#define SLAVE_BYTE_TRANSMITTED        0xC0		// write byte request received

// Functions Prototypes
void M_Twi_Init(void);
void M_Twi_StartCondition(void);
void M_Twi_SendSlaveAddressWrite(u8);
void M_Twi_SendSlaveAddressRead(u8);
void M_Twi_SendByte(u8);
u8   M_Twi_ReadByte(void);
void M_Twi_RepeatedStart(void);
void M_Twi_StopCondition(void);
void M_Twi_Ack(void);

#endif /* TWI_H_ */