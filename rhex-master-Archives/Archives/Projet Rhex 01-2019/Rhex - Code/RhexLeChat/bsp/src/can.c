/*
 * can.c
 *
 *  Created on: 19 oct. 2018
 *      Author: romain
 */

#include "can.h"


void CAN1_Init()
{
	/* Exit from sleep mode */
	CAN1->MCR &= ~(CAN_MCR_SLEEP);

	/* Check Sleep mode leave acknowledge */
	//while ((CAN1->MSR & CAN_MSR_SLAK) != RESET){}

	/* Request initialisation */
	CAN1->MCR |= CAN_MCR_INRQ;

	/* Wait initialisation acknowledge */
	//while ((CAN1->MSR & CAN_MSR_INAK) == RESET){}

	/* Disable the time triggered communication mode TTCM
	 * Disable the automatic bus-off management ABOM
	 * Disable the automatic wake-up mode AWUM
	 * Disable the automatic retransmission NART
	 * Disable the receive FIFO locked mode RFLM
	 * Disable the transmit FIFO priority TXFP
	 */
	CAN1->MCR &= ~( CAN_MCR_TTCM | CAN_MCR_ABOM | CAN_MCR_AWUM | CAN_MCR_NART | CAN_MCR_RFLM |CAN_MCR_TXFP);

	/* Set the bit timing register */
	CAN1->BTR =(uint32_t)(CAN_MODE_NORMAL | CAN_SJW_1TQ  | CAN_BS1_7TQ | CAN_BS2_6TQ | (3 - 1U));
}


void CAN2_Init()
{
	/* Exit from sleep mode */
	CAN2->MCR &= ~(CAN_MCR_SLEEP);

	/* Check Sleep mode leave acknowledge */
	//while ((CAN2->MSR & CAN_MSR_SLAK) != RESET){}

	/* Request initialisation */
	CAN2->MCR |= CAN_MCR_INRQ;

	/* Wait initialisation acknowledge */
	//while ((CAN2->MSR & CAN_MSR_INAK) == RESET){}

	/* Disable the time triggered communication mode TTCM
	 * Disable the automatic bus-off management ABOM
	 * Disable the automatic wake-up mode AWUM
	 * Disable the automatic retransmission NART
	 * Disable the receive FIFO locked mode RFLM
	 * Disable the transmit FIFO priority TXFP
	 */
	CAN2->MCR &= ~( CAN_MCR_TTCM | CAN_MCR_ABOM | CAN_MCR_AWUM | CAN_MCR_NART | CAN_MCR_RFLM |CAN_MCR_TXFP);

	/* Set the bit timing register */
	CAN2->BTR =(uint32_t)(CAN_MODE_NORMAL | CAN_SJW_1TQ  | CAN_BS1_7TQ | CAN_BS2_6TQ | (3 - 1U));
}

/*
 * Configures the CAN reception filter
 * CAN1 filter 0 to 9
 * 		Filter 0: 3EC1
 * 		Filter 1: 3FC1
 * 		Filter 2:
 * 		Filter 3:
 * CAN2 filter 10 to 27
 *		Filter 10: 3EC2
 * 		Filter 11: 3FC2
 * 		Filter 12:
 * 		Filter 13:
 */
void CAN_ConfigFilter()
{
	//////////////////////////////////////////////////////////////
	/*					Filtre 0 laisse tout passer				*/
	//////////////////////////////////////////////////////////////
	uint32_t FilterIdHigh0=0;
	uint32_t FilterIdLow0=0;
	uint32_t FilterMaskIdHigh0=0;
	uint32_t FilterMaskIdLow0=0;

	/* Initialisation mode for the filter */
	CAN1->FMR |= CAN_FMR_FINIT ;

	/* Filter Deactivation */
	CAN1->FA1R &= ~ CAN_FA1R_FACT0;

	/* Select the start filter number of CAN2 slave instance */
	CAN1->FMR &= ~CAN_FMR_CAN2SB;
	CAN1->FMR |= 0x0A << CAN_FMR_CAN2SB_Pos;

	/* Filter Scale */
	/* 32-bit scale for the filter */
	CAN1->FS1R|=CAN_FS1R_FSC0;

	/* Filter Mode */
	/* Id/Mask mode for the filter bank 0 */
	CAN1->FM1R &= ~ CAN_FM1R_FBM0;

	/* 32-bit identifier or First 32-bit identifier */ //Dominant 0 recessif 1
	CAN1->sFilterRegister[0].FR1 =((0x0000FFFFU & FilterIdHigh0) << 16U) |(0x0000FFFFU & FilterIdLow0);

	/* 32-bit mask or Second 32-bit identifier */
	CAN1->sFilterRegister[0].FR2 =((0x0000FFFFU & FilterMaskIdHigh0) << 16U) |(0x0000FFFFU & FilterMaskIdLow0);

	/* Filter FIFO assignment */
	/* FIFO 0 assignation for the filter */
	CAN1->FFA1R &= ~CAN_FFA1R_FFA0;

	/* FIFO 1 assignation for the filter */
	CAN1->FFA1R |= CAN_FFA1R_FFA10;

	/* Filter activation */
	CAN1->FA1R|= CAN_FA1R_FACT0;

	/* Leave the initialisation mode for the filter */
	CAN1->FMR &= ~CAN_FMR_FINIT;
}

