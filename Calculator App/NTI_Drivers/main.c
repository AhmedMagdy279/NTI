/*
 * NTI_Drivers.c
 *
 * Created: 10/17/2023 12:36:20 PM
 * Author : M3gZ
 */ 

#include "LIB/Std_Types.h"
#include "LIB/UTILS.h"
#include "LIB/MemMap.h"
#include "MCAL/DIO/DIO_Interface.h"
#include "HAL/sevenSeg/sevenSeg_Interface.h"
#include "HAL/LCD/LCD_Interface.h"
#include "HAL/KeyPad/KeyPad_Interface.h"
#include "APP/Calculator/Calculator.h"
#define F_CPU 8000000
#include <util/delay.h>

/////////////////////////////////////calculator test//done////////////////////////////////
int main()
{
	DIO_Init();
	LCD_Init();
	KeyPad_Init();
	Calculator_Init();
		
	while(1)
	{
		Calculator_Operation();
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

