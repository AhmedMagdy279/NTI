/*
 * SPI.h
 *
 * Created: 10/30/2023 10:43:22 AM
 *  Author: M3gZ
 */ 

#ifndef SPI_H_
#define SPI_H_

typedef enum{
	MASTER,
	SLAVE
}SPIMode_type;


void SPI_Init(SPIMode_type mode);

u8 SPI_SendReceive(u8 data);
u8 SPI_ReceivePerodic(u8*pdata);
void SPI_SendNoBlock(u8 data);
void SPI_voidSetCallBack( void (*PtrToFunc) (void) );
u8 SPI_ReceiveNoBlock();

#endif /* SPI_H_ */