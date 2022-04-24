/*
 * ultrasonic.c
 *
 *  Created on: Oct 14, 2021
 *      Author: am614
 ********************************************************************************/
#include "icu.h"
#include <avr/io.h>
#include "std_types.h"
#include "gpio.h"
#include <util/delay.h>
#include <math.h>
/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
uint8 g_edgeCount = 0;
uint16 g_timeHigh = 0;
uint16 g_timePeriod = 0;
uint16 g_timePeriodPlusHigh = 0;
uint16 time=0;
uint16 distance=0;
void Ultrasonic_edgeProcessing(void)
{
		g_edgeCount++;
		if(g_edgeCount == 1)
		{
			/*
			 * Clear the timer counter register to start measurements from the
			 * first detected rising edge
			 */
			Icu_clearTimerValue();
			/* Detect falling edge */
			Icu_setEdgeDetectionType(FALLING);
		}
		else if(g_edgeCount == 2)
		{
			/* Store the High time value */
			g_timeHigh = Icu_getInputCaptureValue();
			/* Detect rising edge */
			Icu_clearTimerValue();

			Icu_setEdgeDetectionType(RISING);
		}


}

void Ultrasonic_init(void)
{
	/* Create configuration structure for ICU driver */
	Icu_ConfigType Icu_Config = {(F_CPU_8),RISING};
	/* Enable Global Interrupt I-Bit */
	SREG |= (1<<7);
	/* Set the Call back function pointer in the ICU driver */
	Icu_setCallBack(Ultrasonic_edgeProcessing);
	/* Initialize the ICU driver */
	Icu_init(&Icu_Config);
	/*setup the direction of the trigger pin as output pin through the gpio driver*/
	GPIO_setupPinDirection(PORTB_ID,PIN5_ID,PIN_OUTPUT);

}

void Ultrasonic_Trigger(void)
{
	GPIO_writePin(PORTB_ID,PIN5_ID,1);
	_delay_ms(0.001);
	GPIO_writePin(PORTB_ID,PIN5_ID,0);

}

uint16 Ultrasonic_readDistance(void)
{
		if(g_edgeCount==0)
			{
				Ultrasonic_Trigger();
			}
		else if(g_edgeCount==2)
			{

				//distance=g_timeHigh;
				distance = ceil((float)g_timeHigh/58);
				g_edgeCount=0;
			}




	return distance;

}


