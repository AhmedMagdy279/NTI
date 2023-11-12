/*
 * CyberSecurity.c
 *
 * Created: 11/11/2023 1:06:09 PM
 *  Author: M3gZ
 */ 

#include "../../LIB/Std_Types.h"
#include "../../MCAL/DIO/DIO_Interface.h"
#include "../../HAL/LCD/LCD_Interface.h"
#include "../../LIB/MemMap.h"
#include "CyberSecurity.h"
#include "stdlib.h"
#include "stdio.h"

#define SYMETRIC_KEY	0x10101010


volatile static u8 CS_Service;
volatile static u8 CS_Sub;
volatile static u16 CS_Routine;
volatile static u32 CS_KEY,CS_XOR_VAR=0xFFFFF,CS_RANDOM;
volatile static u8 CS_STATUS=CS_FALSE;		
volatile static u8 CS_ACCESS=DENIED;

void CS_Init()
{
	
}

static void CS_T1_u32Generator()
{
	CS_RANDOM= TCNT1 | ((u32)(TCNT1*4) << 8);
	
}

CS_BOOL CS_ReceiveCom()
{
	switch (CS_Service)
	{
		case 0x31:	//turn on led (check security access first)
		switch (CS_Sub)
		{
			case 0x01:
			if (CS_Routine == 0xAA00)
			{
				if(CS_ACCESS==DENIED)
				{
					LCD_Clear_Position(4,0,19);
					LCD_GoTo(4,0);
					LCD_WriteString("Request to ON LED");
					LCD_Clear_Position(2,0,20);
					LCD_GoTo(2,0);
					LCD_WriteString("NRC (7F 31 35)");//NRC access denied (7f 31 35)
					CS_STATUS=CS_TRUE;
					return CS_TRUE;
				}
				else
				{
					LCD_Clear_Position(4,0,19);
					LCD_GoTo(4,0);
					LCD_WriteString("Request to ON LED");
					LCD_Clear_Position(2,0,20);
					LCD_GoTo(2,0);
					LCD_WriteString("(71 01 AA 00)");
					DIO_SetPin(PINC0,HIGH);
					CS_STATUS=CS_TRUE;
					return CS_TRUE;
				}
				break;
			}
			
			default:
			CS_STATUS=CS_FALSE;
			return CS_FALSE;
		}
		
		
		case 0x27:	
		switch(CS_Sub)
		{
			case 0x01:	//01 to ask for security access
			LCD_Clear_Position(4,0,19);
			LCD_GoTo(4,0);
			LCD_WriteString("Access requested...");
			//access requested so we are sending the 4 random bytes
			CS_SendCom(0x67,0x01,0x0000);
			CS_STATUS=CS_REQUEST;
			return CS_REQUEST;
			break;
			case 0x02:	//02 to send the 4 encrypted bytes afterwards
						//afterwards the MC shall send one of two coms (6702 for OK, 7f2735 for NOK)
			if(CS_STATUS==CS_REQUEST)
			{
				//we need to check the XOR-ed value from the terminal then compare it to our value on the MC
				//we already have the value of the subroutine in the global variable
				if (CS_Routine == CS_XOR_VAR)
				{
					CS_STATUS=CS_TRUE;
					LCD_Clear_Position(4,0,20);
					LCD_GoTo(4,0);
					LCD_WriteString("Access granted.");
					CS_ACCESS=GRANTED;
					return CS_TRUE;
				}
			}
			else
			{
				LCD_Clear_Position(2,0,20);
				LCD_GoTo(2,0);
				LCD_WriteString("ask for request 1st");
				LCD_Clear_Position(4,0,20);
				LCD_GoTo(4,0);
				LCD_WriteString("chck encrypted bytes");
				return CS_REQUEST;
			}
			break;
			default:
			CS_STATUS=CS_FALSE;
			return CS_FALSE;
		}
		
		break;
		default:
		CS_STATUS=CS_FALSE;
		return CS_FALSE;
	}
}

