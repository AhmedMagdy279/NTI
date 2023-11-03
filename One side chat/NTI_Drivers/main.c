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
#include "MCAL/ADC/ADC_Interface.h"
#include "MCAL/UART/UART_Interface.h"
#include "MCAL/SPI/SPI.h"
#define F_CPU 8000000
#include <util/delay.h>

//////////////////////////////////  Debugger-UART-AVR1-SPI-AVR2 /////////////////////////////////////////////////////////

//				MASTER
//avr 1 (receive from debugger through UART and send to AVR2 through SPI)

void UART_Receive_Func();
int main()
{
	DIO_Init();
	LCD_Init();
	LCD_WriteString("Master Here!");
	UART_Init();
	SPI_Init(MASTER);
	Global_INT_Enable;
	UART_RX_SetCallBack(UART_Receive_Func);
	UART_RX_InterruptEnable();
	while(1)
	{
		
	}
}
void UART_Receive_Func()
{
	u8 receive=UART_Receive();
	SPI_SendReceive(receive);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*				SLAVE
//avr 2 receive from SPI and Show on LCD

//// SLAVE CODE
void SPI_ISR_SndRcv();
volatile u8 flag=0,receive;
int main ()
{
	DIO_Init();
	LCD_Init();
	KeyPad_Init();
	LCD_WriteString("Slave Here!");
	LCD_GoTo(2,0);
	SPI_Init(SLAVE);
	SPI_voidSetCallBack(SPI_ISR_SndRcv);
	Global_INT_Enable;
	while (1)
	{
		if (flag)
		{
			LCD_WriteChar(receive);
			flag=0;
		}
	}
}

void SPI_ISR_SndRcv()
{
	receive=SPI_ReceiveNoBlock();
	flag=1;
	
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/