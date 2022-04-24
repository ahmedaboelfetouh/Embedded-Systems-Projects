 /******************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.h
 *
 * Description: header file for the ATmega16 ADC driver
 *
 * Author: Mohamed Tarek
 *
 *******************************************************************************/

#ifndef ADC_H_
#define ADC_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define ADC_MAXIMUM_VALUE    1023
#define ADC_REF_VOLT_VALUE   2.56
#define ADC_ReferenceVolatge uint8
#define ADC_Prescaler		 uint8

/*******************************************************************************
 *                       I2C Configuration                                     *
 *******************************************************************************/
typedef struct{
	/* ref_volt=0xC0 for using internal refrence voltage2.56
	 * ref_volt=0x00 for using Aref (internal turned off)
	 * ref_volt=0x40 for using Avcc with external capacitor at Aref pin
	 * ref_volt= 0x80 for Reversed
	 */
	ADC_ReferenceVolatge ref_volt;
 	/* prescalar=0x00 to choose ADC_Clock=F_CPU/2
 	 * prescalar=0x01 to choose ADC_Clock=F_CPU/2
 	 * prescalar=0x02 to choose ADC_Clock=F_CPU/4
 	 * prescalar=0x03 to choose ADC_Clock=F_CPU/8
 	 * prescalar=0x04 to choose ADC_Clock=F_CPU/16
 	 * prescalar=0x05 to choose ADC_Clock=F_CPU/32
 	 * prescalar=0x06 to choose ADC_Clock=F_CPU/64
 	 * prescalar=0x07 to choose ADC_Clock=F_CPU/128
 	 */
	ADC_Prescaler prescaler;
}ADC_ConfigType;
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/


/*
 * Description :
 * Function responsible for initialize the ADC driver.
 */
void ADC_init(const ADC_ConfigType *Config_Ptr);

/*
 * Description :
 * Function responsible for read analog data from a certain ADC channel
 * and convert it to digital using the ADC driver.
 */
uint16 ADC_readChannel(uint8 channel_num);


#endif /* ADC_H_ */
