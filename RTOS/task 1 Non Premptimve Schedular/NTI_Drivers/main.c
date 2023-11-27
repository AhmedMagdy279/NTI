

#include "LIB/Std_Types.h"
#include "LIB/UTILS.h"
#include "LIB/MemMap.h"
#include "MCAL/DIO/DIO_Interface.h"
#include "HAL/LCD/LCD_Interface.h"
#include "MCAL/Timer/Timer_Interface.h"
#include "Services/Timer_Serv/Timer_Serv.h"
#include "OS/OS.h"
#include "OS/Tasks.h"
#define F_CPU 8000000
#include <util/delay.h>

//////////////////////////////////  RTOS //////////////////////////////////////////////////////////

// ISR Callback (not used anymore)
void vMillisIncrement(void)
{
	static u16 u16_100uSecCounter = 0;
	static u16 u16_millisCounter = 0;
	u16_100uSecCounter++;

	if(u16_100uSecCounter >= 10)
	{
		u16_100uSecCounter = 0;
		u16_millisCounter++;
	}

	if(u16_millisCounter >= 1000)
	{
		// To be called every 1 Sec
		OS_Task_Handler();
		// Reset u16_millisCounter
		u16_millisCounter = 0;
		
		// Execute the scheduler
		OS_TaskExecution();
		
	}

}

// ISR Callback (always used)
void OS_Increrment(void)
{
	// To be called every 1 Sec
	OS_Task_Handler();
	
	// Execute the scheduler
	OS_TaskExecution();
}

void vInitEcu(void)
{
	u8 *str[] = {"Seconds: ", "BLUE      RED"};

	DIO_Init();
	DIO_SetPinDirection(PINC0,OUTPUT);
	DIO_SetPinDirection(PINC1,OUTPUT);

	DIO_SetPin(PINC0,LOW);
	DIO_SetPin(PINC1,LOW);

	LCD_Init();
	//line 1 for task 1 counter
	LCD_WriteString(str[0]);
	
	//line 2 & 3 for updating task 2 & 3 status
	LCD_GoTo(2,0);
	LCD_WriteString(str[1]);
}

void InitScheduler(void)
{
	// task created with (function, periodicity, starting state, first delay)
	OS_TaskCreate(Task_1S_LcdUpdate,1,BLOCKED,0);
	OS_TaskCreate(Task_2S_Blink,2,BLOCKED,4);
	OS_TaskCreate(Task_3S_Blink,3,BLOCKED,0);
	
	//TIMER0_Init(TIMER0_NORMAL_MODE, TIMER0_SCALER_8);
	//TIMER0_OC0Mode(OC0_DISCONNECTED);
	//TIMER0_OV_InterruptEnable();
	//TIMER0_OC_InterruptEnable();
}



int main(void)
{
	// Sw initilaization
	vInitEcu();

	// Start the Scheduler
	InitScheduler();
	
	//set the tick time then enable global interrupt
	Timer1_SetInterruptTime_s(1 , OS_Increrment);
	Global_INT_Enable;
	while(1)
	{
		
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////