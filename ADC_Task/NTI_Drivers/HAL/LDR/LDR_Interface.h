/*
 * LDR_Interface.h
 *
 * Created: 10/23/2023 11:53:39 AM
 *  Author: M3gZ
 */ 


#ifndef LDR_INTERFACE_H_
#define LDR_INTERFACE_H_


void LDR_Init();

u16 LDR_Read();

u16 LDR_ASYNCH_Read(u16 ADC_val);


#endif /* LDR_INTERFACE_H_ */