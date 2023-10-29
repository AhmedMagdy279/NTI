/*
 * LM35_Interface.h
 *
 * Created: 10/23/2023 1:16:48 PM
 *  Author: M3gZ
 */ 


#ifndef LM35_INTERFACE_H_
#define LM35_INTERFACE_H_

void LM35_Init();

u8 LM35_Read();

u8 LM35_TakeRead(u16 READ);

#endif /* LM35_INTERFACE_H_ */