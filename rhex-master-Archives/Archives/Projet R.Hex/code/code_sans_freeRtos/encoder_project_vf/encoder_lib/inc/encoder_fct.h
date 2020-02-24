/*
 * encoder_fct.h
 *
 *  Created on: 24 déc. 2016
 *      Author: quentin.massone
 */

#ifndef ENCODER_LIB_INC_ENCODER_FCT_H_
#define ENCODER_LIB_INC_ENCODER_FCT_H_

#include "can_fct.h"

// LSS
#define LSS_ID_Tx 						 (uint16_t)0x7E5	// Master  -> Encoder
#define LSS_ID_Rx  						 (uint16_t)0x7E4	// Encoder -> Master
#define LSS_SwitchModeGlobal_IN 		 (uint16_t)0x0401
#define LSS_SwitchModeGlobal_OUT 		 (uint16_t)0x0400
#define LSS_InquireNodeId 				 (uint8_t) 0x5E
#define LSS_ConfigureNodeId 			 (uint16_t)0x1100
#define LSS_ConfigureBitTimingParameters (uint32_t)0x130000
#define LSS_StoreConfiguration 			 (uint8_t) 0x17

// SDO
#define SDO_ID_Tx 			(uint16_t)0x580 // Encoder -> Master
#define SDO_ID_Rx			(uint16_t)0x600 // Master  -> Encoder
#define SDO_Send_4B			(uint8_t)0x23	// Instruction to send 4 bytes
#define SDO_Send_2B			(uint8_t)0x2B	// Instruction to send 2 bytes
#define SDO_Send_1B			(uint8_t)0x2F	// Instruction to send 1 bytes
#define SDO_Read			(uint8_t)0x40	// Instruction to read

/* There are 2 encoders by network so 2 nodes by network */
#define Node1 (uint8_t)0x3F
#define Node2 (uint8_t)0x3E



typedef enum
{ // Factory default: 250 kBit/s (value 5)
	Encoder_10kb   = (uint8_t)0x00,
	Encoder_20kb   = (uint8_t)0x01,
	Encoder_50kb   = (uint8_t)0x02,
	Encoder_100kb  = (uint8_t)0x03,
	Encoder_125kb  = (uint8_t)0x04,
	Encoder_250kb  = (uint8_t)0x05,
	Encoder_500kb  = (uint8_t)0x06,
	Encoder_1000kb = (uint8_t)0x08
}Encoder_BaudRate;

typedef enum
{
	LSS_10kb     = (uint8_t)0x08,
	LSS_20kb     = (uint8_t)0x07,
	LSS_50kb     = (uint8_t)0x06,
	LSS_Reserved = (uint8_t)0x05,
	LSS_125kb    = (uint8_t)0x04,
	LSS_250kb    = (uint8_t)0x03,
	LSS_500kb    = (uint8_t)0x02,
	// We will not use it because we don't use 800kb with
	// the controller CAN
	//LSS_800kb    = (uint8_t)0x01,
	LSS_1000kb   = (uint8_t)0x00
}LSS_BaudRate;

typedef enum
{
	TPDO1	= (uint16_t)0x1BF,
	TPDO2	= (uint16_t)0x2BF,
	TPDO3	= (uint16_t)0x3BF
}TPDO;




void mode_Operationnel(CAN_TypeDef* CANx, uint8_t node);
void mode_Pre_Operationnel(CAN_TypeDef* CANx, uint8_t node);
void reset_Encoder(CAN_TypeDef* CANx, uint8_t node);
void use_LSS(CAN_TypeDef* CANx, uint8_t node, LSS_BaudRate BR);
void get_2Angles(CAN_TypeDef* CANx, TPDO obj, float* angle1, float* angle2);
void save_all(CAN_TypeDef* CANx, uint8_t node);
float conv_AngleInDegree(uint16_t objAngle);
void reset_Position(CAN_TypeDef* CANx, uint8_t node);
void reset_4Positions();
void disp_Data(CanRxMsg Msg);
void disp_TPDO_Param(CAN_TypeDef* CANx, uint8_t node);
void SDO_ReadAccess(CAN_TypeDef* CANx, uint8_t node, uint16_t index, uint8_t sub_index);
void SDO_WriteAccess(CAN_TypeDef* CANx, uint8_t node, uint8_t DLC, uint16_t index, uint8_t sub_index, uint32_t Data);

#endif /* ENCODER_LIB_INC_ENCODER_FCT_H_ */


