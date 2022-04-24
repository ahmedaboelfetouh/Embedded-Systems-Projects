/*
 * DCMotor.c
 *
 *  Created on: Oct 13, 2021
 *      Author: am614
 *
 *******************************************************************************/

#include "DCMotor.h"
#include "common_macros.h"
#include "avr/io.h"
#include "gpio.h"
#include "PWM.h"
/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void DcMotor_Init(void)
{
	GPIO_setupPinDirection(PORTB_ID,PIN0_ID,PIN_OUTPUT);//declaring pin PB0 as input pin
	GPIO_setupPinDirection(PORTB_ID,PIN1_ID,PIN_OUTPUT);//declaring pin PB1 as input pin

	/* making the motor stop at the beginning */
	GPIO_writePin(PORTB_ID,PIN0_ID,0);
	GPIO_writePin(PORTB_ID,PIN1_ID,0);
}



void DcMotor_Rotate(DcMotor_State state,uint8 speed)
{
	/* clockwise direction*/
	uint8 speedx;
	if (state==0)
	{
		if(speed != 0)
		{
			if (speed == 25)
			{
				speedx=64;
			}
			if (speed == 50)
			{
				speedx = 128;
			}
			if (speed == 75)
			{
				speedx=192;
			}
			if (speed == 100)
			{
				speedx=255;
			}
			GPIO_writePin(PORTB_ID,PIN0_ID,0);
			GPIO_writePin(PORTB_ID,PIN1_ID,1);
			PWM_Timer0_Init(speedx);
		}
		else if(speed == 0)
		{
			GPIO_writePin(PORTB_ID,PIN0_ID,0);
			GPIO_writePin(PORTB_ID,PIN1_ID,0);
		}
	}
	/* Anti clock wise direction*/
	else if (state==1)
	{
		if(speed != 0)
		{
			if (speed == 25)
			{
				speedx=64;
			}
			else if (speed == 50)
			{
				speedx= 128;
			}
			else if (speed == 75)
			{
				speedx=192;
			}
			else if (speed == 100)
			{
				speedx=255;
			}
			GPIO_writePin(PORTB_ID,PIN0_ID,1);
			GPIO_writePin(PORTB_ID,PIN1_ID,0);
			PWM_Timer0_Init(speedx);
		}
		else if(speed == 0)
		{
			GPIO_writePin(PORTB_ID,PIN0_ID,0);
			GPIO_writePin(PORTB_ID,PIN1_ID,0);
		}
	}

}
