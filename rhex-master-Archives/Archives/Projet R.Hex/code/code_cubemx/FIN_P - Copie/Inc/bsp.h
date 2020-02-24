/*
 * bsp.h
 *
 *  Created on: 28 mai 2016
 *      Author: laurent
 */

#ifndef BSP_INC_BSP_H_
#define BSP_INC_BSP_H_

#include "main.h"


#define READ_FLAG	0x80


// Global variables


// BSP	LED functions
void 	BSP_LED_Init			(void);
void 	BSP_LED_On				(uint8_t n);
void 	BSP_LED_Off				(uint8_t n);
void 	BSP_LED_Toggle			(uint8_t n);

// BSP	User Button function
void BSP_UBTN_Init				(void);

// BSP	Console output
void 	BSP_CONSOLE_TX_Init		(void);

// BSP	RN42 USART
void BSP_RN42_USART_Init		(void);

// BSP SPI2 common initializations
void BSP_SPI2_CSPins_Init		(void);
void BSP_SPI2_Common_Init		(void);

// BSP I2C2 initialization
void BSP_I2C2_Init				(void);



#endif /* BSP_INC_BSP_H_ */
