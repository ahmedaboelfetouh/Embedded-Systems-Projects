/*
 * Mini_Project1.c
 *
 *  Created on: Sep 11, 2021
 *      Author: am614
 */





#include <stdio.h>
#define WITH_ENGINE_TEMP_CONTROLLER 1



void turnon(void);
void turnoff(void);
char start(void);
void displaystate(void);

char speed;
float enginetemperature;
char enginecontrflag;
float roomtemperature;
char acflag;
char engineflag;
int counter=0;

int main() {
	setvbuf(stdout,NULL,_IONBF,0);
	setvbuf(stderr,NULL,_IONBF,0);
	char input;
	do{
		displaystate();
		input = start();
		if(input == 'b')
		{
			turnoff();
		}
		else if(input == 'a')
		{
			turnon();
		}
	}while(input != 'c');



	if(input == 'c')
	{
		return 0;
	}



	return 0;
}





char start(void)
{
	char inputstart;
	do{
			printf("What do you want ?!\n");
			printf("please enter the letter ('a' or 'b' or 'c') according for your choice\n");
			printf("a. Turn on the vehicle engine\n");
			printf("b. Turn off the vehicle engine\n");
			printf("c. Quit the system\n");
			scanf(" %c",&inputstart);
	}while(inputstart != 'c' && inputstart != 'a' && inputstart != 'b');

	return inputstart;
}




void turnon(void){
	char inputon;
	char color;
	printf("The vehicle engine is turned on\n");
	do{
			printf("sensor set menu:\n");
			printf("please enter the letter ('a' or 'b' or 'c' or 'd') according for your choice\n");
			printf("a. Turn off the engine\n");
			printf("b. Set the traffic light color\n");
			printf("c. Set the room temperature (temperature sensor)\n");
#if WITH_ENGINE_TEMP_CONTROLLER
			printf("d. Set the engine temperature (engine temperature sensor)\n");
#endif
			scanf(" %c",&inputon);


			if(inputon == 'b')
			{
				counter++;
				do{
					printf("please enter the letter ('G' or 'O' or 'R') based on the traffic light color\n");
					scanf(" %c",&color);
				}while(color != 'G' && color != 'O' && color != 'R');
				if(color=='G')
				{
					speed=100;
				}
				if(color=='O')
				{
					speed=30;
				}
				if(color=='R')
				{
					speed=0;
				}
			}
			else if(inputon == 'd')
			{
				counter++;
				printf("please enter the engine temperature value\n");
				scanf("%f",&enginetemperature);
#if WITH_ENGINE_TEMP_CONTROLLER
				if(enginetemperature<100)
				{
					enginetemperature=125;
					enginecontrflag=1;
				}
				else if(enginetemperature>150)
				{
					enginetemperature=125;
					enginecontrflag=1;
				}
				else
				{
					enginecontrflag=0;
				}
#endif
			}
			else if(inputon == 'c')
			{
				counter++;
				printf("please enter the room temperature value\n");
				scanf("%f",&roomtemperature);
				if(roomtemperature<10)
				{
					acflag=1;
					roomtemperature=20;
				}
				else if(roomtemperature>30)
				{
					acflag=1;
					roomtemperature=20;
				}
				else
				{
					acflag=0;
				}

			}



			if(speed==30)
			{
				acflag=1;
				roomtemperature=roomtemperature*(5/4)+1;
#if WITH_ENGINE_TEMP_CONTROLLER
				enginecontrflag=1;
				enginetemperature=enginetemperature*(5/4)+1;
#endif
			}

			if(counter>=3 && inputon != 'a')
			{
				engineflag=1;
				displaystate();
			}

	}while(inputon != 'a');

	if(inputon=='a')
	{
		turnoff();
		engineflag=0;
		displaystate();
		return;
	}

}


void displaystate(void)
{
	if(counter>=3)
	{
		if(engineflag==1)
		{
		printf("i. engine state:ON\n");
		}
		else if(engineflag==0)
		{
		printf("i. engine state:OFF\n");
		}
		if(acflag==1)
		{
		printf("ii. AC:ON\n");
		}
		else if(acflag==0)
		{
		printf("ii. AC:OFF\n");
		}
		printf("iii. vehicle speed:%d\n",speed);
		printf("iv. room temperature:%f\n",roomtemperature);
#if WITH_ENGINE_TEMP_CONTROLLER
		if(enginecontrflag==1)
		{
		printf("v. engine temperature controller state:ON\n");
		}
		else if(enginecontrflag==0)
		{
		printf("v. engine temperature controller state:OFF\n");
		}
		printf("vi. engine temperature:%f\n",enginetemperature);
#endif
	}
	return;
}


void turnoff(void){
	printf("The vehicle engine is turned off\n");
	return;
}
