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


#define F_CPU 8000000
#include <util/delay.h>


/*////////////////////////////////////////////////lcd 7amoksha story // done////////////////////////////////////////////////*/
int main()
{
	DIO_Init();
	LCD_Init();
	
	while(1)
	{
		u8 str  [8]= {0x4, 0xe, 0x1f, 0x1f, 0x1f, 0x1f, 0xe, 0x4};
		
		for (int i=0;i<20;i++)
		{
			LCD_CustomChar(0,str);
			LCD_GoTo(1,i++);
			LCD_WriteChar(0);
			_delay_ms(200);
		}
		LCD_GoTo(2,0);
		LCD_WriteString("Once upon a time, a"); 
		LCD_GoTo(3,0);
		LCD_WriteString("traveler on a quest ");
		LCD_GoTo(4,0);
		LCD_WriteString("to find hidden loot ");
		_delay_ms(3000); 
		
		LCD_CLR();
		for (int i=0;i<20;i++)
		{
			LCD_CustomChar(0,str);
			LCD_GoTo(1,i++);
			LCD_WriteChar(0);
			_delay_ms(200);
		}
		LCD_GoTo(2,0);
		LCD_WriteString("with mysterious mark");
		LCD_GoTo(3,0);
		LCD_WriteString("Long story short, he");
		LCD_GoTo(4,0);
		LCD_WriteString("found it in a cavexD");
		_delay_ms(3000);
		LCD_CLR();
		for (int i=0;i<20;i++)
		{
			LCD_CustomChar(0,str);
			LCD_GoTo(1,i++);
			LCD_WriteChar(0);
			LCD_GoTo(4,i++);
			LCD_WriteChar(0);
			_delay_ms(100);
		}
		LCD_GoTo(2,0);
		LCD_WriteString("Have a wonderful day");
		LCD_GoTo(3,10);
		LCD_WriteString(":)");
		_delay_ms(3000);
		LCD_CLR();
		
	}
}
