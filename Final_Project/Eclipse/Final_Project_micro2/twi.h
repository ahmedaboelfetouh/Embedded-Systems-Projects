 /******************************************************************************
 *
 * Module: TWI(I2C)
 *
 * File Name: twi.h
 *
 * Description: Header file for the TWI(I2C) AVR driver
 *
 * Author: Mohamed Tarek
 *
 *******************************************************************************/ 

#ifndef TWI_H_
#define TWI_H_

#include "std_types.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

/* I2C Status Bits in the TWSR Register */
#define TWI_START         0x08 /* start has been sent */
#define TWI_REP_START     0x10 /* repeated start */
#define TWI_MT_SLA_W_ACK  0x18 /* Master transmit ( slave address + Write request ) to slave + ACK received from slave. */
#define TWI_MT_SLA_R_ACK  0x40 /* Master transmit ( slave address + Read request ) to slave + ACK received from slave. */
#define TWI_MT_DATA_ACK   0x28 /* Master transmit data and ACK has been received from Slave. */
#define TWI_MR_DATA_ACK   0x50 /* Master received data and send ACK to slave. */
#define TWI_MR_DATA_NACK  0x58 /* Master received data but doesn't send ACK to slave. */
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define TWI_Bit_rate_devision_factor uint8
#define TWI_Bit_rate_prescalar uint8
#define TWI_Bit_slave_address uint8
/*******************************************************************************
 *                       I2C Configuration                                     *
 *******************************************************************************/
typedef struct{
	/* bit_rate_devision_factor -> choose a value between 0 to 255
	 */
	TWI_Bit_rate_devision_factor bit_rate_devision_factor;
	/* bit_rate_prescalar=0x00  to set prescalar value = 1
	 * bit_rate_prescalar=0x01  to set prescalar value = 4
	 * bit_rate_prescalar=0x02  to set prescalar value = 16
	 * bit_rate_prescalar=0x03  to set prescalar value = 64
	 */
	TWI_Bit_rate_prescalar bit_rate_prescalar;
	/* bit_rate_slave_address -> choose a value between 0 to 255 to be your address if this MC is chosen to be a slave
	 */
	TWI_Bit_slave_address slave_address;


}TWI_ConfigType;
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void TWI_init(const TWI_ConfigType *Config_Ptr);
void TWI_start(void);
void TWI_stop(void);
void TWI_writeByte(uint8 data);
uint8 TWI_readByteWithACK(void);
uint8 TWI_readByteWithNACK(void);
uint8 TWI_getStatus(void);


#endif /* TWI_H_ */
