 /******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.h
 *
 * Description: Header file for the UART AVR driver
 *
 * Author: Mohamed Tarek
 *
 *******************************************************************************/

#ifndef UART_H_
#define UART_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define UART_Character_Size uint8
#define UART_Parity_Mode uint8
#define UART_Baud_rate uint32
#define UART_Stop_Mode uint8


/*******************************************************************************
 *                      UART Configuration                                     *
 *******************************************************************************/

typedef struct{
	/* data_size = 0x00   for using 5-bit data mode
	 * data_size = 0x01   for using 6-bit data mode
	 * data_size = 0x02   for using 7-bit data mode
	 * data_size = 0x03   for using 8-bit data mode
	 * data_size = 0x10   Reserved
	 * data_size = 0x11   Reserved
	 * data_size = 0x12   Reserved
	 * data_size = 0x13   for using 9-bit data mode
	 */
	UART_Character_Size data_size;
	/* parity_type = 0x00   for disable parity
	 * parity_type = 0x01   for reserved parity
	 * parity_type = 0x02   for enable even parity
	 * parity_type = 0x03   for enable odd parity
	 */
	UART_Parity_Mode parity_type;
	/* baud_rate = 10   for using baud rate of 10 symbol/sec
	 * baud_rate = 300   for using baud rate of 300 symbol/sec
	 * baud_rate = 600   for using baud rate of 600 symbol/sec
	 * baud_rate = 1200   for using baud rate of 1200 symbol/sec
	 * baud_rate = 2400   for using baud rate of 2400 symbol/sec
	 * baud_rate = 4800   for using baud rate of 4800 symbol/sec
	 * baud_rate = 9600   for using baud rate of 9600 symbol/sec
	 * baud_rate = 14400   for using baud rate of 14400 symbol/sec
	 * baud_rate = 19200   for using baud rate of 19200 symbol/sec
	 * baud_rate = 38400   for using baud rate of 38400 symbol/sec
	 * baud_rate = 57600   for using baud rate of 57600 symbol/sec
	 * baud_rate = 11500   for using baud rate of 11500 symbol/sec
	 * baud_rate = 128000   for using baud rate of 128000 symbol/sec
	 * baud_rate = 256000   for using baud rate of 256000 symbol/sec
	 */
	UART_Baud_rate baud_rate;
	/* stop_type = 0x00   for using 1-stop bit
	 * stop_type = 0x01   for using 2-stop bits
	 */
	UART_Stop_Mode stop_type;

}UART_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(const UART_ConfigType *Config_Ptr);

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data);

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void);

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str);

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str); // Receive until #

#endif /* UART_H_ */
