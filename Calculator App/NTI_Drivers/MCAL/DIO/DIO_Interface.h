/*
 * DIO_Interface.h
 *
 * Created: 10/17/2023 12:39:56 PM
 *  Author: M3gZ
 */ 


#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

typedef enum {
	LOW,
	HIGH
	}DIO_PIN_VOLT;
typedef enum{
	OUTPUT,
	INFREE,
	INPULL
}DIO_PinStatus_type;
typedef enum{
	PA=0,
	PB,
	PC,
	PD
}DIO_Port_type;
typedef enum{
	PINA0=0,
	PINA1=1,
	PINA2,
	PINA3,
	PINA4,
	PINA5,
	PINA6,
	PINA7,
	PINB0,	//8
	PINB1,
	PINB2,
	PINB3,
	PINB4,
	PINB5,
	PINB6,
	PINB7,
	PINC0,	//16
	PINC1,
	PINC2,
	PINC3,
	PINC4,
	PINC5,
	PINC6,
	PINC7,
	PIND0,	//24
	PIND1,
	PIND2,
	PIND3,
	PIND4,
	PIND5,
	PIND6,
	PIND7,
	TOTAL_PINS
}DIO_Pin_Num;

extern const DIO_PinStatus_type DIO_PinsStatusArr[TOTAL_PINS];	//this array is from the config file to be adjusted as the user pref.

void DIO_init (); //setting the direction of each pin using the array in the CFG file
void DIO_SetPinDirection(DIO_Pin_Num PN,DIO_PinStatus_type status);	// if the user want to change pin direction manually
void DIO_SetPin(DIO_Pin_Num P, DIO_PIN_VOLT volt);
DIO_PIN_VOLT DIO_ReadPin(DIO_Pin_Num PN);
void DIO_TogglePin(DIO_Pin_Num PN);
void DIO_SetPort(DIO_Port_type PT, u8 data);
DIO_Port_type DIO_ReadPort(DIO_Port_type PT);
void DIO_TogglePort(DIO_Port_type PT);
#endif /* DIO_INTERFACE_H_ */