#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

//ADC for atmega 32 works between 50 kHz and 200 kHz. If a lower resolution than 10 bits is needed, the input
//clock frequency to the ADC can be higher than 200 kHz to get a higher sample rate.
//so the Prescalar for 8 MHz to operate good is gotta be --> ADPS2:0 = 110 = 64  which gives us 125  kHz -->clck cycle:8 micro seconds
//														 --> ADPS2:0 = 111 = 128 which gives us 62.5 kHz -->clck cycle:16 micro seconds
//									   or for lower res: --> ADPS2:0 = 101 = 32	 which gives us 250  kHz -->clck cycle:4 micro seconds
typedef enum{
	ADC_SCALER_2=1,
	ADC_SCALER_4,
	ADC_SCALER_8,
	ADC_SCALER_16,
	ADC_SCALER_32,
	ADC_SCALER_64,
	ADC_SCALER_128,
}ADC_Prescaler_type;

//to adjust the voltage reference type that we use in the driver we use REFS1:0
//				----> 00 = AREF, Internal Vref turned off (connect external to AREF pin)
//				----> 01 = AVCC with external capacitor at AREF pin (connect the VCC to the AREF pin)
//				----> 11 = Internal 2.56V Voltage Reference with external capacitor at AREF pin
typedef enum{
	VREF_AREF,
	VREF_AVCC,
	VREF_256V
}ADC_VoltRef_type;

//in atmega 32 we got 7 channels from PINA0 ~ PINA7
typedef enum{
	CH_0=0,
	CH_1,
	CH_2,
	CH_3,
	CH_4,
	CH_5,
	CH_6,
	CH_7
}ADC_Channel_type;


void ADC_Init(ADC_VoltRef_type vref,ADC_Prescaler_type scaler);
u16 ADC_Read(ADC_Channel_type CH);
/* return mv*/
u16 ADC_VoltRead(ADC_Channel_type CH);
void ADC_StartConversion(ADC_Channel_type CH);
u8 ADC_GetReadPerodic(u16*pdata);
u16 ADC_GetRead(void);
u16 ADC_GetReadNoblock(void);

/*using interrupt*/
void ADC_StartConversion_INT(ADC_Channel_type CH);
u16 ADC_Read_INT(void);
void ADC_SetInterruptCallBack(void (*LocalPtr)(void));

#endif /* ADC_INTERFACE_H_ */