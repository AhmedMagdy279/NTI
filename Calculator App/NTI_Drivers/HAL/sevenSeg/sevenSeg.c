/*
 * sevenSeg.c
 *
 * Created: 10/20/2023 9:48:31 AM
 *  Author: M3gZ
 */ 
#include "../../LIB/Std_Types.h"
#include "../../LIB/UTILS.h"
#include "../../MCAL/DIO/DIO_Interface.h"
#include "sevenSeg_Interface.h"
#include "../../CFG/sevenSeg_CFG.h"
#define F_CPU 8000000
#include <util/delay.h>

static const u8 SevenSegBCD4Bits[10] = {	//we can use #define to optimize the code to the max (try later)
    0b0000, // 0
    0b0001, // 1
    0b0010, // 2
    0b0011, // 3
    0b0100, // 4
    0b0101, // 5
    0b0110, // 6
    0b0111, // 7
    0b10000, // 8
    0b10001  // 9
};

void SEG_Disable_All()
{
	DIO_SetPin(SEG_1,HIGH);
	DIO_SetPin(SEG_2,HIGH);
	DIO_SetPin(SEG_3,HIGH);
	DIO_SetPin(SEG_4,HIGH);
}

void SEG_init()
{
	SEG_Disable_All();
}



void SEG_Display(u16 data)
{
	//calculations for each number
	u8 d4 = data/1000;
	u8 d3 = (data/100)%10;
	u8 d2 = (data /10)%10;
	u8 d1 = data % 10;
	
	
	//sending the value to the display port (EACH AT A TIME)
	DIO_SetPort(DATA_BCD,SevenSegBCD4Bits[d1]);
	SEG_Disable_All();	//disable all then
	DIO_SetPin(SEG_1,LOW);		// Enable the first display
	_delay_ms(5);
	
	DIO_SetPort(DATA_BCD,SevenSegBCD4Bits[d2]);
	SEG_Disable_All();	//disable all then
	DIO_SetPin(SEG_2,LOW);		// Enable the second display
	_delay_ms(5);
	
	DIO_SetPort(DATA_BCD,SevenSegBCD4Bits[d3]);
	SEG_Disable_All();	//disable all then
	DIO_SetPin(SEG_4,LOW);		// Enable the 3rd display
	_delay_ms(5);
	
	DIO_SetPort(DATA_BCD,SevenSegBCD4Bits[d4]);
	SEG_Disable_All();	//disable all then
	DIO_SetPin(SEG_3,LOW);		// Enable the fourth display
	_delay_ms(5);
	
	
	
	SEG_Disable_All();
}
