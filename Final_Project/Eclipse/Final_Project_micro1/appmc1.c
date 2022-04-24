/*
 * app.c
 *
 *  Created on: Oct 23, 2021
 *      Author: am614
 ***********************************************************************************************/


/*******************************************************************************
 *                                 Includes                                    *
 *******************************************************************************/


#include "lcd.h"
#include "std_types.h"
#include "keypad.h"
#include "uart.h"
#include "timer0.h"


/*******************************************************************************
 *                              Application  Definitions                       *
 *******************************************************************************/
#define password_length  5          /* define for the required length of the password*/


/*******************************************************************************
 *                              Global Variables                               *
 *******************************************************************************/
/*flag used for the function (set_new_password) to detect
  if the 2 passwords entered are the same or not */
uint8 flag_same_set_pass=0;
uint8 buzzercount=0;
/* global variable contain the ticks count of the timer */
uint8 g_tick = 0;
/*******************************************************************************
 *                     Application Functions Prototypes                        *
 *******************************************************************************/
/*
 * Description:
 * 1. used for making delays using timer0 in normal mode
 * 2. it initializes the timer0 driver with the wanted configuration
 * 3. setup the call back function for timer0 driver
 * 4. wait till the required delay finished then de_initialize the timer0 driver
 */
void delay_timer0_normal_mode(uint32);
/*
 * the normal mode call back function of the timer0 driver
 */
void delay(void);
/*
 * Description :
 * 1. used for set new password to the system
 */
void set_new_password(void);
/*
 * Description :
 * 1. detect the password entered keypad as the password length required
 * 2. show '*' on LCD everytime a keypad input is pressed
 */
void get_entered_password(uint8 *);
/*
 * Description :
 * 1. detect if the 2 entered passwords for setting new password are matching or not
 */
uint8 password_match(uint8 *,uint8 *);
/*
 * Description :
 * 1. used for (step 2) after setting password for the system
 * 2. for openning the door or setting new password to the system
 */
void open_or_changepass(void);
/*
 * Description :
 * 1. used for checking if the entered password is the same as in the eeprom in mc2 or not
 */
uint8 eeprom_match(uint8 *);

/*******************************************************************************
 *                               Main Function                                 *
 *******************************************************************************/
int main(void)
{

	/* Initialize the LCD driver */
	LCD_init();
	/* Initialize the UART driver */
	UART_ConfigType ptr;
	(ptr.data_size) = 0x03;
	(ptr.parity_type) = 0x00;
	(ptr.baud_rate) = 9600;
	(ptr.stop_type) = 0x00;
	UART_init(&ptr);

	while(1)
	{

		while(flag_same_set_pass==0)
		{
			set_new_password();
		}

		open_or_changepass();






	}
	return 0;
}




/*******************************************************************************
 *                     Application Functions Definitions                       *
 *******************************************************************************/


void set_new_password(void)
{
	uint8 pass_1[password_length];
	uint8 pass_2[password_length];
	LCD_clearScreen();
	LCD_displayString("Enter password");
	get_entered_password(pass_1);
	LCD_clearScreen();
	LCD_displayString("ReEnter password");
	get_entered_password(pass_2);
	if(password_match(pass_1,pass_2))
	{
		flag_same_set_pass=1;
		/* Send the Password to the other device through the UART */
		delay_timer0_normal_mode(1);
		uint8 i;
		for(i=0;i<password_length;i++)
		{
			UART_sendByte(pass_1[i]);
		}
		LCD_clearScreen();
		LCD_displayString("Match");
		delay_timer0_normal_mode(2);
	}
	else
	{
		flag_same_set_pass=0;
		LCD_clearScreen();
		LCD_displayString("Repeat");
		delay_timer0_normal_mode(2);
	}

}



void get_entered_password(uint8 *pass)
{
	LCD_moveCursor(1,0);
	uint8 i=0;
	uint8 pressed;
	for(i=0;i<password_length;i++)
	{
		/*get the pressed key number*/
		pressed=KEYPAD_getPressedKey();
		pass[i]=pressed;
		LCD_intgerToString(pressed);
		delay_timer0_normal_mode(2);
	}
}



