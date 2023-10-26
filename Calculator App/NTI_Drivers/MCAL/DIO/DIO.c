/*
 * DIO.c
 *
 * Created: 10/17/2023 12:40:19 PM
 *  Author: M3gZ
 */ 
#include "../../LIB/Std_Types.h"
#include "../../LIB/MemMap.h"
#include "../../LIB/UTILS.h"
#include "DIO_Interface.h"
#include "DIO_Private.h"
#include "../../CFG/DIO_CFG.h"


void DIO_SetPinDirection(DIO_Pin_Num PN,DIO_PinStatus_type status)
{
	u8 pinNUM = PN % 8;
	DIO_Port_type portNUM = PN / 8;
	
	switch(status)
	{
		case OUTPUT:
		switch(portNUM)
		{
			case PA:
			SET_BIT(DDRA,pinNUM);
			CLR_BIT(PORTA,pinNUM);
			break;
			case PB:
			SET_BIT(DDRB,pinNUM);
			CLR_BIT(PORTB,pinNUM);
			break;
			case PC:
			SET_BIT(DDRC,pinNUM);
			CLR_BIT(PORTC,pinNUM);
			break;
			case PD:
			SET_BIT(DDRD,pinNUM);
			CLR_BIT(PORTD,pinNUM);
			break;
		}
		break;
		case INFREE:
		switch(portNUM)
		{
			case PA:
			CLR_BIT(DDRA,pinNUM);
			CLR_BIT(PORTA,pinNUM);
			break;
			case PB:
			CLR_BIT(DDRB,pinNUM);
			CLR_BIT(PORTB,pinNUM);
			break;
			case PC:
			CLR_BIT(DDRC,pinNUM);
			CLR_BIT(PORTC,pinNUM);
			break;
			case PD:
			CLR_BIT(DDRD,pinNUM);
			CLR_BIT(PORTD,pinNUM);
			break;
		}
		break;
		case INPULL:
		switch(portNUM)
		{
			case PA:
			CLR_BIT(DDRA,pinNUM);
			SET_BIT(PORTA,pinNUM);
			break;
			case PB:
			CLR_BIT(DDRB,pinNUM);
			SET_BIT(PORTB,pinNUM);
			break;
			case PC:
			CLR_BIT(DDRC,pinNUM);
			SET_BIT(PORTC,pinNUM);
			break;
			case PD:
			CLR_BIT(DDRD,pinNUM);
			SET_BIT(PORTD,pinNUM);
			break;
		}
		break;
	}
}

void DIO_Init()
{
	for (DIO_Pin_Num i=0;i<TOTAL_PINS;i++)
		DIO_SetPinDirection(i,DIO_PinsStatusArr[i]);
}


void DIO_SetPin(DIO_Pin_Num PN, DIO_PIN_VOLT volt)
{
	u8 pinNUM = PN % 8;
	DIO_Port_type portNUM = PN / 8;
	switch(portNUM)
	{
		case PA:
		if(READ_BIT(DDRA,pinNUM))
		{
			switch(volt)
			{
				case LOW:
				CLR_BIT(PORTA,pinNUM);
				break;
				case HIGH:
				SET_BIT(PORTA,pinNUM);
				break;
			}
		}
		break;
		case PB:
		if(READ_BIT(DDRB,pinNUM))
		{
			switch(volt)
			{
				case LOW:
				CLR_BIT(PORTB,pinNUM);
				break;
				case HIGH:
				SET_BIT(PORTB,pinNUM);
				break;
			}
		}
		break;
		case PC:
		if(READ_BIT(DDRC,pinNUM))
		{
			switch(volt)
			{
				case LOW:
				CLR_BIT(PORTC,pinNUM);
				break;
				case HIGH:
				SET_BIT(PORTC,pinNUM);
				break;
			}
		}
		break;
		case PD:
		if(READ_BIT(DDRD,pinNUM))
		{
			switch(volt)
			{
				case LOW:
				CLR_BIT(PORTD,pinNUM);
				break;
				case HIGH:
				SET_BIT(PORTD,pinNUM);
				break;
			}
		}
		break;
	}
}

DIO_PIN_VOLT DIO_ReadPin(DIO_Pin_Num PN)
{
	u8 pinNUM = PN % 8;
	DIO_Port_type portNUM = PN / 8;
	switch(portNUM)
	{
		case PA:
		if (READ_BIT(PINA,pinNUM))
		return HIGH;
		else
		return LOW;
		break;
		
		case PB:
		if (READ_BIT(PINB,pinNUM))
		return HIGH;
		else
		return LOW;
		break;
		
		case PC:
		if (READ_BIT(PINC,pinNUM))
		return HIGH;
		else
		return LOW;
		break;
		
		case PD:
		if (READ_BIT(PIND,pinNUM))
		return HIGH;
		else
		return LOW;
		break;
		
		default:
		return LOW;
	}
}

void DIO_TogglePin(DIO_Pin_Num PN)
{
	u8 pinNUM = PN % 8;
	DIO_Port_type portNUM = PN / 8;

	switch(portNUM)
	{
		case PA:
		if(READ_BIT(PORTA,pinNUM))
		DIO_SetPin(PN,LOW);
		else
		DIO_SetPin(PN,HIGH);
		break;
		case PB:
		if(READ_BIT(PORTB,pinNUM))
		DIO_SetPin(PN,LOW);
		else
		DIO_SetPin(PN,HIGH);
		break;
		case PC:
		if(READ_BIT(PORTC,pinNUM))
		DIO_SetPin(PN,LOW);
		else
		DIO_SetPin(PN,HIGH);
		break;
		case PD:
		if(READ_BIT(PORTD,pinNUM))
		DIO_SetPin(PN,LOW);
		else
		DIO_SetPin(PN,HIGH);
		break;
	}
}

void DIO_SetPort(DIO_Port_type PT, u8 data)
{
	switch(PT)
	{
		case PA:
		PORTA = data;
		break;
		case PB:
		PORTB = data;
		break;
		case PC:
		PORTC = data;
		break;
		case PD:
		PORTD = data;
		break;
	}
}
DIO_Port_type DIO_ReadPort(DIO_Port_type PT)
{
	switch(PT)
	{
		case PA:
		return PINA;
		break;
		case PB:
		return PINB;
		break;
		case PC:
		return PINC;
		break;
		case PD:
		return PIND;
		break;
		
		default:
		return 0;
	}
}

void DIO_TogglePort(DIO_Port_type PT)
{
	switch(PT)
	{
		case PA:
		PORTA ^= 0xFF;
		break;
		case PB:
		PORTB ^= 0xFF;
		break;
		case PC:
		PORTC ^= 0xFF;
		break;
		case PD:
		PORTD ^= 0xFF;
		break;
	}
}
