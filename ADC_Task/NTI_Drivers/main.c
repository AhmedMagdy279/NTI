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
#include "HAL/LDR/LDR_Interface.h"
#include "HAL/LM35/LM35_Interface.h"
#include "MCAL/Timer/Timer_Interface.h"
#define F_CPU 8000000
#include <util/delay.h>

///*////////////////////////LDR (light dependatent resistor)	&& LM35 (temprature sensor)//done//////////////////////////////////////
void LDR_INTERRUPT();
void LM35_INTERRUPT();
void Sensors_Reading_Chain();
void EXT_INT1_Trigger();
void EXT_INT2_Trigger();
void EXT_INT3_Trigger();
#define SENSORS_NUM	3
volatile u8 Sensors_count=0;
volatile u16 Readings_Arr[SENSORS_NUM];
volatile u8 Sensors_Flags[SENSORS_NUM];
int main()
{
				
	DIO_Init();
	LCD_Init();
	ADC_Init(VREF_AVCC,ADC_SCALER_64);
	LDR_Init();
	LM35_Init();
	
	//			USING CHAIN INTERRUPT	
	
	LCD_WriteString("NTI ADC Project");
	LCD_GoTo(2,0);
	LCD_WriteString("We will only show:");
	LCD_GoTo(3,0);
	LCD_WriteString("LDR>2700mv & LM35>70");
	LCD_GoTo(4,0);
	LCD_WriteString("Sensor3>3000 mv");
	_delay_ms(5000);
	EXI_Init();
	EXI_SetCallBack(EX_INT0,EXT_INT1_Trigger);
	EXI_Enable(EX_INT0);
	EXI_SetCallBack(EX_INT1,EXT_INT2_Trigger);
	EXI_Enable(EX_INT1);
	EXI_SetCallBack(EX_INT2,EXT_INT3_Trigger);
	EXI_Enable(EX_INT2);
	ADC_StartConversion_INT(CH_0);
	ADC_SetInterruptCallBack(Sensors_Reading_Chain);
	Global_INT_Enable;
	while (1)
	{
		LCD_CLR();
		if(LDR_ASYNCH_Read(Readings_Arr[0])>2700)
		{
			Sensors_Flags[0]=1;
			DIO_SetPin(PINA7,HIGH);
			DIO_SetPin(PIND2,HIGH);
		}

		if(LM35_TakeRead(Readings_Arr[1])>70)
		{
			Sensors_Flags[1]=1;
			DIO_SetPin(PINA7,HIGH);
			DIO_SetPin(PIND3,HIGH);
		}
		Readings_Arr[2] = (Readings_Arr[2]*(u32)5000)/1024;
		if(Readings_Arr[2]>3000)
		{
			Sensors_Flags[2]=1;
			DIO_SetPin(PINA7,HIGH);
			DIO_SetPin(PINB2,HIGH);
		}
		if(Sensors_Flags[0]==0 && Sensors_Flags[1]==0 && Sensors_Flags[2]==0 )
			DIO_SetPin(PINA7,LOW);
		_delay_ms(500);
	}

	return 0;
}

void Sensors_Reading_Chain()
{
	if (Sensors_count==SENSORS_NUM-1)
	{
		Readings_Arr[Sensors_count]=ADC_GetReadNoblock();
		Sensors_count=0;
		ADC_StartConversion_INT(Sensors_count);
	}
	else
	{
		Readings_Arr[Sensors_count]=ADC_GetReadNoblock();
		Sensors_count++;
		ADC_StartConversion_INT(Sensors_count);
	}
}

void EXT_INT1_Trigger()
{
	if (Sensors_Flags[0])
	{
		LCD_GoTo(3,0);
		LCD_WriteString("LDR");
		LCD_GoTo(4,0);
		LCD_WriteNumber(LDR_ASYNCH_Read(Readings_Arr[0]));
		Sensors_Flags[0]=0;
	}
	DIO_SetPin(PIND2,LOW);
}
void EXT_INT2_Trigger()
{
	if (Sensors_Flags[1])
	{
		LCD_GoTo(3,8);
		LCD_WriteString("LM35");
		LCD_GoTo(4,8);
		LCD_WriteNumber(LM35_TakeRead(Readings_Arr[1]));
		Sensors_Flags[1]=0;
	}
	DIO_SetPin(PIND3,LOW);
}
void EXT_INT3_Trigger()
{
	if (Sensors_Flags[2])
	{
		LCD_GoTo(3,16);
		LCD_WriteString("Sns3");
		LCD_GoTo(4,16);
		LCD_WriteNumber(Readings_Arr[2]);
		Sensors_Flags[2]=0;
	}
	DIO_SetPin(PINB2,LOW);
}
//*/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
