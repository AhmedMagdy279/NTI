/*
 * EXT_EEPROM.h
 *
 * Created: 11/3/2023 10:13:13 AM
 *  Author: M3gZ
 */ 

#ifndef EXTERNAL_EEPROM_H_
#define EXTERNAL_EEPROM_H_

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
#define ERROR 0
#define SUCCESS 1

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void EEPROM_init(void);
u8 EEPROM_writeByte(u16 u16addr,u8 u8data);
u8 EEPROM_readByte(u16 u16addr,u8 *u8data);


#endif /* EXTERNAL_EEPROM_H_ */