/*
 * buzzer.c
 *
 *  Created on: Oct 26, 2021
 *      Author: am614
 *
 ********************************************************************************/

#include "gpio.h"
#include "std_types.h"
#include "common_macros.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/


void buzzer_init(void)
{
	GPIO_setupPinDirection(PORTD_ID,PIN3_ID,PIN_OUTPUT);
	GPIO_writePin(PORTD_ID,PIN3_ID,LOGIC_LOW);
}

void buzzer_on(void)
{
	GPIO_writePin(PORTD_ID,PIN3_ID,LOGIC_HIGH);
}


void buzzer_off(void)
{
	GPIO_writePin(PORTD_ID,PIN3_ID,LOGIC_LOW);
}