/*
 *Start the CAN module
 */
void CAN_Start(void)
{
	/* Request leave initialisation */
	CAN1->MCR &= ~CAN_MCR_INRQ;

	/* Wait the acknowledge */
	while ((CAN1->MSR & CAN_MSR_INAK) != RESET){}

	/* Request leave initialisation */
	CAN2->MCR &= ~CAN_MCR_INRQ;

	/* Wait the acknowledge */
	while ((CAN2->MSR & CAN_MSR_INAK) != RESET){}
}


/*
 * Send message
 * Standard id :11 bits CAN_ID_STD
 */
void CAN_TxMessage(CAN_TypeDef * CAN_id, uint32_t ID, uint32_t DLC, uint32_t msg)
{
	uint32_t transmitmailbox;
	uint32_t RTR;
	uint8_t i,j;
	uint32_t Data[8];

	if (DLC != 0)
	{
		RTR = CAN_RTR_DATA;
	}
	else
	{
		RTR = CAN_RTR_REMOTE;
	}

	/* Check that all the Tx mailboxes are not full */
	if (((CAN_id->TSR & CAN_TSR_TME0) != RESET) ||((CAN_id->TSR & CAN_TSR_TME1) != RESET) ||((CAN_id->TSR & CAN_TSR_TME2) != RESET))
	{
		/* Select an empty transmit mailbox */
		transmitmailbox = (CAN_id->TSR & CAN_TSR_CODE) >> CAN_TSR_CODE_Pos;

		/* Set up the Id */
		CAN_id->sTxMailBox[transmitmailbox].TIR = ((ID << CAN_TI0R_STID_Pos) | RTR);

		/* Set up the DLC */
		DLC &= (uint8_t)0x0000000F;
		CAN_id->sTxMailBox[transmitmailbox].TDTR &= (uint32_t)0xFFFFFFF0U;
		CAN_id->sTxMailBox[transmitmailbox].TDTR = (uint32_t)DLC;

		j = DLC;
		for (i = 0; i < DLC; i++)
		{
			j--;
			//TODO verif octet / transtypage <=> masque 8 bits
			Data[i] = (uint8_t) (msg >> (8 * j));
		}

		/* Set up the data field */
		CAN_id->sTxMailBox[transmitmailbox].TDHR=(((uint32_t)Data[7] << CAN_TDH0R_DATA7_Pos) | ((uint32_t)Data[6] << CAN_TDH0R_DATA6_Pos) | ((uint32_t)Data[5] << CAN_TDH0R_DATA5_Pos) | ((uint32_t)Data[4] << CAN_TDH0R_DATA4_Pos));
		CAN_id->sTxMailBox[transmitmailbox].TDLR=(((uint32_t)Data[3] << CAN_TDL0R_DATA3_Pos) | ((uint32_t)Data[2] << CAN_TDL0R_DATA2_Pos) | ((uint32_t)Data[1] << CAN_TDL0R_DATA1_Pos) | ((uint32_t)Data[0] << CAN_TDL0R_DATA0_Pos));

		/* Request transmission */
		CAN_id->sTxMailBox[transmitmailbox].TIR |= CAN_TI0R_TXRQ;

		i = 0;

		my_printf("\n\rTx -> id : %x  DLC : %d  Data : ", ID, DLC);
		for (i = 0; i < DLC; i++)
		{
			my_printf("%x ", Data[i]);
		}
		my_printf("\n\r");
	}
	else
	{
		my_printf("Error CAN Tx message !\r\n");
	}
}

/*
 *
 */
