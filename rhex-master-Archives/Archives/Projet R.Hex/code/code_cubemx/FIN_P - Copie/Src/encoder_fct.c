
#include "encoder_fct.h"



void mode_Operationnel(CAN_TypeDef* CANx, uint8_t node)
{
	write_msg(CANx, 0x00, 2, 0x0100 + node, 1);
	/* 4 messages are sent after a switch in operational mode.
	 * However, the FIFO can contains 3 messages at maximum, so
	 * one message will be overwritten.
	 */
	/* We read 3 messages in 4 */
	read_msg(CANx, 1);
	read_msg(CANx, 1);
	read_msg(CANx, 1);
}
void mode_Pre_Operationnel(CAN_TypeDef* CANx, uint8_t node)
{
	write_msg(CANx, 0x00, 2, 0x8000 + node, 1);
}

void reset_Encoder(CAN_TypeDef* CANx, uint8_t node)
{
	write_msg(CANx, 0x00, 2, 0x8100 + node, 1);
}


void use_LSS(CAN_TypeDef* CANx, uint8_t node, LSS_BaudRate BR)
{
	if((node <= 0xFF && node > 0) || (BR >= 0 && BR <= 8 && BR != LSS_Reserved && BR != 1))
	{
		/* Enter in the LSS mode */
		//DLC = 2
		write_msg(CANx, LSS_ID_Tx, 2, LSS_SwitchModeGlobal_IN, 1);
		if(node <= 0xFF && node > 0)
		{
			/* Change the node */
			//DLC = 1;
			write_msg(CANx, LSS_ID_Tx, 1, LSS_ConfigureNodeId+node, 1);
			read_msg(CANx, 1);
		}
		if(BR >= 0 && BR <= 8 && BR != LSS_Reserved && BR != 1)
		{
			/* Change the baud rate */
			//DLC = 3;
			write_msg(CANx, LSS_ID_Tx, 3, LSS_ConfigureBitTimingParameters+BR, 1);
			read_msg(CANx, 1);

			/* We also change the baud rate of controller CAN */
			switch(BR)
			{
				case LSS_10kb: CAN_BaudRate_Init(CANx, BaudRate_10kb);
				break;
				case LSS_20kb: CAN_BaudRate_Init(CANx, BaudRate_20kb);
				break;
				case LSS_50kb: CAN_BaudRate_Init(CANx, BaudRate_50kb);
				break;
				case LSS_125kb: CAN_BaudRate_Init(CANx, BaudRate_125kb);
				break;
				case LSS_250kb: CAN_BaudRate_Init(CANx, BaudRate_250kb);
				break;
				case LSS_500kb: CAN_BaudRate_Init(CANx, BaudRate_500kb);
				break;
				case LSS_1000kb: CAN_BaudRate_Init(CANx, BaudRate_1000kb);
				break;
			}
		}
		/* Save new configuration */
		//DLC = 1;
		write_msg(CANx, LSS_ID_Tx, 1, LSS_StoreConfiguration, 1);
		read_msg(CANx, 1);
		/* Stop LSS mode */
		//DLC = 2;
		write_msg(CANx, LSS_ID_Tx, 2, LSS_SwitchModeGlobal_OUT, 1);
		/* Reset */
		reset_Encoder(CANx, node);
	}
}


void SDO_WriteAccess(CAN_TypeDef* CANx, uint8_t node, uint8_t DLC, uint16_t index, uint8_t sub_index, uint32_t Data)
{
	uint8_t inst;
	uint32_t cmd;
	uint64_t msg;
	if(DLC == 5)
		inst = SDO_Send_1B;
	else if(DLC == 6)
		inst = SDO_Send_2B;
	else if(DLC == 8)
		inst = SDO_Send_4B;
	else
		my_printf("Error message transmission");

	cmd = ((uint32_t)inst << 24) + ((uint32_t)index << 8) + (uint32_t)sub_index;
	msg = ((uint64_t)cmd << (DLC-4)*8) + (uint64_t)Data;
	write_msg(CANx, SDO_ID_Rx + node, DLC, msg, 0);
}

void SDO_ReadAccess(CAN_TypeDef* CANx, uint8_t node, uint16_t index, uint8_t sub_index)
{
	uint32_t cmd = ((uint32_t)SDO_Read << 24) + ((uint32_t)index << 8) + (uint32_t)sub_index;

	write_msg(CANx, SDO_ID_Rx + node, 4, cmd, 0);
}

void save_all(CAN_TypeDef* CANx, uint8_t node)
{
	SDO_WriteAccess(CANx, node, 8, 0x1010, 0x00, 0x73617665);
	read_msg(CANx, 0);
}


void get_2Angles(CAN_TypeDef* CANx, TPDO obj, float* angle1, float* angle2)
{
	while(((CANx->RF0R) & CAN_RF0R_FMP0) != 0)
		CAN_FIFORelease(CANx, CAN_FIFO0);
	//RTR(CANx, obj);
	SDO_ReadAccess(CANx, Node1, 0x0460, 0x00);
	CanRxMsg msg1 = read_msg(CANx, 1);
	SDO_ReadAccess(CANx, Node2, 0x0460, 0x00);
	CanRxMsg msg2 = read_msg(CANx, 1);
	uint16_t objAngle1 = msg1.Data[4] + ((uint16_t)msg1.Data[5] << 8);
	uint16_t objAngle2 = msg2.Data[4] + ((uint16_t)msg2.Data[5] << 8);

	my_printf("%d %d", objAngle1, objAngle2);

	*angle1 = conv_AngleInDegree(objAngle1);
	*angle2 = conv_AngleInDegree(objAngle2);
}




