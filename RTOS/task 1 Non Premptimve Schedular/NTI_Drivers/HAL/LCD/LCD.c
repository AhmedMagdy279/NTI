#include "../../LIB/Std_Types.h"
#include "../../LIB/UTILS.h"
#include "LCD_Interface.h"
#include "../../MCAL/DIO/DIO_Interface.h"
#include "../../CFG/LCD_CFG.h"
#define  F_CPU   8000000
#include <util/delay.h>


#if USE_4_BIT
////////////////////////// m5rita's code / 4 PIN LCD
static void LCD_Instruction(u8 ins)
{
	DIO_SetPin(LCD_RS,LOW);					//setting RS to 0 to send instruction
	//sending the 4 MSB first
	DIO_SetPin(LCD_D7,READ_BIT(ins,7));		
	DIO_SetPin(LCD_D6,READ_BIT(ins,6));
	DIO_SetPin(LCD_D5,READ_BIT(ins,5));
	DIO_SetPin(LCD_D4,READ_BIT(ins,4));
	
	DIO_SetPin(LCD_EN,HIGH);
	_delay_ms(1);
	DIO_SetPin(LCD_EN,LOW);
	_delay_ms(1);
	
	//sending the 4 LSB first
	DIO_SetPin(LCD_D7,READ_BIT(ins,3));
	DIO_SetPin(LCD_D6,READ_BIT(ins,2));
	DIO_SetPin(LCD_D5,READ_BIT(ins,1));
	DIO_SetPin(LCD_D4,READ_BIT(ins,0));
	
	DIO_SetPin(LCD_EN,HIGH);
	_delay_ms(1);
	DIO_SetPin(LCD_EN,LOW);
	_delay_ms(1);
}

static void LCD_WriteData(u8 data)
{
	DIO_SetPin(LCD_RS,HIGH);				//setting RS to 1 to send Data
	DIO_SetPin(LCD_D7,READ_BIT(data,7));
	DIO_SetPin(LCD_D6,READ_BIT(data,6));
	DIO_SetPin(LCD_D5,READ_BIT(data,5));
	DIO_SetPin(LCD_D4,READ_BIT(data,4));
	
	DIO_SetPin(LCD_EN,HIGH);
	_delay_ms(1);
	DIO_SetPin(LCD_EN,LOW);
	_delay_ms(1);
	
	DIO_SetPin(LCD_D7,READ_BIT(data,3));
	DIO_SetPin(LCD_D6,READ_BIT(data,2));
	DIO_SetPin(LCD_D5,READ_BIT(data,1));
	DIO_SetPin(LCD_D4,READ_BIT(data,0));
	
	DIO_SetPin(LCD_EN,HIGH);
	_delay_ms(1);
	DIO_SetPin(LCD_EN,LOW);
	_delay_ms(1);
	
}

void LCD_Init(void)
{
	//wait for more than 30ms for VDD to rise to 4.5v
	_delay_ms(50);
	//using 4 bit configuration the used register is as follows:
	//		RS-RW-DB7-DB6-DB5-DB4-xxxx
	
	//Step 1:
	//so sending function set:
	LCD_Instruction(0x02);
	
	//Step 2:
	//displaying ON/OFF control
	//now you can choose for any of the following when displaying on:
	// 0x0C for no cursor and no blink for it	(D:1)
	// 0x0E for cursor with no blink			(D:1 , C:1)
	// 0x0F for cursor and with blink			(D:1 , C:1 , B:1)
	
	//Step 2a: Display off
	LCD_Instruction(0x28);
	//Step 2b: Display on
	LCD_Instruction(0x0c);
	
	//Step 3: Clearing screen
	LCD_Instruction(0x01);
	_delay_ms(1);
	LCD_Instruction(0x06);
}

void LCD_CLR()
{
	LCD_Instruction(0x01);
	_delay_ms(1);
	//LINE1_Cell=1;
	//Line2_CELL=1;
}

void LCD_GoTo(u8 line, u8 cell)
{
	if (line==1)
	{
		LCD_Instruction(0x80+cell);
	}
	else if (line==2)
	{
		LCD_Instruction(0x80+0x40+cell);	// 0xC0: Sets cursor to line 2 of display	+ cell
	}																					
	else if (line==3)																	
	{																					
		LCD_Instruction(0x80+0x14+cell);	// 0x94: Sets cursor to line 3 of display	+ cell
	}																					
	else if (line==4)																	
	{																					
		LCD_Instruction(0x80+0x54+cell);	// 0xD4: Sets cursor to line 4 of display	+ cell
	}
}



void LCD_WriteChar(u8 ch)
{
	LCD_WriteData(ch);
}

void LCD_WriteString(u8* str)
{
	u8 i;
	for(i=0;str[i];i++)
		LCD_WriteData(str[i]);
}

