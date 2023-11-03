#include "../../LIB/Std_Types.h"
#include "../../LIB/MemMap.h"
#include "../../LIB/UTILS.h"
#include "ADC_Interface.h"
#define  F_CPU   8000000
#include <util/delay.h>

static u8 ADC_BusyFlag;

static void (*ADC_Fptr) (void)= NULLPTR;

/*			Not working init
void ADC_Init (ADC_VoltRef_type vref, ADC_Prescaler_type scaler)
{
	//vref 
	switch(vref)
	{
		case VREF_AREF:
		CLR_BIT(ADMUX,REFS0);
		CLR_BIT(ADMUX,REFS1);
		break;
		case VREF_AVCC:
		SET_BIT(ADMUX,REFS0);
		CLR_BIT(ADMUX,REFS1);
		break;
		case VREF_256V:
		SET_BIT(ADMUX,REFS0);
		SET_BIT(ADMUX,REFS1);
		break;
	}
	
	//prescaler 
	
	ADCSRA &=0XF8;
	scaler &=0X07;
	
	ADCSRA = ADCSRA|scaler;
	
	// enable ADC
	SET_BIT(ADCSRA,ADEN);
	
	//enable ADC interrupt
	SET_BIT(ADCSRA,ADIE);

}
*/
	void ADC_Init (ADC_VoltRef_type vref, ADC_Prescaler_type scaler)
{
	/* vref */
	switch(vref)
	{
		case VREF_AREF:
		CLR_BIT(ADMUX,REFS0);
		CLR_BIT(ADMUX,REFS1);
		break;
		case VREF_AVCC:
		SET_BIT(ADMUX,REFS0);
		CLR_BIT(ADMUX,REFS1);
		break;
		case VREF_256V:
		SET_BIT(ADMUX,REFS0);
		SET_BIT(ADMUX,REFS1);
		break;
	}
	
	/* prescaler */
	
	ADCSRA &=0XF8;
	scaler &=0X07;
	
	ADCSRA = ADCSRA|scaler;
	
	/* enable ADC*/
	SET_BIT(ADCSRA,ADEN);
	
	//enable ADC interrupt
	SET_BIT(ADCSRA,ADIE);

}

void ADC_StartConversion(ADC_Channel_type CH)
{
	if (ADC_BusyFlag==0)
	{
		//first we need to clear the channel bits that we are gonna get the data on
		ADMUX&=0XE0;//11100000
		ADMUX|=(CH & 0x07);
		
		//then we start conversion
		//ADCSRA |= (1<<ADSC);
		SET_BIT(ADCSRA,ADSC);
		
		//we are gonna use polling instead of blocking
		//ADC_BusyFlag=1;

	}
	
	
	//busy wait until conversion ends
	while(READ_BIT(ADCSRA,ADSC));		//this line shall be in the ADC_READ and busy flag replacing it
}

u16 ADC_Read(ADC_Channel_type CH)
{
	u16 ADC_value=0;
	//conversion is in the main function and we should add busy flag
	ADC_StartConversion(CH);
	
	//add the data after conversion ends
	/* IF adle==0*/
	ADC_value  = ADCL;
	ADC_value |= (ADCH << 8);
	/* IF adle==1*/
	//u16 adc=ADCL>>6;
	//adc=adc|ADCH<<2;
	
	
	return ADC_value;
}

/* return mv*/
u16 ADC_VoltRead(ADC_Channel_type CH)
{
	u16 adc=ADC_Read(CH);
	u16 Vout_mV = (adc *(u32) 5000) / 1024;
	return Vout_mV;
}

u8 ADC_GetReadPerodic(u16*pdata)
{
	/* perodic ckeck  (polling)*/
	
	if (!READ_BIT(ADCSRA,ADSC))
	{
		*pdata=ADC;
		ADC_BusyFlag=0;
		return 1;
	}
	return 0;
	
}
u16 ADC_GetRead(void)
{
	
	/*get read*/
	//u16 adc=ADCL;
	//adc=adc|(ADCH<<8);
	/* IF adle==1*/
	//u16 adc=ADCL>>6;
	//adc=adc|ADCH<<2;
	/* w8 ADC finish busy wait( blocking )**/
	while(READ_BIT(ADCSRA,ADSC));
	return ADC;
}
u16 ADC_GetReadNoblock(void)
{
	return ADC;
}

void ADC_StartConversion_INT(ADC_Channel_type CH)
{
	if (ADC_BusyFlag==0)
	{
		/*setting Interrupt enable and auto trigger as well*/
		SET_BIT(ADCSRA,ADIE);
		//SET_BIT(ADCSRA,ADATE);	//commented for chain test code
		/* set channel mux*/
		ADMUX&=0XE0;//11100000
		ADMUX|=CH;
		
		/*start conversion*/
		SET_BIT(ADCSRA,ADSC);
		
		ADC_BusyFlag=1;
	}
}
u16 ADC_Read_INT(void)
{
	u16 adc;
	adc=ADC_GetReadNoblock();
	return adc;
	
}
void ADC_SetInterruptCallBack(void (*LocalPtr)(void))
{
	ADC_Fptr=LocalPtr;
}


ISR (ADC_vect)
{
	ADC_BusyFlag=0;
	if (ADC_Fptr!=NULLPTR)
	{
		ADC_Fptr();
	}
}
