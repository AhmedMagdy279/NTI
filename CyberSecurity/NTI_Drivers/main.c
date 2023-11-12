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
#include "MCAL/Timer/Timer_Interface.h"
#include "MCAL/UART/UART_Interface.h"
#include "Services/UART_Serv/UART_Serv.h"
#include "APP/CyberSecurity/CyberSecurity.h"
#define F_CPU 8000000
#include <util/delay.h>

//////////////////////////////////  Cyber Security Task /////////////////////////////////////////////////////////

volatile static u8 strg_tmp[8], encrpt[12];
int main()
{
	DIO_Init();
	LCD_Init();
	UART_Init();
	CS_Init();
	//we are gonna init timer 1 only to use random number from timer 1
	Timer1_Init(TIMER1_NORMAL_MODE,TIMER1_SCALER_64);
	
	LCD_WriteString("MC Response: ");
	LCD_GoTo(3,0);
	LCD_WriteString("MC Receive: ");
	while (1)
	{
		//here we wait to receive the command to either:
		//1) turn on led
		//2) ask for security access
		while (1)
		{
			UART_ReceiveString(strg_tmp);
			CS_ConvertString(strg_tmp);
			CS_ReceiveCom();
			if( CS_getStatus() == CS_FALSE)
			{
				LCD_Clear_Position(4,0,19);
				LCD_GoTo(4,0);
				LCD_WriteString("Failed... Try again");
			}
			else
				break;
		}
		///////////////////////////////////////////////////
		while (CS_getStatus()==CS_REQUEST)
		{
			UART_ReceiveString(encrpt);
			CS_ConvertString(encrpt);
			if (CS_getAccess()==GRANTED)
			break;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
