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
#include "HAL/LCD/LCD_Interface.h"
#include "MCAL/EXT_INT/EXT_INT_Interface.h"
#include "MCAL/ADC/ADC_Interface.h"
#include "HAL/LM35/LM35_Interface.h"
#include "MCAL/Timer/Timer_Interface.h"
#include "MCAL/SPI/SPI.h"
#include "Services/Timer_Serv/Timer_Serv.h"
#define F_CPU 8000000
#include <util/delay.h>

//////////////////////////////////  MASTER(AVR1)<--SPI-->SLAVE(AVR2)<->LM35 /////////////////////////////////////////////////////////
//avr 1 is gonna be used to receive LM35 readings from MC2 every 5 seconds. However if the temp is more than 50 degrees, MC2 is gonna
//trigger EXTI INT0 pin for 5ms 

void Receive_Reading();
void EXT_INT0_Trigger();
volatile u8 reading,override;
int main()
{
	EXI_SetCallBack(EX_INT0,EXT_INT0_Trigger);
	DIO_Init();
	LCD_Init();
	//Safe call
	EXI_Init();
	EXI_Enable(EX_INT0);
	Global_INT_Enable;
	SPI_Init(MASTER);
	LCD_GoTo(1,0);
	LCD_WriteString("LM35 readings");
	LCD_GoTo(2,0);
	LCD_WriteString("Reading:     degrees");
	Timer1_SetInterruptTime_s (5,Receive_Reading);
	
	//the following 2 lines are only for the first reading error
	_delay_ms(300);
	SPDR=0;
	while(1)
	{
		
		if (override)
		{
			EXI_Disable(EX_INT0);
			LCD_GoTo(4,0);
			LCD_WriteString("Overheat");
		}
		if (reading<50 && override)
		{
			override=0;
			EXI_Enable(EX_INT0);
			LCD_Clear_Position(4,0,10);
		}
		LCD_Clear_Position(2,9,3);
		LCD_GoTo(2,9);
		LCD_WriteNumber(reading);
		_delay_ms(50);
	}
}
void Receive_Reading()
{
	reading=SPI_SendReceive('G');
}
void EXT_INT0_Trigger()
{
	override=1;
	reading=SPI_SendReceive('A');
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////