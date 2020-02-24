/*
 * can.h
 *
 *  Created on: 19 oct. 2018
 *      Author: romain
 */

#ifndef BSP_INC_CAN_H_
#define BSP_INC_CAN_H_

#include "stm32f4xx.h"
#include "stm32f4xx_hal_can.h"
#include "main.h"

typedef struct
{
	uint32_t StdId;    //!< Specifies the standard identifier.
	uint32_t ExtId;    //!< Specifies the extended identifier.
	uint32_t IDE;      //!< Specifies the type of identifier for the message that will be transmitted.
	uint32_t RTR;      //!< Specifies the type of frame for the message that will be transmitted.
	uint32_t DLC;      //!< Specifies the length of the frame that will be transmitted.
	uint32_t Timestamp; //!< Specifies the timestamp counter value captured on start of frame reception.
	uint32_t FilterMatchIndex; //!< Specifies the index of matching acceptance filter element.

} CAN_HeaderTypeDef;

/* Global functions */
int my_printf	(const char *format, ...);
int my_sprintf	(char *out, const char *format, ...);

void _Error_Handler(char * file, int line);

/*
 * INIT function
 */

void CAN1_Init(void);
void CAN2_Init(void);

/*
 * CAN filter configuration BANK
 */

void CAN_ConfigFilter(void);

/*
 * Start the CAN module
 */
void CAN_Start(void);

/*
 * Send message by CAN
 */
void CAN_TxMessage(CAN_TypeDef * CAN_id, uint32_t ID, uint32_t DLC, uint32_t msg);

void CAN_RxMessage(CAN_TypeDef * CAN_id,CAN_HeaderTypeDef *pHeader, uint32_t Data[]);

uint32_t CAN_RxFifoFillLevel(CAN_TypeDef * CAN_id, uint32_t fifoNumber);

#endif /* BSP_INC_CAN_H_ */