void CS_SendCom(u8 copy_Serv, u8 copy_u8Sub, u16 copy_Rout)
{
	switch (copy_Serv)
	{
		case 0x67:	
		switch(copy_u8Sub)
		{
			case 0x01: //sending 4 random bytes afterwards and wait for 4 encrypted bytes
			
			LCD_Clear_Position(2,0,19);
			LCD_GoTo(2,0);
			LCD_WriteString("bytes: ");
			CS_T1_u32Generator();
			LCD_WriteHexU32(CS_RANDOM);
			//if you want a direct test case use the next variable 0x12005C48 instead of CS_RANDOM, the result is:
			//	0210 4C58
			//LCD_WriteString("0x12005C48");
			CS_XOR_VAR = (u32)(CS_RANDOM ^ SYMETRIC_KEY);
			
			break;
			
			default:
			CS_STATUS=CS_FALSE;
			return CS_FALSE;
		}
		
		break;
		default:
		CS_STATUS=CS_FALSE;
		return CS_FALSE;
	}
	return TRUE;
}



CS_BOOL CS_ReceiveEncrypted(u32 copy_Encrpt)
{
	if(CS_STATUS==CS_REQUEST)
	{
		//we need to check the XOR-ed value from the terminal then compare it to our value on the MC
		//we already have the value of the subroutine in the global variable
		if (copy_Encrpt == CS_XOR_VAR)
		{
			CS_STATUS=CS_TRUE;
			LCD_Clear_Position(4,0,20);
			LCD_GoTo(4,0);
			LCD_WriteString("Encrypted 4 bytes");
			LCD_Clear_Position(2,0,20);
			LCD_GoTo(2,0);
			LCD_WriteString("Access granted(6702)");
			CS_ACCESS=GRANTED;
			return CS_TRUE;
		}
		else
		{
			LCD_Clear_Position(4,0,20);
			LCD_GoTo(4,0);
			LCD_WriteString("NRC (7F 27 35)");
		}
	}
	else
	{
		LCD_Clear_Position(4,0,20);
		LCD_GoTo(4,0);
		LCD_WriteString("Request Access 1st");
		return CS_REQUEST;
	}
	
}

void CS_ConvertString(u8 * str)
{
	//we need to divide each two digits from the string
	//from 8 digits we need:
	//					2 digits service
	//					2 digits subservice
	//					4 digits routine
	// Extract substrings
	char aa[3];    // 2 characters for 'aa' + 1 for service
	char bb[3];    // 2 characters for 'bb' + 1 for subservice
	char cccc[5];  // 4 characters for 'cccc' + 1 for routine and in requesting access it's gonna be the encrypted 4 bytes
	char dddd[9];
	if (CS_STATUS==CS_TRUE || CS_STATUS==CS_FALSE)
	{
		strncpy(aa, str, 2);
		aa[2] = '\0';

		strncpy(bb, str + 2, 2);
		bb[2] = '\0';

		strncpy(cccc, str + 4, 4);
		cccc[4] = '\0';
		// Convert substrings to desired data types
		CS_Service = (u8) strtol(aa, NULL, 16);
		CS_Sub = (u8) strtol(bb, NULL, 16);
		CS_Routine = (u16) strtol(cccc, NULL, 16);
	}
	else if (CS_STATUS==CS_REQUEST)
	{
		strncpy(aa, str, 2);
		aa[2] = '\0';

		strncpy(bb, str + 2, 2);
		bb[2] = '\0';

		strncpy(dddd, str + 4, 8);
		dddd[8] = '\0';
		// Convert substrings to desired data types
		CS_Service = (u8)strtol(aa, NULL, 16);
		CS_Sub = (u8)strtol(bb, NULL, 16);
		CS_KEY = (u32)strtol(dddd, NULL, 16);
		CS_ReceiveEncrypted(CS_KEY);
	}
	
}

ACCESS_TYPE CS_getAccess()
{
	return CS_ACCESS;
}

CS_BOOL CS_getStatus()
{
	return CS_STATUS;
}