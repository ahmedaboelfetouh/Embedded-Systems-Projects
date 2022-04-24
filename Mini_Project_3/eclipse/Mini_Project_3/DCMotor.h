/*
 * DCMotor.h
 *
 *  Created on: Oct 13, 2021
 *      Author: am614
 *
 *******************************************************************************/

#ifndef DCMOTOR_H_
#define DCMOTOR_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define DcMotor_State uint8



/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 * Description :
 * Function responsible for initialize the DCMOTOR driver.
 * The Function responsible for setup the direction for the two
 * motor pins through the GPIO driver
 * Stop at the DC-Motor at the beginning through the GPIO driver
 */

void DcMotor_Init(void);
/*
 * Description :
 * The function responsible for rotate the DC Motor CW/ or A-CW or
 * stop the motor based on the state input state value
 * Send the required duty cycle to the PWM driver based on the
 * required speed value
 */

void DcMotor_Rotate(DcMotor_State state,uint8 speed);

#endif /* DCMOTOR_H_ */