void LCD_WriteNumber(u32 num)
{
	c8 str[20];
	u8 i=0;
	s8 j;
	if (num==0)
	{
		LCD_WriteChar('0');
		return ;
	}
	if (num<0)
	{
		LCD_WriteChar('-');
		num=num*(-1);
	}
	
	while(num)
	{
		str[i]=num%10 +'0';
		i++;
		num=num/10;
	}
	for (j=i-1;j>=0;j--)
	{
		LCD_WriteChar(str[j]);
	}
	//LCD_WriteString(str);
	
	/*u8 indx=11, tmpString[indx];
	
	tmpString[indx]='\0';
	while(num>0)
	{
		indx--;
		s32 tmp=num % 10;
		num/=10;
		tmpString[indx]=tmp+'0';
	}
	
	for (;tmpString[indx];indx++)
	{
		LCD_WriteData(tmpString[indx]);
	}
	*/
}
void LCD_WriteBinary(u8 num)
{
	u8 indx=9, tmpString[indx];
	
	tmpString[indx]='\0';
	indx=0;
	
	for (u8 i=1<<7 ; i>0; i/=2)
	{
		if (num & i) 
			tmpString[indx]='1';
		else 
			tmpString[indx]='0';
		indx++;
	}
	indx=0;
	for (;tmpString[indx];indx++)
	{
		LCD_WriteData(tmpString[indx]);
	}
}
void LCD_WriteHex(s32 num)
{
	u8 indx=11, tmpString[indx];
	
	tmpString[indx]='\0';
	while(num>0)
	{
		indx--;
		s32 tmp=num % 16;
		num/=16;
		if (tmp>=10)
		{
			switch (tmp)
			{
				case 10:
				tmpString[indx]=65;		//A
				break;
					
				case 11: 
				tmpString[indx]=66;		//B
				break;
				
				case 12:
				tmpString[indx]=67;		//C
				break;
				
				case 13:
				tmpString[indx]=68;		//D
				break;
				
				case 14:
				tmpString[indx]=69;		//E
				break;
				
				case 15:
				tmpString[indx]=70;		//F
				break;
			}	
		}
		else
			tmpString[indx]=tmp+'0';
	}
	
	for (;tmpString[indx];indx++)
	{
		LCD_WriteData(tmpString[indx]);
	}
}

void LCD_WriteHexU32(u32 num) {
	u8 indx = 11, counter = 0;
	char tmpString[indx];

	tmpString[indx] = '\0';

	do {
		indx--;
		u32 tmp = num % 16;

		if (tmp >= 10) {
			tmpString[indx] = tmp - 10 + 'A';
			} else {
			tmpString[indx] = tmp + '0';
		}

		num /= 16;
		counter++;
	} while (num > 0 && indx > 0);

	for (u8 i = 0; i < 8 - counter; i++) {
		LCD_WriteData('0');
	}

	for (; indx < 11; indx++) {
		LCD_WriteData(tmpString[indx]);
	}
}



void LCD_CustomChar(u8 address,u8* customchar)
{
	u8 i;
	if(address<8)
	{
		LCD_Instruction(0x40+(address*8));
		for(i=0;i<8;i++)
		{
			_delay_ms(1);
			LCD_WriteData(customchar[i]);
		}
		LCD_Instruction(0x80);
	}
}

void LCD_Clear_Position(u8 line, u8 cell, u8 noCells)
{
	LCD_GoTo(line,cell);
	for(u8 i=0; i<noCells; i++)
	{
		LCD_WriteChar(' ');
	}
}

/*#else
////////////////////////////////////////////////////////////////////// 
////////////////////////////////my code
static void LCD_Instruction(u8 INS)
{
	DIO_SetPin(LCD_RS,LOW);
	DIO_SetPort(LCD_PORT,INS);
	DIO_SetPin(LCD_EN,HIGH);
	_delay_ms(1);
	DIO_SetPin(LCD_EN,LOW);
	_delay_ms(1);
}
void LCD_Init()			//8-bit intiallization
{
	//the used bits in port A: 0b0xxxxxx0
	//RT:::::: DL=1, N=1, F=0
	//wait for more than 30ms for VDD to rise to 4.5v
	_delay_ms(35);
	LCD_Instruction(0x38);
	//now you can choose for any of the following:
	// 0x0C for no cursor and no blink for it
	// 0x0E for cursor with no blink
	// 0x0F for cursor and with blink
	LCD_Instruction(0x0f);
	//then clear screen
	LCD_Instruction(0x01);
	_delay_ms(1);
	//for automatic incrementing I/D=1 and for decrementing I/D=0
	//S is for shifting like when u write on Cell 5 and you enter a new character the one in Cell 5 is gonna move to cell 4 and so on
	//so at S=1 it shifts to the left if I/D=1 and to the right if I/D=0. And When S=0 no shift at all
	// VI NOTE you can mix both of the previous two features to make an animation or something
	LCD_Instruction(0x06);
}
static void LCD_WriteData(u8 data)
{
	
	//if (LINE1_Cell==17 && Line2_CELL!=17)
	//	{
	//		LCD_GoTo(2,Line2_CELL-1);
	//		Line2_CELL++;
	//	}
	//else if(LINE1_Cell>=17 && Line2_CELL>=17)
	//	return;
	//else
	//	LINE1_Cell++;
	//
	DIO_SetPin(LCD_RS,HIGH);
	DIO_SetPort(LCD_PORT,data);
	DIO_SetPin(LCD_EN,HIGH);
	_delay_ms(1);
	DIO_SetPin(LCD_EN,LOW);
	_delay_ms(1);
}
*////////////////////////////////////////////////////////////
#endif

