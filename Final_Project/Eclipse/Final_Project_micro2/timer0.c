/*
 * timer0.c
 *
 *  Created on: Oct 26, 2021
 *      Author: am614
 *********************************************************************************/
#include "timer0.h"
#include "common_macros.h"
#include <avr/interrupt.h>
#include <avr/io.h>
/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_callBackPtr_ISR_Normal_Mode)(void) = NULL_PTR;
/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_callBackPtr_ISR_CTC_MOde)(void) = NULL_PTR;



/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/
/*
 * Timer0 Normal Mode ISR
 */
ISR(TIMER0_OVF_vect)
{
	if(g_callBackPtr_ISR_Normal_Mode != NULL_PTR)
		{
			/* Call the Call Back function in the application*/
			(*g_callBackPtr_ISR_Normal_Mode)(); /* another method to call the function using pointer to function  */
		}
}

/*
 * Timer0 CTC Mode ISR
 */
ISR(TIMER0_COMP_vect)
{
	if(g_callBackPtr_ISR_CTC_MOde != NULL_PTR)
		{
			/* Call the Call Back function in the application */
			(*g_callBackPtr_ISR_CTC_MOde)(); /* another method to call the function using pointer to function */
		}
}

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void timer0_init(const TIMER0_ConfigType *Config_Ptr)
{
	/* Enable Global Interrupt I-Bit */
	SREG |= (1<<7);
	TCNT0 = Config_Ptr -> initial_value;  //Set Timer initial value
	/*
	 * Normal mode initialization
	 */
	if(Config_Ptr -> mode == 0x00)
	{
		TIMSK |= (1<<TOIE0); // Enable Timer0 Overflow Interrupt
		/* Configure the timer control register (TCCR0)
		 * 1. Non PWM mode FOC0=1
		 * 2. Normal Mode WGM01=0 & WGM00=0
		 * 3. Normal Mode COM00=0 & COM01=0
		 * 4. clock = F_CPU/prescalar
		 */
		TCCR0 = (1<<FOC0) | (((Config_Ptr -> prescalar) & (0x01))<<CS00) | ((((Config_Ptr -> prescalar) & (0x02))>>1)<<CS01) | ((((Config_Ptr -> prescalar) & (0x04))>>2)<<CS02);
	}
	/*
	 * CTC mode initialization
	 */
	else if(Config_Ptr -> mode == 0x02)
	{
		OCR0 = Config_Ptr -> compare_value; // Set Compare Value
		TIMSK |= (1<<OCIE0); // Enable Timer0 Compare Interrupt
		/* Configure timer control register
		 * 1. Non PWM mode FOC0=1
		 * 2. CTC Mode WGM01=1 & WGM00=0
		 * 3. No need for OC0 (Output compare pin) so COM00=0 & COM01=0 (OC0 disconnected)
		 * 4. clock = F_CPU/prescalar
		 */
		TCCR0 = (1<<FOC0) | (1<<WGM01) | (((Config_Ptr -> prescalar) & (0x01))<<CS00) | ((((Config_Ptr -> prescalar) & (0x02))>>1)<<CS01) | ((((Config_Ptr -> prescalar) & (0x04))>>2)<<CS02);
	}
	/*
	 * Fast PWM mode initialization
	 */
	else if(Config_Ptr -> mode == 0x03)
	{
		OCR0  = Config_Ptr -> compare_value;    /*(Duty-Cycle)*/
		DDRB  = DDRB | (1<<PB3); //set PB3/OC0 as output pin --> pin where the PWM signal is generated from MC.
		/* Configure timer control register
		 * 1. Fast PWM mode FOC0=0
		 * 2. Fast PWM Mode WGM01=1 & WGM00=1
		 * 3. Clear OC0 when match occurs (non inverted mode) COM00=0 & COM01=1
		 * 4. clock = F_CPU/prescalar
		 */
		TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (((Config_Ptr -> prescalar) & (0x01))<<CS00) | ((((Config_Ptr -> prescalar) & (0x02))>>1)<<CS01) | ((((Config_Ptr -> prescalar) & (0x04))>>2)<<CS02) ;
	}
}


void timer0_setCallBack_normal_mode(void(*a_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_callBackPtr_ISR_Normal_Mode = a_ptr;
}

void timer0_setCallBack_CTC_mode(void(*a_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_callBackPtr_ISR_CTC_MOde = a_ptr;
}

void timer0_de_init(void)
{
	/* no clock source for Timer0 (CS02=0),(CS01=0),(CS00=0) -> Timer0 stopped */
	TCCR0 = 0 ;
}