uint8 password_match(uint8 *pass1,uint8 *pass2)
{
	uint8 i;
	for(i=0;i<password_length;i++)
	{
		if(pass1[i]==pass2[i])
		{
			continue;
		}
		else
		{
			return 0;
		}
	}
	return 1;
}

void open_or_changepass(void)
{
	uint8 open_change;
	uint8 pass_open[password_length];

	LCD_clearScreen();
	LCD_displayString("+ : open door");
	LCD_moveCursor(1,0);
	LCD_displayString("- : change pass");
	open_change=KEYPAD_getPressedKey();
	delay_timer0_normal_mode(2);
	LCD_clearScreen();
	if(open_change == '+')                         /*open door*/
	{
		LCD_displayString("enter pass");
		get_entered_password(pass_open);
		if(eeprom_match(pass_open)==1)
		{
			UART_sendByte(1);      /*sending 1 to mc2 to inform it that the entered password is correct*/
			buzzercount=0;
			LCD_clearScreen();
			LCD_displayString("Opneing Door");
			delay_timer0_normal_mode(60);
			LCD_clearScreen();
			LCD_displayString("Door Opened");
			delay_timer0_normal_mode(20);
			LCD_clearScreen();
			LCD_displayString("Closing Door");
			delay_timer0_normal_mode(60);

		}
		else
		{
			UART_sendByte(0);		/*sending 0 to mc2 to inform it that the entered password is not correct*/
			buzzercount++;
			if(buzzercount==3)
			{
				LCD_clearScreen();
				LCD_displayString("ERROR");
				delay_timer0_normal_mode(240);
				buzzercount=0;
			}
			else
			{
				LCD_clearScreen();
				LCD_displayString("Wrong Password");
				delay_timer0_normal_mode(2);
			}
		}

	}
	else if(open_change == '-')                     /*change password*/
	{
		LCD_displayString("enter pass");
		get_entered_password(pass_open);
		if(eeprom_match(pass_open)==1)
		{
			UART_sendByte(11);		/*sending 11 to mc2 to inform it that the entered password is correct*/
			flag_same_set_pass=0;
			while(flag_same_set_pass==0)
			{
				set_new_password();
			}
		}
		else
		{
			UART_sendByte(0);		/*sending 0 to mc2 to inform it that the entered password is not correct*/
			buzzercount++;
			if(buzzercount==3)
			{
				LCD_clearScreen();
				LCD_displayString("ERROR");
				delay_timer0_normal_mode(240);
				buzzercount=0;
			}
			else
			{
				LCD_clearScreen();
				LCD_displayString("Wrong Password");
				delay_timer0_normal_mode(2);
			}

		}




	}

}



uint8 eeprom_match(uint8 *password)
{

	uint8 eeprom_pass[password_length];
	UART_sendByte(10);          /*sending 10 to mc2 to make it send the password that stored in eeprom*/
	uint8 i;
	for(i=0;i<password_length;i++)
	{
		eeprom_pass[i]=UART_recieveByte();        /*receiving the password stored in mc2 in eeprom*/
	}
	for(i=0;i<password_length;i++)
	{
		if(password[i]==eeprom_pass[i])      /* checking if the password entered is the same with the password stored in eeprom or not*/
		{
			continue;
		}
		else
		{
			return 0;   /*2 passwords are not the same */
		}
	}
	return 1;  /*2 passwords are the same*/
}

void delay(void)
{
	g_tick++;
}

void delay_timer0_normal_mode(uint32 num_of_quarter_secs)
{
	/* Set the Call back function pointer in the TIMER0 driver */
	timer0_setCallBack_normal_mode(delay);

	/* Initialize the TIMER0 driver */
	TIMER0_ConfigType ptr_timer0;
	(ptr_timer0.mode) = 0x00;
	(ptr_timer0.initial_value) = 0;
	(ptr_timer0.compare_value) = 0;
	(ptr_timer0.prescalar) = 0x05;
	timer0_init(&ptr_timer0);
	/*
	 * normal mode
	 * prescalar = 1024    ->  it cause an interrupt every 0.26 sec
	 * initial value = 0
	 * compare value = 0  (normal mode)
	 */
	while(g_tick != num_of_quarter_secs);
	g_tick=0;
	timer0_de_init();
}




