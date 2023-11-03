/*
 * sevenSeg_CFG.h
 *
 * Created: 10/20/2023 9:49:08 AM
 *  Author: M3gZ
 */ 


#ifndef SEVENSEG_CFG_H_
#define SEVENSEG_CFG_H_

//BCD pins are PB0,PB1,PB2,PB3
#define DATA_BCD	PB

//to enable each one we need to enable and disable each one at a time
#define SEG_1		PINA3
#define SEG_2		PINA2
#define SEG_3		PINB6
#define SEG_4		PINB5

#endif /* SEVENSEG_CFG_H_ */