float conv_AngleInDegree(uint16_t objAngle)
{
	float angle = objAngle * (45.0f/8192);
	return angle;
}

void reset_Position(CAN_TypeDef* CANx, uint8_t node)
{
	mode_Pre_Operationnel(CANx, node);
	SDO_WriteAccess(CANx, node, 8, 0x0360, 0x00, 0x01000000);
	save_all(CANx, node);
	reset_Encoder(CANx, node);
}

void reset_4Positions()
{
	reset_Position(CAN1, Node1);
	reset_Position(CAN1, Node2);
	reset_Position(CAN2, Node1);
	reset_Position(CAN2, Node2);

}


void disp_Data(CanRxMsg Msg)
{
	uint8_t i;
	uint8_t j = 0;
	if(Msg.StdId >> 8 == 5) // SDO TX
	{
		j = 4;
	}
	for(i=Msg.DLC-1; i>=j; i--)
	{
		if(Msg.Data[i] == 0)
			my_printf("00 ");
		else if(Msg.Data[i] < 16)
			my_printf("0%x ", Msg.Data[i]);
		else
			my_printf("%x ", Msg.Data[i]);
	}

}

void disp_TPDO_Param(CAN_TypeDef* CANx, uint8_t node)
{
	CanRxMsg msg;
	uint8_t i;
	my_printf("\n\r***** 1800h : TPDO1 Communication Parameter *****");
	SDO_ReadAccess(CANx, node, 0x0018, 0x01);
	my_printf("\n\r      - 01h : COB-ID :             ");
	disp_Data(read_msg(CANx, 0));
	SDO_ReadAccess(CANx, node, 0x0018, 0x02);
	my_printf("\n\r      - 02h : Transmission type :  ");
	disp_Data(read_msg(CANx, 0));
	SDO_ReadAccess(CANx, node, 0x0018, 0x03);
	my_printf("\n\r      - 03h : inhibit time :       ");
	disp_Data(read_msg(CANx, 0));
	SDO_ReadAccess(CANx, node, 0x0018, 0x05);
	my_printf("\n\r      - 05h : Event timer :        ");
	disp_Data(read_msg(CANx, 0));

	my_printf("\n\r***** 1801h : TPDO2 Communication Parameter *****");
	SDO_ReadAccess(CANx, node, 0x0118, 0x01);
	my_printf("\n\r      - 01h : COB-ID :             ");
	disp_Data(read_msg(CANx, 0));
	SDO_ReadAccess(CANx, node, 0x0118, 0x02);
	my_printf("\n\r      - 02h : Transmission type :  ");
	disp_Data(read_msg(CANx, 0));
	SDO_ReadAccess(CANx, node, 0x0118, 0x03);
	my_printf("\n\r      - 03h : inhibit time :       ");
	disp_Data(read_msg(CANx, 0));
	SDO_ReadAccess(CANx, node, 0x0118, 0x05);
	my_printf("\n\r      - 05h : Event timer :        ");
	disp_Data(read_msg(CANx, 0));

	my_printf("\n\r***** 1802h : TPDO3 Communication Parameter *****");
	SDO_ReadAccess(CANx, node, 0x0218, 0x01);
	my_printf("\n\r      - 01h : COB-ID :             ");
	disp_Data(read_msg(CANx, 0));
	SDO_ReadAccess(CANx, node, 0x0218, 0x02);
	my_printf("\n\r      - 02h : Transmission type :  ");
	disp_Data(read_msg(CANx, 0));
	SDO_ReadAccess(CANx, node, 0x0218, 0x03);
	my_printf("\n\r      - 03h : inhibit time :       ");
	disp_Data(read_msg(CANx, 0));
	SDO_ReadAccess(CANx, node, 0x0218, 0x05);
	my_printf("\n\r      - 05h : Event timer :        ");
	disp_Data(read_msg(CANx, 0));

	my_printf("\n\r***** 1A00h : TPDO1 Mapping *****");
	SDO_ReadAccess(CANx, node, 0x001A, 0x00);
	my_printf("\n\r      - 00h : nb objects :         ");
	msg = read_msg(CANx, 0);
	disp_Data(msg);
	for(i = 1; i <= msg.Data[4]; i++)
	{
		SDO_ReadAccess(CANx, node, 0x001A, i);
		my_printf("\n\r      - 0%dh : nb objects :         ", i);
		disp_Data(read_msg(CANx, 0));
	}

	my_printf("\n\r***** 1A01h : TPDO2 Mapping *****");
	SDO_ReadAccess(CANx, node, 0x011A, 0x00);
	my_printf("\n\r      - 00h : nb objects :         ");
	msg = read_msg(CANx, 0);
	disp_Data(msg);
	for(i = 1; i <= msg.Data[4]; i++)
	{
		SDO_ReadAccess(CANx, node, 0x011A, i);
		my_printf("\n\r      - 0%dh : nb objects :         ", i);
		disp_Data(read_msg(CANx, 0));
	}

	my_printf("\n\r***** 1A02h : TPDO3 Mapping *****");
	SDO_ReadAccess(CANx, node, 0x021A, 0x00);
	my_printf("\n\r      - 00h : nb objects :         ");
	msg = read_msg(CANx, 0);
	disp_Data(msg);
	for(i = 1; i <= msg.Data[4]; i++)
	{
		SDO_ReadAccess(CANx, node, 0x021A, i);
		my_printf("\n\r      - 0%dh : nb objects :         ", i);
		disp_Data(read_msg(CANx, 0));
	}
}
