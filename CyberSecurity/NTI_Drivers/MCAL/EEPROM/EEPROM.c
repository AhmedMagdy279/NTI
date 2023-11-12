/*
 * EEPROM.c
 *
 * Created: 11/3/2023 9:56:55 AM
 *  Author: M3gZ
 */ 


#include "../../LIB/Std_Types.h"
#include "../../LIB/MemMap.h"
#include "../../LIB/Utils.h"
#include "EEPROM_Interface.h"


static void (*EEPROM_Fptr)(void) = NULLPTR;


void EEPROM_Init(void)
{
}


void EEPROM_Write(u16 address,u8 data)
{
	while(READ_BIT(EECR,EEWE));
	Global_INT_Disable;
	EEAR=address;
	EEDR=data;
	SET_BIT(EECR,EEMWE);
	SET_BIT(EECR,EEWE);
	Global_INT_Enable;
}
u8 EEPROM_Read(u16 address)
{
	while(READ_BIT(EECR,EEWE));
	EEAR=address;
	SET_BIT(EECR,EERE);
	return EEDR;
}

/********EEPROM Interrupt Funcs**********/

void EEPROM_InterruptEnable(void)
{
	SET_BIT(EECR,EERIE);
}
void EEPROM_InterruptDisable(void)
{
	CLR_BIT(EECR,EERIE);
}
void EEPROM_InterruptSetCallBack(void (*local_fptr)(void))
{
	EEPROM_Fptr=local_fptr;
}

ISR(EE_RDY_vect)
{
	if (EEPROM_Fptr!=NULLPTR)
	{
		EEPROM_Fptr();
	}
}