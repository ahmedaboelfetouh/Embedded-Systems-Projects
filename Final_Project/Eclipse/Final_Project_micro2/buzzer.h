/*
 * buzzer.h
 *
 *  Created on: Oct 26, 2021
 *      Author: am614
 *
 ********************************************************************************/

#ifndef BUZZER_H_
#define BUZZER_H_



/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 * Description :
 * 1. used for initialization of buzzer driver
 */
void buzzer_init(void);
/*
 * Description :
 * 1. used for turning on the buzzer
 */
void buzzer_on(void);
/*
 * Description :
 * 1. used for turning off the buzzer
 */
void buzzer_off(void);


#endif /* BUZZER_H_ */
