/*
 * LDR.c
 *
 * Created: 10/23/2023 11:54:06 AM
 *  Author: M3gZ
 */ 
#include "../../LIB/Std_Types.h"
#include "LDR_Interface.h"
#include "../../CFG/LDR_CFG.h"
#include "../../MCAL/DIO/DIO_Interface.h"
#include "../../MCAL/ADC/ADC_Interface.h"

void LDR_Init()
{
	DIO_SetPinDirection(LDR_PIN,INPULL);
	DIO_SetPinDirection(LDR_GRN_PIN,OUTPUT);
	DIO_SetPinDirection(LDR_RED_PIN,OUTPUT);
	DIO_SetPinDirection(LDR_BLU_PIN,OUTPUT);
	DIO_SetPinDirection(LDR_YEL_PIN,OUTPUT);
}

//this func is gonna return the readings of the LDR in mv
//all these values are sent to the main to be diplayed on the screen
u16 LDR_Read()
{
	u16 volt_test=0;
	volt_test= ADC_VoltRead(LDR_Channel);
	
	if (volt_test>=4700)
	{
		DIO_SetPin(LDR_RED_PIN,HIGH);
		DIO_SetPin(LDR_GRN_PIN,LOW);
		DIO_SetPin(LDR_BLU_PIN,LOW);		
		DIO_SetPin(LDR_YEL_PIN,LOW);
	}
	else if (volt_test>=3700)
	{
		DIO_SetPin(LDR_RED_PIN,HIGH);
		DIO_SetPin(LDR_GRN_PIN,HIGH);
		DIO_SetPin(LDR_BLU_PIN,LOW);
		DIO_SetPin(LDR_YEL_PIN,LOW);
	}
	else if (volt_test>=2700)
	{
		DIO_SetPin(LDR_RED_PIN,HIGH);
		DIO_SetPin(LDR_GRN_PIN,HIGH);
		DIO_SetPin(LDR_BLU_PIN,HIGH);
		DIO_SetPin(LDR_YEL_PIN,LOW);
	}
	else
	{
		DIO_SetPin(LDR_RED_PIN,HIGH);
		DIO_SetPin(LDR_GRN_PIN,HIGH);
		DIO_SetPin(LDR_BLU_PIN,HIGH);
		DIO_SetPin(LDR_YEL_PIN,HIGH);
	}
	return volt_test;
}

u16 LDR_ASYNCH_Read(u16 ADC_val)
{
	ADC_val = (ADC_val*(u32)5000)/1024;
	if (ADC_val==50000)
	{
		//no reading yet
	}
	else if (ADC_val>=4400)
	{
		DIO_SetPin(LDR_RED_PIN,HIGH);
		DIO_SetPin(LDR_GRN_PIN,LOW);
		DIO_SetPin(LDR_BLU_PIN,LOW);
		DIO_SetPin(LDR_YEL_PIN,LOW);
	}
	else if (ADC_val>=3400)
	{
		DIO_SetPin(LDR_RED_PIN,HIGH);
		DIO_SetPin(LDR_GRN_PIN,HIGH);
		DIO_SetPin(LDR_BLU_PIN,LOW);
		DIO_SetPin(LDR_YEL_PIN,LOW);
	}
	else if (ADC_val>=2000)
	{
		DIO_SetPin(LDR_RED_PIN,HIGH);
		DIO_SetPin(LDR_GRN_PIN,HIGH);
		DIO_SetPin(LDR_BLU_PIN,HIGH);
		DIO_SetPin(LDR_YEL_PIN,LOW);
	}
	else
	{
		DIO_SetPin(LDR_RED_PIN,HIGH);
		DIO_SetPin(LDR_GRN_PIN,HIGH);
		DIO_SetPin(LDR_BLU_PIN,HIGH);
		DIO_SetPin(LDR_YEL_PIN,HIGH);
	}
	return ADC_val;
}