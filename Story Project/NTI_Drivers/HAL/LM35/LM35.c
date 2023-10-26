/*
 * LM35.c
 *
 * Created: 10/23/2023 1:16:58 PM
 *  Author: M3gZ
 */ 

#include "../../LIB/Std_Types.h"
#include "LM35_Interface.h"
#include "../../CFG/LM35_CFG.h"
#include "../../MCAL/DIO/DIO_Interface.h"
#include "../../MCAL/ADC/ADC_Interface.h"

void LM35_Init()
{
	DIO_SetPinDirection(LM35_PIN,INPULL);
}

u8 LM35_Read()
{
	u8 temp;
	u16 volt= ADC_VoltRead(LM35_Channel);
	temp = volt>1500? 150 : volt/10; 
	
	return temp;
}