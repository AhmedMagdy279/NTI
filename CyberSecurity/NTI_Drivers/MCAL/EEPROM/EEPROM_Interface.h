/*
 * EEPROM_Interface.h
 *
 * Created: 11/3/2023 9:57:13 AM
 *  Author: M3gZ
 */ 

#ifndef EEPROM_INTERFACE_H_
#define EEPROM_INTERFACE_H_


void EEPROM_Init(void);

void EEPROM_Write(u16 address,u8 data);
u8 EEPROM_Read(u16 address);


/********EEPROM Interrupt Funcs**********/
void EEPROM_InterruptEnable(void);
void EEPROM_InterruptDisable(void);
void EEPROM_InterruptSetCallBack(void (*local_fptr)(void));



#endif /* EEPROM_INTERFACE_H_ */