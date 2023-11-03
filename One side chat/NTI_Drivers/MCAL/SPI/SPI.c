/*
 * SPI.c
 *
 * Created: 10/30/2023 10:42:07 AM
 *  Author: M3gZ
 */ 

#include "../../LIB/Std_Types.h"
#include "../../LIB/MemMap.h"
#include "../../LIB/Utils.h"
#include "SPI.h"

static void(*SPI_Fptr)(void)=NULLPTR;

void SPI_Init(SPIMode_type mode)
{
	if (mode==MASTER)
	{
		//clock 2MHZ
		SET_BIT(SPCR,MSTR);
	}
	else
	{
		CLR_BIT(SPCR,MSTR);
	}
	
	// SPI ENABLE
	SET_BIT(SPCR,SPE);
	
	//SPI Interrupt enable
	SET_BIT(SPCR,SPIE);
	
}


u8 SPI_SendReceive(u8 data)
{
	SPDR=data;
	while(!READ_BIT(SPSR,SPIF));
	return SPDR;
}


u8 SPI_ReceivePerodic(u8*pdata)
{
	if (READ_BIT(SPSR,SPIF))
	{
		*pdata=SPDR;
		return 1;
	}
	return 0;
}

void SPI_SendNoBlock(u8 data)
{
	SPDR=data;
}
u8 SPI_ReceiveNoBlock()
{
	return SPDR;
}

void SPI_voidSetCallBack( void (*PtrToFunc) (void) )
{
	SPI_Fptr = PtrToFunc;
}

ISR(SPI_STC_vect)
{
	if (SPI_Fptr!=NULLPTR)
	{
		SPI_Fptr();
	}
}