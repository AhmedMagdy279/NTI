/*
 * CyberSecurity.h
 *
 * Created: 11/11/2023 1:05:39 PM
 *  Author: M3gZ
 */ 


#ifndef CYBERSECURITY_H_
#define CYBERSECURITY_H_

typedef enum{
	DENIED=0,
	GRANTED
	}ACCESS_TYPE;

typedef enum{
	CS_FALSE=0,
	CS_TRUE,
	CS_REQUEST
}CS_BOOL;

void CS_Init();

CS_BOOL CS_ReceiveCom();
CS_BOOL CS_ReceiveEncrypted(u32 copy_Encrpt);
void CS_SendCom(u8 copy_Serv, u8 copy_u8Sub, u16 copy_Rout);
ACCESS_TYPE CS_getAccess();
void CS_ConvertString(u8 * str);
CS_BOOL CS_getStatus();
#endif /* CYBERSECURITY_H_ */