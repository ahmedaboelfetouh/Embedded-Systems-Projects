/*
 * appmc2.c
 *
 *  Created on: Oct 25, 2021
 *      Author: am614
 ************************************************************************************************/


/*******************************************************************************
 *                                 Includes                                    *
 *******************************************************************************/
#include "std_types.h"
#include "DCMotor.h"
#include "uart.h"
#include "twi.h"
#include "external_eeprom.h"
#include "buzzer.h"
#include "timer0.h"


/*******************************************************************************
 *                              Application  Definitions                       *
 *******************************************************************************/
#define password_length  5          /* define for the required length of the password*/

/*******************************************************************************
 *                              Global Variables                               *
 *******************************************************************************/
/* global variable contain the ticks count of the timer */
uint8 g_tick = 0;
uint8 buzzer_count=0;
uint8 first_flag=0;
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
 * 1. used for getting new password for the system and store it in the eeprom
 */
void get_new_password(void);
/*
 * Description :
 * 1. used for checking if the sent password form mc1 is the same password in the eeprom or not
 */
uint8 check_password(void);
/*
 * Description :
 * 1. used for open motor to open the door
 * 2. the door is being opened (motor rotates in clock-wise) for 15 sec
 * 3. the door is opened (motor off) for 3 sec
 * 4. the dor is being closed (motor rotates in anti-clock-wise) for 15 sec
 */
void open_motor(void);

/*******************************************************************************
 *                               Main Function                                 *
 *******************************************************************************/
int main(void)
{

	uint8 wrong__right;

	/* Initialize the UART driver */
	UART_ConfigType ptr_UART;
	(ptr_UART.data_size) = 0x03;
	(ptr_UART.parity_type) = 0x00;
	(ptr_UART.baud_rate) = 9600;
	(ptr_UART.stop_type) = 0x00;
	UART_init(&ptr_UART);
	/* Initialize the TWI/I2C Driver */
	TWI_ConfigType ptr_TWI;
	(ptr_TWI.bit_rate_devision_factor) = 2;
	(ptr_TWI.bit_rate_prescalar) = 0x00;
	(ptr_TWI.slave_address) = 1;
	TWI_init(&ptr_TWI);
	/*	initializing the motor */
	DcMotor_Init();
	/*	initializing the buzzer */
	buzzer_init();

	while(1)
	{

			if(first_flag==0)
			{
				get_new_password();
				first_flag=1;
			}
			wrong__right=check_password();
			if(wrong__right==1)			/*entered correct password*/
			{
				buzzer_count=0;
				open_motor();

			}
			else if(wrong__right==0)    /*entered wrong password*/
			{
				buzzer_count++;
				if(buzzer_count==3)
				{
					buzzer_on();
					delay_timer0_normal_mode(240);
					buzzer_off();
					buzzer_count=0;
				}

			}
			else if(wrong__right==11)   /*wants to change password and entered correct password*/
			{
					get_new_password();
			}

	}
	return 0;
}


/*******************************************************************************
 *                     Application Functions Definitions                       *
 *******************************************************************************/



void get_new_password(void)
{
	uint8 pass[password_length];
	/* Receive the Password from the other device through the UART */
	uint8 i;
	for(i=0;i<password_length;i++)
	{
		pass[i]=UART_recieveByte();
	}
	for(i=0;i<password_length;i++)
	{
		EEPROM_writeByte(0x0311+i, pass[i]); /* Write the password in the external EEPROM */
		delay_timer0_normal_mode(1);
	}

}

uint8 check_password(void)
{
	uint8 wrong_right;
	uint8 eeprom_pass[password_length];
	uint8 check;
	uint8 i;
	for(i=0;i<password_length;i++)
	{
		EEPROM_readByte(0x0311+i, &(eeprom_pass[i])); /* read the password form the external EEPROM */
		delay_timer0_normal_mode(1);
	}
	check=UART_recieveByte();    /*receive 10 from eeprom_match function in mc1 to start sending the pasword saved in eeprom*/
	delay_timer0_normal_mode(4);
	for(i=0;i<password_length;i++)
	{
		UART_sendByte(eeprom_pass[i]);    /* send the password saved in the eeprom to mc1 to check wrong or right */
	}
	wrong_right=UART_recieveByte();     /*receive if the password entered is wrong or right 1-> right 0 -> wrong */
	return wrong_right;
}



void open_motor(void)
{
	DcMotor_Rotate(0,100);
	delay_timer0_normal_mode(60);
	DcMotor_Rotate(0,0);
	delay_timer0_normal_mode(20);
	DcMotor_Rotate(1,100);
	delay_timer0_normal_mode(60);
	DcMotor_Rotate(0,0);
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



