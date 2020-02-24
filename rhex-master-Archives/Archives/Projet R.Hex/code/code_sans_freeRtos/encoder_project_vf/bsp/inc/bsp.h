/*
 * bsp.h
 *
 *  Created on: 28 mai 2016
 *      Author: laurent
 */

#ifndef BSP_INC_BSP_H_
#define BSP_INC_BSP_H_
#define Matlab_RX_BUFFER_SIZE		8

#include "main.h"

uint16_t	adc_buffer[4];
uint8_t	matlab_rx_buffer[Matlab_RX_BUFFER_SIZE];

// BSP	LED functions
void 	BSP_LED_Init			(void);
void 	BSP_PB_Init				(void);
void 	BSP_LED_On				(uint8_t n);
void 	BSP_LED_Off				(uint8_t n);
void 	BSP_LED_Toggle			(uint8_t n);
void	BSP_ADC_Init();

// BSP	Console output (/input)
void 	BSP_CONSOLE_TX_Init		(void);
void 	BSP_USART_PC_Init		(void);

#endif /* BSP_INC_BSP_H_ */