void CAN_RxMessage(CAN_TypeDef * CAN_id,CAN_HeaderTypeDef *pHeader, uint32_t Data[])
{

	int8_t fifoNumber;

	if (CAN_id==CAN1)
	{
		fifoNumber=0;
	}
	else if(CAN_id==CAN2)
	{
		fifoNumber=1;
	}

	/* Wait message */
	my_printf("\n\r fifo : %d  ",CAN_RxFifoFillLevel(CAN_id,fifoNumber));
	//while(CAN_RxFifoFillLevel(CAN_id,fifoNumber)==0){}

	/* Get the header */
	pHeader->IDE = CAN_RI0R_IDE & CAN_id->sFIFOMailBox[fifoNumber].RIR;
	if (pHeader->IDE == CAN_ID_STD)
	{
		pHeader->StdId = (CAN_RI0R_STID & CAN_id->sFIFOMailBox[fifoNumber].RIR) >> CAN_TI0R_STID_Pos;
	}
	else
	{
		pHeader->ExtId = ((CAN_RI0R_EXID | CAN_RI0R_STID) & CAN_id->sFIFOMailBox[fifoNumber].RIR) >> CAN_RI0R_EXID_Pos;
	}
	pHeader->RTR = (CAN_RI0R_RTR & CAN_id->sFIFOMailBox[fifoNumber].RIR) >> CAN_RI0R_RTR_Pos;
	pHeader->DLC = (CAN_RDT0R_DLC & CAN_id->sFIFOMailBox[fifoNumber].RDTR) >> CAN_RDT0R_DLC_Pos;
	pHeader->FilterMatchIndex = (CAN_RDT0R_FMI & CAN_id->sFIFOMailBox[fifoNumber].RDTR) >> CAN_RDT0R_FMI_Pos;
	pHeader->Timestamp = (CAN_RDT0R_TIME & CAN_id->sFIFOMailBox[fifoNumber].RDTR) >> CAN_RDT0R_TIME_Pos;

	/* Get the data */
	Data[0] = (CAN_RDL0R_DATA0 & CAN_id->sFIFOMailBox[fifoNumber].RDLR) >> CAN_RDL0R_DATA0_Pos;
	Data[1] = (CAN_RDL0R_DATA1 & CAN_id->sFIFOMailBox[fifoNumber].RDLR) >> CAN_RDL0R_DATA1_Pos;
	Data[2] = (CAN_RDL0R_DATA2 & CAN_id->sFIFOMailBox[fifoNumber].RDLR) >> CAN_RDL0R_DATA2_Pos;
	Data[3] = (CAN_RDL0R_DATA3 & CAN_id->sFIFOMailBox[fifoNumber].RDLR) >> CAN_RDL0R_DATA3_Pos;
	Data[4] = (CAN_RDH0R_DATA4 & CAN_id->sFIFOMailBox[fifoNumber].RDHR) >> CAN_RDH0R_DATA4_Pos;
	Data[5] = (CAN_RDH0R_DATA5 & CAN_id->sFIFOMailBox[fifoNumber].RDHR) >> CAN_RDH0R_DATA5_Pos;
	Data[6] = (CAN_RDH0R_DATA6 & CAN_id->sFIFOMailBox[fifoNumber].RDHR) >> CAN_RDH0R_DATA6_Pos;
	Data[7] = (CAN_RDH0R_DATA7 & CAN_id->sFIFOMailBox[fifoNumber].RDHR) >> CAN_RDH0R_DATA7_Pos;

	/* Release RX FIFO 0 */
	if (fifoNumber==0)
	{
		CAN_id->RF0R |= CAN_RF0R_RFOM0;
	}
	else
	{
		CAN_id->RF1R |= CAN_RF1R_RFOM1;
	}
	uint8_t i = 0;
	my_printf("\n\rRx -> id : %x  DLC : %d  Data : ", pHeader->StdId, pHeader->DLC);
	for (i = 0; i < pHeader->DLC; i++)
		my_printf("%x ", Data[i]);
	my_printf("\n\r");
}

uint32_t CAN_RxFifoFillLevel(CAN_TypeDef * CAN_id, uint32_t fifoNumber)
{
	uint32_t filllevel = 0U;

	if (fifoNumber == CAN_RX_FIFO0)
	{
		filllevel = CAN_id->RF0R & CAN_RF0R_FMP0;
	}
	else /* RxFifo == CAN_RX_FIFO1 */
	{
		filllevel = CAN_id->RF1R & CAN_RF1R_FMP1;
	}

	/* Return Rx FIFO fill level */
	return filllevel;
}






