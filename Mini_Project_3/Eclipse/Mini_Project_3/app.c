/*
 * app.c
 *
 *  Created on: Oct 12, 2021
 *      Author: am614
 */

#include "adc.h"
#include "lcd.h"
#include "lm35_sensor.h"
#include "GPIO.h"
#include "DCMotor.h"
#include "PWM.h"



int main(void)
{
	uint8 temp;


	/*	initializing the motor */
	DcMotor_Init();
	/*	motor rotates in clock wise direction and stop at the beginning */
	DcMotor_Rotate(0,0);
	/* initialize LCD driver */
	LCD_init();
	/* initialize ADC driver */
	ADC_ConfigType ptr;
	(ptr.ref_volt) = 0xC0;
	(ptr.prescaler) = 0x03;
	ADC_init(&ptr);
	/* Display this string "FAN is    " and "Temp =   C"*/
	LCD_displayString("   Fan is");
	LCD_moveCursor(1,0);
	LCD_displayString("   Temp =    C");

	while(1)
	{
		temp = LM35_getTemperature();

		/* Display the temperature value every time at same position */
		LCD_moveCursor(1,10);
		if(temp >= 100)
		{
			LCD_intgerToString(temp);
		}
		else
		{
			LCD_intgerToString(temp);
			/* In case the digital value is two or one digits print space in the next digit place */
			LCD_displayCharacter(' ');
		}
		/**************************************************************************************/
		/*controlling the mototr according to the temprature sensored*/
		if(temp<30)
		{
			DcMotor_Rotate(0,0);
			LCD_moveCursor(0,10);
			LCD_displayString("OFF");
			LCD_moveCursor(1,10);

		}

		else if(temp>=30 && temp<60)
		{
			DcMotor_Rotate(0,25);
			LCD_moveCursor(0,10);
			LCD_displayString(" ON");
			LCD_moveCursor(1,10);
		}
		else if(temp>=60 && temp<90)
		{
			DcMotor_Rotate(0,50);
			LCD_moveCursor(0,10);
			LCD_displayString(" ON");
			LCD_moveCursor(1,10);
		}
		else if(temp>=90 && temp<120)
		{
			DcMotor_Rotate(0,75);
			LCD_moveCursor(0,10);
			LCD_displayString(" ON");
			LCD_moveCursor(1,10);
		}
		else if(temp>=120)
		{
			DcMotor_Rotate(0,100);
			LCD_moveCursor(0,10);
			LCD_displayString(" ON");
			LCD_moveCursor(1,10);
		}


	}


}

