#include<stdlib.h>
#include<stdio.h>
#include <conio.h> //On Windows, you can use the getch() function from the "conio.h" 
//library, which allows capturing single key presses without the need to press Enter
#include <locale.h>//using this to check mark in Case Turn on only


//	DAY 3 - C Project 2 (Vehicle Control System)

char Engine_state=0;	//intially engine is off

void Menu_transitions();

typedef enum {
	Exit=0,
	Turn_ON,
	Turn_Off,
}operation_choice;

typedef enum {
	Turn_Off2=1,
	Traffic_Light_color,
	Room_Temp,
	Engine_Temp
}On_OP_choice;

void main()
{
	char EXIT_Flag=0, TURN_ON_Trigger=0, check1=0,check2=0,check3=0;
	char res=0;
	setlocale(LC_ALL, ""); // Enable UTF-8 output
	operation_choice choice;
	On_OP_choice OnChoice;

	while (1)
	{
		printf("Welcome to NTI Vehicle Control System\n----------------------------------------\n");
		if (TURN_ON_Trigger)
				choice=Turn_ON;		//once the Turn on case is triggered the user has to provide all the sensors reads to 
									//proceed to the stats, otherwise he needs to turn off the engine to return to the main menu
			else{
			printf("\nSelect the NUMBER of operation you want to proceed with: ");
			printf("\n1-Turn on the vehicle engine\n2-Turn off the vehicle engine\n0-Exit\n");
			printf ("Your choice: ");
			scanf("%d",&choice);
			}
		switch (choice)
		{
			
			case Exit:
				EXIT_Flag=1;
			break;
			///////////////////////////// STARTING case TURN ON ///////////////////////////////////////////////
			case Turn_ON:
				static int Etemp,temp;
				static char traffic_color;
				Engine_state=1;
				if (!TURN_ON_Trigger)
					printf("\n----------------------------------------------------------------------------------");
				printf("\nSelect the NUMBER of operation you want to proceed with: ");
				printf("\n1-Turn off engine\n2-set the traffic light color ");
				if (check1)
					 printf("%c",42);
				printf("\n3-Set the room temprature ");
				if (check2)
					printf("%c",42);

				printf("\n4-Set the Engine temprature");
				if (check3)
					printf("%c",42);
				if(check1 || check2 || check3)
					printf("\n\n(NOTE THAT all readings followed by '%c' sign has been already entered before)\n",42);
				printf ("\nYour choice: ");
				scanf("%d",&OnChoice);
				switch (OnChoice)
				{
					
				case Turn_Off2 :
					TURN_ON_Trigger=0;
					check1=0;
					check2=0;
					check3=0;
					printf("\n\nTurning the Engine off...\n\n");
					break;
				
				case Traffic_Light_color :
					TURN_ON_Trigger++;
					check1++;
					printf("\n\nChecking the traffic light color.");
					
					while (!res)
					{
						printf("\nEnter a sensor read either (G,O,R): ");
						fflush(stdin);
						scanf("%c",&traffic_color);
						if (traffic_color== 'G'||traffic_color== 'g'||traffic_color== 'o'||traffic_color== 'O'||traffic_color== 'r'||traffic_color== 'R')
							res=1;
						else
							printf("\nInvalid read! try again\n");
					}
					res=0;
					if (traffic_color== 'G'||traffic_color== 'g')
						printf("\nGreen detected! Setting the vehcile speed to 100 Km/hr\n");
					else if (traffic_color== 'o'||traffic_color== 'O')
						printf("\nOrange detected! Setting the vehcile speed to 30 Km/hr\n");
					else if (traffic_color== 'r'||traffic_color== 'R')
						printf("\nRed detected! Setting the vehcile speed to 0 Km/hr\n");
					else 
					{
						//nothing
					}
					break;

				case Room_Temp: 
					check2++;
					TURN_ON_Trigger++;
					while (!res)
					{
						printf("\nEnter a sensor read for room temp (-20 <=> 50 degrees): ");
						fflush(stdin);
						scanf("%d",&temp);
						if (temp>=-20 && temp<= 50)
							res=1;
						else
							printf("\nInvalid read! try again\n");
					}
					res=0;
					if (temp <10 || temp>30)
					{
						printf("\nTurning AC on and setting temp to 20 degrees\n");
						temp=20;
					}
					else 
					{
						printf("\nTurning AC off\n");
					}
					break;

				case Engine_Temp: 
					check3++;
					TURN_ON_Trigger++;
					while (!res)
					{
						printf("\nEnter a sensor read for room temp ( 50 <=> 200 degrees): ");
						fflush(stdin);
						scanf("%d",&Etemp);
						if (Etemp>=50 && Etemp<= 200)
							res=1;
						else
							printf("\nInvalid read! try again\n");
					}
					res=0;
					if (Etemp < 100 || Etemp>30)
					{
						printf("\nTurning Engine controller on and setting temp to 125 degrees\n");
						Etemp=125;
					}
					else 
					{
						printf("\nTurning Engine controller off\n");
					}
					break;
				default:
					break;
				}
				if (check1 && check2 && check3)
				{
					system("cls");
					printf("Welcome to NTI Vehicle Control System\n----------------------------------------\n");
					printf("\nPrinting Stats after sensors reads\n\nEngine state: ON");
					if (traffic_color=='O' || traffic_color=='o')
					{
						printf("\nSince vehicle Speed is 30km/hr we will override the follows:\n");
						printf("Override 1: Turning on AC, and the new temp: %d\n",(temp*5/4)+1);
						printf("Override 2: Turning on Engine temp control, and the new temp: %d\n",(Etemp*5/4)+1);

					}
					else
					{
						if (traffic_color=='G'||traffic_color=='g')
							printf("\nVehicle speed: 100km/hr");
						else
							printf("\nVehicle speed: 0km/hr");
						if(temp==20)
							printf("\nAC state: ON		temp: 20");
						else
							printf("\nAC state: OFF		temp: %d",temp);
						if(Etemp==125)
							printf("\nEngine controller state: ON		Engine temp: 125");
						else
							printf("\nEngine controller state: ON		Engine temp: %d",Etemp);
					}
					
				}
				else{}

				Menu_transitions();
				break;
			///////////////////////////// End of case Turn On ///////////////////////////////////
			case Turn_Off:
				if (!Engine_state)
					printf("\n\nENGINE IS ALREADY OFF.\n\n");
				else 
					printf("\n\nTurning the Engine off...\n\n");
				TURN_ON_Trigger=0;
				Menu_transitions();
				break;
			default:
				break;
		}
		if (EXIT_Flag)
		{
			printf("\nThanks! Bye Bye");
			Menu_transitions();
			break;
		}
	}
}


void Menu_transitions()
{
    char ch;
    printf("\n\nOperation succeeded! Press Space to proceed");
    
    while (1)
    {
        ch = getch(); // Use getch() to capture a single key press
        if (ch == ' ')
        {
            system("cls");
			fflush(stdin);
            break;
        }
    }
}