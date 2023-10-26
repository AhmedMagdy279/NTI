/*
 * NTI_Drivers.c
 *
 * Created: 10/17/2023 12:36:20 PM
 * Author : M3gZ
 */ 

#include "LIB/Std_Types.h"
#include "LIB/UTILS.h"
#include "LIB/MemMap.h"
#include "MCAL/DIO/DIO_Interface.h"
#include "HAL/sevenSeg/sevenSeg_Interface.h"
#include "HAL/LCD/LCD_Interface.h"
#include "HAL/KeyPad/KeyPad_Interface.h"
#include "APP/Calculator/Calculator.h"
#include "MCAL/EXT_INT/EXT_INT_Interface.h"
#include "MCAL/ADC/ADC_Interface.h"
#include "HAL/LDR/LDR_Interface.h"
#include "HAL/LM35/LM35_Interface.h"
#define F_CPU 8000000
#include <util/delay.h>



/////////////////////////////////////LCD GAME main()	//done//////////////////////////////////////////////////
void LCD_Game();
void LCD_GameScore( u8 score);
void LCD_playersPos(u8 P1, u8 P2x,u8 P2y);
int main ()
{
	DIO_Init();
	LCD_Init();
	KeyPad_Init();
	
	while(1)
	{
		LCD_Game();
	}
}


// the game is mainly consists of two players, one controls the brackets on both sides and the other is controlling 
//the ball trying to score on one of either sides

//Player 1 is the goalkeeper and Player 2 is the ball controller
//player 1 can only move on Y-axis, while player 2 has X and Y axis

void LCD_GameScore(u8 score)		//score	--> 0 for intiation
{									//		--> 1 player left scored
	static u8 p1=0,p2=0;			//		--> 2 player right scored
	LCD_CLR();						//		--> 3 while loop
	LCD_GoTo(4,0);
	LCD_WriteString("SCORE=> P1:    P2: ");
	
	if (score==1)
		p1++;
	else if (score == 2)
		p2++;
	else if (!score)
		{
			p1=0;
			p2=0;
		}
	
	LCD_GoTo(4,12);
	LCD_WriteNumber(p1);
	
	LCD_GoTo(4,19);
	LCD_WriteNumber(p2);
}

void LCD_playersPos(u8 P1, u8 P2x,u8 P2y)
{
	//char p1='|',p2="o";
	//player 1
	LCD_GoTo(P1,0);
	LCD_WriteString("|");
	LCD_GoTo(P1,19);
	LCD_WriteString("|");
	
	//player 2
	LCD_GoTo(P2y,P2x);
	LCD_WriteString("o");
}

void LCD_Game()
{
	u8 rightDirec=1;
	static char p1Pos=2, p2X=10, p2Y=2;	//intially player1 will start in the middle line (line 2)
	LCD_GameScore(0);
	while(1)
	{
		
		LCD_GameScore(3);
		LCD_playersPos(p1Pos,p2X,p2Y);
		
		
		//check for press on PB
		DIO_SetPin(PINC5,HIGH);
		if (!DIO_ReadPin(PIND7))
		{
			if (p1Pos==2||p1Pos==3)
			{
				p1Pos--;
			}
		}
		else if (!DIO_ReadPin(PIND6))
		{
			if (p1Pos==1||p1Pos==2)
			{
				p1Pos++;
			}
		}
		else if (!DIO_ReadPin(PIND5))
		{
			if(p2Y==2||p2Y==3)
				p2Y--;
		}
		else if (!DIO_ReadPin(PIND3))
		{
			if(p2Y==1||p2Y==2)
				p2Y++;
		}
		
		
		if(p2X< 18 && p2X>1)	//checking only the ball normal movement between 1 ~ 18
		{
			if (rightDirec)		//Ball shall be initially start going right
			p2X++;
			else
			p2X--;
		}
		else
		{
			//goal score update code and re-intiate the game
			if (p2X==18 && p2Y!=p1Pos && rightDirec)
			{
				p2X++;
				LCD_playersPos(p1Pos,p2X,p2Y);
				LCD_GameScore(1);
				LCD_GoTo(2,8);
				LCD_WriteString("GOAL!");
				_delay_ms(3000);
				rightDirec=1;
				p1Pos=2;
				p2X=10;
				p2Y=2;
			}
			else if (p2X==1 && p2Y!=p1Pos &&!rightDirec)
			{
				p2X--;
				LCD_playersPos(p1Pos,p2X,p2Y);
				LCD_GameScore(2);
				LCD_GoTo(2,8);
				LCD_WriteString("GOAL!");
				_delay_ms(3000);
				rightDirec=1;
				p1Pos=2;
				p2X=10;
				p2Y=2;
			}
			else
			{
				if (rightDirec && p2X==18)
				{
					rightDirec=0;
					p2X--;
				}
				else if (!rightDirec && p2X==1)
				{
					rightDirec=1;
					p2X++;
				}
			}
		}
		
		_delay_ms(250);
	}
	
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
