/*
 * Password.c
 *
 * Created: 11/3/2023 10:20:41 AM
 *  Author: M3gZ
 */
#include "../../LIB/Std_Types.h"
#include "../../HAL/LCD/LCD_Interface.h"
#include "../../HAL/EXT_EEPROM/EXT_EEPROM.h"
#include "../../MCAL/EEPROM/EEPROM_Interface.h"
#define F_CPU 8000000
#include <util/delay.h>
 
//creating default password for the app, it's better to be written on the eeprom to keep the password when the power cuts off
static u8 pass[4] = {0};

//Writing on EEPROM INDX
static u8 EINDX	=0;


void Pass_Init(void)
{
	/*EEPROM_init();
	//EEPROM_readByte(0x0040+EIchck,&chck);*/
	if (EEPROM_Read(4)==255)
	{
		for (EINDX=0;EINDX<4;EINDX++)
		{
			
			EEPROM_Write(EINDX,0);
		}
	}
	//start with the password
	LCD_CLR();
	LCD_GoTo(1,0);
	LCD_WriteString("Pass: ");
	PassView();
	LCD_WriteString(" okay?");
	LCD_GoTo(2,0);
	LCD_WriteString("yes(+)     no(-)");
	while(1)
	{
		u8 key=KeyPad_getKey();
		if (key=='-')
		{
			Pass_Change();
			break;
		}
		else if (key=='+')
		break;
	}
	LCD_CLR();
	LCD_GoTo(1,0);
	LCD_WriteString("Initiation done");
	LCD_GoTo(2,0);
	LCD_WriteString("starting....");
	_delay_ms(300);
	LCD_CLR();
}
static void TMPPASSVIEW()
{
	for (EINDX=0;EINDX<4;EINDX++)
	{
		LCD_WriteNumber(pass[EINDX]);
	}
}
void PassView(void)
{
	for (EINDX=0;EINDX<4;EINDX++)
	{
		pass[EINDX]=EEPROM_Read(EINDX);
		LCD_WriteNumber(pass[EINDX]);
		/*u8 error = EEPROM_readByte(0x0040+EINDX,&pass+EINDX);
		if (error== 0)
		{	
			LCD_WriteString("ERROR");
		}*/
	}
}

void Pass_Change(void)
{
	u8 pass_key, verified=0;
	//we are copying the old password data in case the user decided not to change it mid-process
	//we might use another solution that the user can work on another variable then when done we can
	//copy the new values to the global variable it can save one loop in the CODE SIZE
	u8 def_pass[4];
	for (u8 i=0;i<4;i++)
	def_pass[i]=pass[i];
	
	LCD_CLR();
	LCD_GoTo(2,0);
	LCD_WriteString("to cancel 'C'");
	LCD_GoTo(1,0);
	LCD_WriteString("[    ] new pass");
	LCD_GoTo(1,1);
	PassView();
	LCD_GoTo(1,1);
	while(verified<4)
	{
		pass_key=KeyPad_getKey();
		if (pass_key=='0' || pass_key=='1' || pass_key=='2' || pass_key=='3' || pass_key=='4' || pass_key=='5' || pass_key=='6' || pass_key=='7' || pass_key=='8' || pass_key=='9')
		{
			pass[verified]=pass_key-'0';
			LCD_GoTo(1,1);
			TMPPASSVIEW();
			LCD_GoTo(1,(1+verified));
			verified++;
		}
		else if (pass_key=='=' || pass_key=='/' || pass_key=='*' || pass_key=='-' || pass_key=='+')
		{
			verified=0;
			LCD_GoTo(1,1);
			pass[0]=0;
			pass[1]=0;
			pass[2]=0;
			pass[3]=0;
			TMPPASSVIEW();
			LCD_GoTo(1,1);
		}
		else if (pass_key=='C')
		{
			LCD_CLR();
			LCD_GoTo(1,0);
			LCD_WriteString("Change canceled");
			LCD_GoTo(2,0);
			LCD_WriteString("pass: [    ]");
			LCD_GoTo(2,7);
			for (u8 i=0;i<4;i++)
			pass[i]=def_pass[i];
			TMPPASSVIEW();
			_delay_ms(300);
			break;
		}
		
		if (verified>=4)
		{
			LCD_CLR();
			LCD_GoTo(1,0);
			LCD_WriteString("Pass changed");
			LCD_GoTo(2,0);
			LCD_WriteString("pass: [    ]");
			LCD_GoTo(2,7);
			TMPPASSVIEW();
			for (EINDX=0;EINDX<4;EINDX++)
			{
				EEPROM_Write(EINDX , pass[EINDX]);
				/*u8 error = EEPROM_writeByte(0x0040+EINDX,pass[EINDX]);
				if (error== 0)
				{
					LCD_WriteString("ERROR");
				}*/
			}
			EEPROM_Write(4 , 1);
			/*EEPROM_writeByte(0x0040+EIchck,chck);*/
			_delay_ms(3000);
			break;
		}
	}
}