/*
 * app.c
 *
 *  Created on: Oct 14, 2021
 *      Author: am614
 *********************************************************************************/


#include "lcd.h"
#include "icu.h"
#include "gpio.h"
#include "std_types.h"
#include "ultrasonic.h"
#include <avr/io.h>
#include <util/delay.h>
uint16 dis;

int main(void)
{
		/* Initialize the LCD driver */
		LCD_init();
		/* Initialize the LCD driver */
		Ultrasonic_init();
		LCD_displayString("Distance=    cm");

		while(1)
		{

			dis=Ultrasonic_readDistance();
			LCD_moveCursor(0,10);
			if(dis >= 100)
			{
				LCD_intgerToString(dis);
			}

			else
			{
				LCD_intgerToString(dis);
				/* In case the digital value is two or one digits print space in the next digit place*/
				LCD_displayCharacter(' ');
			}



		}

}
