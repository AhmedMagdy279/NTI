/*
 * TWI.c
 *
 * Created: 11/3/2023 10:02:13 AM
 *  Author: M3gZ
 */ 
#include "../../LIB/Std_Types.h"
#include "../../LIB/MemMap.h"
#include "../../LIB/Utils.h"
#include "../DIO/DIO_Interface.h"
#include "TWI_Interface.h"
void TWI_init(const TWI_ConfigType * Config_Ptr)
{
    /*  Bit Rate: 400.000 kbps and insert the required  pre-scaler value in the two three bits  TWPS1,TWPS2 and F_CPU=8Mhz */
    TWBR = 0x02;
	TWSR = (TWSR & 0XFC)|(Config_Ptr->prescaler);
	
    /* Two Wire Bus address my address if any master device want to call me: (used in case this MC is a slave device)
       General Call Recognition: Off */
	
    TWAR = Config_Ptr-> adress_slave; // insert the required  address slave value

    TWCR = (1<<TWEN); /* enable TWI */
}

void TWI_start(void)
{
    /* 
	 * Clear the TWINT flag before sending the start bit TWINT=1
	 * send the start bit by TWSTA=1
	 * Enable TWI Module TWEN=1 
	 */
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    
    /* Wait for TWINT flag set in TWCR Register (start bit is send successfully) */
    while(READ_BIT(TWCR,TWINT)==LOW);
}

void TWI_stop(void)
{
    /* 
	 * Clear the TWINT flag before sending the stop bit TWINT=1
	 * send the stop bit by TWSTO=1
	 * Enable TWI Module TWEN=1 
	 */
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

void TWI_write(u8 data)
{
    /* Put data On TWI data Register */
    TWDR = data;
    /* 
	 * Clear the TWINT flag before sending the data TWINT=1
	 * Enable TWI Module TWEN=1 
	 */ 
    TWCR = (1 << TWINT) | (1 << TWEN);
    /* Wait for TWINT flag set in TWCR Register(data is send successfully) */
    while(READ_BIT(TWCR,TWINT)==LOW);
}

u8 TWI_readWithACK(void)
{
	/* 
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable sending ACK after reading or receiving data TWEA=1
	 * Enable TWI Module TWEN=1 
	 */ 
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
    /* Wait for TWINT flag set in TWCR Register (data received successfully) */
    while(READ_BIT(TWCR,TWINT)==LOW);
    /* Read Data */
    return TWDR;
}

u8 TWI_readWithNACK(void)
{
	/* 
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable TWI Module TWEN=1 
	 */
    TWCR = (1 << TWINT) | (1 << TWEN);
    /* Wait for TWINT flag set in TWCR Register (data received successfully) */
    while(READ_BIT(TWCR,TWINT)==LOW);
    /* Read Data */
    return TWDR;
}

u8 TWI_getStatus(void)
{
    u8 status;
    /* masking to eliminate first 3 bits and get the last 5 bits (status bits) */
    status = TWSR & 0xF8;
    return status;
}


