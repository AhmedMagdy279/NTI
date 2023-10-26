#include "../../LIB/Std_Types.h"
#include "../../MCAL/DIO/DIO_Interface.h"
#include "KeyPad_Interface.h"
#include "../../CFG/KeyPad_CFG.h"
#define  F_CPU   8000000
#include <util/delay.h>

void KeyPad_Init(void)
{
	//after configuring all the needed pins in the DIO_Cfg.c we can start from here
	//to start the keypad
	for (u8 i=0;i<ROWS;i++)
	{
		DIO_SetPin(FirstTrigger-i,HIGH);
	}
}
u8 KeyPad_getKey()
{
	u8 key=NO_KEY;
	for (u8 i=0;i<ROWS;i++)
	{
		DIO_SetPin(FirstTrigger-i,LOW);
		for (u8 j=0; j<COLS+1;j++)
		{
			if (DIO_ReadPin(FirstReceiver-j)==LOW && j!=3)
			{
				key= Keys_ARR[i][j];
				_delay_ms(10);
				while(DIO_ReadPin(FirstReceiver-j)==LOW);
				_delay_ms(10);
			}
		}
		DIO_SetPin(FirstTrigger-i,HIGH);
	}
	return key;
}