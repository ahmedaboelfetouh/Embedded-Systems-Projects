/*
 * timer0.h
 *
 *  Created on: Oct 26, 2021
 *      Author: am614
 *********************************************************************************/

#ifndef TIMER0_H_
#define TIMER0_H_

#include "std_types.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define Timer0_mode uint8
#define Timer0_initial_value uint8
#define Timer0_compare_value uint8
#define Timer0_prescalar uint8

/*******************************************************************************
 *                       I2C Configuration                                     *
 *******************************************************************************/
typedef struct{
	/*
	 * Normal mode -> mode = 0x00
	 * CTC mode ->  mode = 0x02
	 * Fast PWM mode -> mode = 0x03
	 */
	Timer0_mode mode;
	/*
	 * select initial value from 0 to 255
	 */
	Timer0_initial_value initial_value;
	/*
	 * select compare value from 0 to 255
	 * in case of using PWM mode -> compare value will be the required duty cycle
	 */
	Timer0_compare_value compare_value;
	/*
	 * prescalar = 0x00 (no clcok source) timer/counter stopped
	 * prescalar = 0x01 no prescalar
	 * prescalar = 0x02 clk/8
	 * prescalar = 0x03 clk/64
	 * prescalar = 0x04 clk/256
	 * prescalar = 0x05 clk/1024
	 * prescalar = 0x06 external clock source on T0 PIN. clock on falling edge
	 * prescalar = 0x07 external clcok source on T0 PIN. clock on rising edge
	 */
	Timer0_prescalar prescalar;
}TIMER0_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 * Description :
 * Function responsible for initialize the Timer0 driver with the required configuration
 */
void timer0_init(const TIMER0_ConfigType *Config_Ptr);
/*
 * Description:
 * Function to set the Call Back function address for Timer0 Normal mode
 */
void timer0_setCallBack_normal_mode(void(*a_ptr)(void));
/*
 * Description:
 * Function to set the Call Back function address for Timer0 CTC mode
 */
void timer0_setCallBack_CTC_mode(void(*a_ptr)(void));
/*
 * Description :
 * Function responsible for de-initialize the Timer0 driver
 */
void timer0_de_init(void);










#endif /* TIMER0_H_ */
