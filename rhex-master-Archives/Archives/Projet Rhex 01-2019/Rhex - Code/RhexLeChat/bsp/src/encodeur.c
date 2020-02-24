/*
 * encodeur.c
 *
 *  Created on: 7 nov. 2018
 *      Author: romain
 */

#include "can.h"
#include "encodeur.h"

/*
 * SET Pre Op Mode on encoder
 * VERT Clignote tres vite
 */
void mode_Pre_Operationnel(CAN_TypeDef * CAN_id, uint8_t ID_Encodeur)
{
	uint32_t ID;
	uint32_t DLC;
	uint32_t msg;

	ID=0x00;
	DLC=2;
	msg = 0x8000 + ID_Encodeur ;
	CAN_TxMessage(CAN_id,ID, DLC,msg);
}

/*
 * SET Op Mode on encoder
 * VERT FIXE
 */
void mode_Operationnel(CAN_TypeDef * CAN_id, uint8_t ID_Encodeur)
{
	CAN_HeaderTypeDef *pHeader;
	uint8_t Data[8];
	uint32_t ID;
	uint32_t DLC;
	uint32_t msg;

	ID=0x00;
	DLC=2;
	msg = 0x0100 + ID_Encodeur ;
	CAN_TxMessage(CAN_id,ID, DLC,msg);

	CAN_RxMessage(CAN_id, pHeader, Data);
	CAN_RxMessage(CAN_id, pHeader, Data);
	CAN_RxMessage(CAN_id, pHeader, Data);
}

void ConfigEncodeur(CAN_TypeDef * CAN_id)
{
	mode_Pre_Operationnel(CAN_id, 0x3F);
	my_printf("PREOP-3F OK\r\n");
	mode_Operationnel(CAN_id, 0x3F);
	my_printf("OP-3F OK\r\n");

	mode_Pre_Operationnel(CAN_id, 0x3E);
	my_printf("PREOP-3E OK\r\n");
	mode_Operationnel(CAN_id, 0x3E);
	my_printf("OP-3E OK\r\n");
}
