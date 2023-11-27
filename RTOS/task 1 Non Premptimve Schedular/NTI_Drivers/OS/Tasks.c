/*
 * Tasks.c
 *
 * Created: 11/27/2023 9:58:33 AM
 *  Author: M3gZ
 */ 

#include "Tasks.h"
#include "../LIB/Std_Types.h"
#include "../LIB/MemMap.h"
#include "../LIB/UTILS.h"
#include "../MCAL/DIO/DIO_Interface.h"
#include "../HAL/LCD/LCD_Interface.h"
#include "../MCAL/Timer/Timer_Interface.h"
#include "../Services/Timer_Serv/Timer_Serv.h"
#define  F_CPU   8000000
#include <util/delay.h>



void Task_2S_Blink(void)
{
	u8 *str[] = {"ON", "OFF"};
	DIO_TogglePin(PINC0);
	
	//clearing prev string
	LCD_Clear_Position(3,0,4);
	//blue led check status
	if (DIO_ReadPin(PINC0))
	{
		LCD_GoTo(3,0);
		LCD_WriteString(str[0]);
	}
	else
	{
		LCD_GoTo(3,0);
		LCD_WriteString(str[1]);
	}
}


void Task_1S_LcdUpdate(void)
{
	static u16 u16Seconds = 1;
	LCD_Clear_Position(1,10,5);
	LCD_GoTo(1,10);
	LCD_WriteNumber(u16Seconds);
	u16Seconds++;

}

void Task_3S_Blink(void)
{
	u8 *str[] = {"ON", "OFF"};
	DIO_TogglePin(PINC1);
	
	//clearing prev string
	LCD_Clear_Position(3,10,4);
	//blue led check status
	if (DIO_ReadPin(PINC1))
	{
		LCD_GoTo(3,10);
		LCD_WriteString(str[0]);
	}
	else
	{
		LCD_GoTo(3,10);
		LCD_WriteString(str[1]);
	}
}