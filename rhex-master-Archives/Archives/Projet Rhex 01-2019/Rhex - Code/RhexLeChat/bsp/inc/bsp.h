/*
 * bsp.h
 *
 *  Created on: 5 août 2017
 *      Author: Laurent
 */

#ifndef BSP_INC_BSP_H_
#define BSP_INC_BSP_H_

#include "stm32f4xx.h"

/*
 * LED driver functions
 */

#define	GREEN	0
#define BLUE	1
#define	RED		2

void	BSP_LED_Init	(void);
void	BSP_LED_On		(uint8_t id);
void	BSP_LED_Off		(uint8_t id);
void	BSP_LED_Toggle	(uint8_t id);

/*
 * NVIC initialization
 */

void BSP_NVIC_Init				(void);

/*
 * Push-Button driver functions
 */

void	BSP_PB_Init		(void);
uint8_t	BSP_PB_GetState	(void);

/*
 * Debug Console driver functions
 */

void	BSP_Console_Init	(void);

/*
 * Init GPIO
 */
void BSP_GPIO_Init(void);

/*
 * Init PWM
 */
void BSP_PWM_Init(void);

/*
 *  Init CAN 1
 */
void BSP_CAN1_Init(void);

/*
 *  Init CAN 2
 */
void BSP_CAN2_Init(void);


void CAN1_WriteMessage(uint32_t ID, uint32_t DLC,uint8_t Data[]);


#endif /* BSP_INC_BSP_H_ */
