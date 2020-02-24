/*
 * encodeur.h
 *
 *  Created on: 7 nov. 2018
 *      Author: romai
 */

#ifndef BSP_INC_ENCODEUR_H_
#define BSP_INC_ENCODEUR_H_

#include "stm32f4xx.h"

/* Global functions */
int my_printf	(const char *format, ...);
int my_sprintf	(char *out, const char *format, ...);

void mode_Pre_Operationnel(CAN_TypeDef * CAN_id, uint8_t ID_Encodeur);

void mode_Operationnel(CAN_TypeDef * CAN_id, uint8_t ID_Encodeur);

void ConfigEncodeur(CAN_TypeDef * CAN_id);

#endif /* BSP_INC_ENCODEUR_H_ */
