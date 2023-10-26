/*
 * UTILS.h
 *
 * Created: 10/17/2023 12:38:08 PM
 *  Author: M3gZ
 */ 


#ifndef UTILS_H_
#define UTILS_H_

#define  READ_BIT(reg,bit)  ((reg>>bit)&1)
#define  READ_BIT2(reg,bit)  (reg&(1<<BIT))
#define  SET_BIT(reg,bit)   (reg=reg|(1<<bit))
#define  CLR_BIT(reg,bit)   (reg=reg&(~(1<<bit)))
#define  TOG_BIT(reg,bit)   (reg=reg^(1<<bit))


#endif /* UTILS_H_ */