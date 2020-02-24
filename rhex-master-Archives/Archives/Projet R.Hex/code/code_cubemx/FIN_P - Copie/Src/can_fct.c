
#include "can_fct.h"


/* Global structure which contain transmitted and received
 * messages. These variables are global because we process
 * messages one by one. So it's not necessary to initialize
 * these variables for every function which use them. */

CanTxMsg 				TxMessage;
CanRxMsg				RxMessage;


/*----------------------------------------------------------------------------
  Configure Baudrate for CANx
 *----------------------------------------------------------------------------*/
void CAN_BaudRate_Init(CAN_TypeDef* CANx, CAN_BaudRate BaudRate)
{
	/*  Clock Can is APB1_Clock = 42 MHz
		There are several solutions to calculate the baudrate,
		but I chose to fix CAN_BS1 and CAN_BS2 and change
		CAN_Prescaler in function baudrate chosen. 				*/
	uint8_t InitStatus = CAN_InitStatus_Failed;
	uint32_t wait_ack = 0x00000000;

	/* Exit from sleep mode */
	CANx->MCR &= (~(uint32_t)CAN_MCR_SLEEP);

	/* Request initialisation */
	CANx->MCR |= CAN_MCR_INRQ ;

	/* Wait the acknowledge */
	while (((CANx->MSR & CAN_MSR_INAK) != CAN_MSR_INAK) && (wait_ack != 0x0000FFFF))
	{
		wait_ack++;
	}

	/* Specifies the CAN operating mode */
	uint8_t CAN_Mode = CAN_Mode_Normal;

	/* Specifies the maximum number of time quanta the CAN hardware is
	   allowed to lengthen or shorten a bit to perform resynchronization. */
	uint8_t CAN_SJW = CAN_SJW_1tq;

	/* Specifies the number of time quanta in Bit Segment 1 & Segment 2 */
	uint8_t CAN_BS1 = CAN_BS1_7tq;
	uint8_t CAN_BS2 = CAN_BS2_6tq;

	/* Specifies the length of a time quantum : 1 to 1024 */
	uint16_t CAN_Prescaler = APB1_Clock/((13+1)*BaudRate);

	/* Set the bit timing register */
	CANx->BTR = (uint32_t)((uint32_t)CAN_Mode << 30) | \
				((uint32_t)CAN_SJW << 24) | \
				((uint32_t)CAN_BS1 << 16) | \
				((uint32_t)CAN_BS2 << 20) | \
				((uint32_t)CAN_Prescaler - 1);
	/* Request leave initialisation */
	CANx->MCR &= ~(uint32_t)CAN_MCR_INRQ;

   /* Wait the acknowledge */
   wait_ack = 0;

   while (((CANx->MSR & CAN_MSR_INAK) == CAN_MSR_INAK) && (wait_ack != 0x0000FFFF))
   {
	 wait_ack++;
   }

	/* ...and check acknowledged */
	if ((CANx->MSR & CAN_MSR_INAK) == CAN_MSR_INAK)
	{
	  InitStatus = CAN_InitStatus_Failed;
	}
	else
	{
	  InitStatus = CAN_InitStatus_Success ;
	}
}

void CAN1_GPIO_Config()
{
	uint8_t i;

	/* Enable GPIO clock for CAN1 */
	RCC->AHB1ENR |= CAN1_GPIO_CLK;

	/* Configure CAN1_RX_PIN and CAN1_TX_PIN as AF mode */
	CAN1_GPIO_PORT->MODER &= ~((0x03 << (2*CAN1_RX_PIN)) | (0x03 << (2*CAN1_TX_PIN)));
	CAN1_GPIO_PORT->MODER |=   (0x02 << (2*CAN1_RX_PIN)) | (0x02 << (2*CAN1_TX_PIN));

	/* Connect CAN1_RX_PIN to CAN (AF9) */
	i = CAN1_RX_PIN >> 0x03;
	CAN1_GPIO_PORT->AFR[i] &= ~(0xF << (CAN1_RX_PIN - 8*i)*4);
	CAN1_GPIO_PORT->AFR[i] |= (GPIO_AF9_CAN1 << (CAN1_RX_PIN - 8*i)*4);
	/* Connect CAN1_TX_PIN to CAN (AF9) */
	i = CAN1_TX_PIN >> 0x03;
	CAN1_GPIO_PORT->AFR[i] &= ~(0xF << (CAN1_TX_PIN - 8*i)*4);
	CAN1_GPIO_PORT->AFR[i] |= (GPIO_AF9_CAN1 << (CAN1_TX_PIN - 8*i)*4);
}

void CAN2_GPIO_Config()
{
	uint8_t i;

	/* Enable GPIO clock for CAN2*/
	RCC->AHB1ENR |= CAN2_GPIO_CLK;

	/* Configure CAN2_RX_PIN and CAN2_TX_PIN as AF mode */
	CAN2_GPIO_PORT->MODER &= ~((0x03 << (2*CAN2_RX_PIN)) | (0x03 << (2*CAN2_TX_PIN)));
	CAN2_GPIO_PORT->MODER |=   (0x02 << (2*CAN2_RX_PIN)) | (0x02 << (2*CAN2_TX_PIN));

	/* Connect CAN2_RX_PIN to CAN (AF9) */
	i = CAN2_RX_PIN >> 0x03;
	CAN2_GPIO_PORT->AFR[i] &= ~(0xF << (CAN2_RX_PIN - 8*i)*4);
	CAN2_GPIO_PORT->AFR[i] |= (GPIO_AF9_CAN2 << (CAN2_RX_PIN - 8*i)*4);
	/* Connect CAN2_TX_PIN to CAN (AF9) */
	i = CAN2_TX_PIN >> 0x03;
	CAN2_GPIO_PORT->AFR[i] &= ~(0xF << (CAN2_TX_PIN - 8*i)*4);
	CAN2_GPIO_PORT->AFR[i] |= (GPIO_AF9_CAN2 << (CAN2_TX_PIN - 8*i)*4);
}

void CAN_Filter_Config(CAN_TypeDef* CANx)
{
	/* Structure to configure filters of controller */
	CAN_FilterInitTypeDef  	CAN_FilterInitStructure;
	uint8_t x = 0;
	if(CANx == CAN2)
		x = 14;
	/* CAN filter init */
	CAN_FilterInitStructure.CAN_FilterNumber = x;
	CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
	CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
	CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;
	CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;
	CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment = 0;
	CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
	CAN_FilterInit(&CAN_FilterInitStructure);
}

/*----------------------------------------------------------------------------
  Configure controllers CAN1 & CAN2
 *----------------------------------------------------------------------------*/
void CAN_Config(CAN_BaudRate BR_CAN1, CAN_BaudRate BR_CAN2)
{
	CAN1_GPIO_Config();
	CAN2_GPIO_Config();

	/* Enable CAN clock for CAN1 and CAN2 */
	RCC->APB1ENR |= CAN1_CLK;
	RCC->APB1ENR |= CAN2_CLK;

	/* Deinitialize the CAN peripheral registers to their default reset values. */
	CAN_DeInit(CAN1);
	/* Deinitialize the CAN peripheral registers to their default reset values. */
	CAN_DeInit(CAN2);

	/* Configure Baudrate for controllers CAN1 and CAN2 */
	CAN_BaudRate_Init(CAN1, BR_CAN1);
	CAN_BaudRate_Init(CAN2, BR_CAN2);

	CAN_Filter_Config(CAN1);
}

/*----------------------------------------------------------------------------
  Write a message to CAN peripheral and transmit it.
 *----------------------------------------------------------------------------*/
uint8_t write_msg(CAN_TypeDef* CANx, uint16_t id, uint8_t DLC, uint64_t Msg, uint8_t display)
{
	uint8_t i, j, TransmitMailbox;
	if (CANx == CAN1)
		CAN_Filter_Config(CAN1);
	else if(CANx == CAN2)
		CAN_Filter_Config(CAN2);

	TxMessage.StdId = (uint32_t)id;
	if(DLC != 0)
		TxMessage.RTR = CAN_RTR_DATA;
	else
		TxMessage.RTR = CAN_RTR_REMOTE;

	TxMessage.IDE = CAN_ID_STD; // Standard id : 11 bits
	TxMessage.DLC = DLC;
	j = DLC;
	for(i=0; i<DLC; i++)
	{
		j--;
		TxMessage.Data[i] = (uint8_t)(Msg>>(8*j));
	}
	TransmitMailbox = CAN_Transmit(CANx, &TxMessage);
	i = 0;
	/* Waiting for the end of transmission */
	while((CAN_TransmitStatus(CANx, TransmitMailbox)  !=  CANTXOK) && (i  !=  0xFFF))
	{
	  i++;
	}
	delay_ms(10);
	if(i == 0xFFF)
	{
		my_printf("Error message transmission");
		return 0;
	}
	else
	{
		if (display)
			print_msgTX();
		return 1;
	}
}

/*----------------------------------------------------------------------------
  Read a message from CAN peripheral and release it
 *----------------------------------------------------------------------------*/
CanRxMsg read_msg(CAN_TypeDef* CANx, uint8_t display)
{
	uint8_t i = 0;
	if (CANx == CAN1)
		CAN_Filter_Config(CAN1);
	else if(CANx == CAN2)
		CAN_Filter_Config(CAN2);
	while((CAN_MessagePending(CANx, CAN_FIFO0) < 1) && (i  !=  0xFFF))
	{
	  i++;
	}
	CAN_Receive(CANx, CAN_FIFO0, &RxMessage);
	delay_ms(10);
	if(i == 0xFFF)
	{
		my_printf("Error message transmission");
		return RxMessage;
	}
	else
	{
		if (display)
			print_msgRX();
		return RxMessage;
	}
}


/*----------------------------------------------------------------------------
  Write a RTR message to CAN peripheral and transmit it.
 *----------------------------------------------------------------------------*/
uint8_t RTR(CAN_TypeDef* CANx, uint32_t id)
{
	return write_msg(CANx, id, 0, 0, 1);
}

/*----------------------------------------------------------------------------
  Display a TX message on the port COM with USART3
 *----------------------------------------------------------------------------*/
void print_msgTX()
{
	uint8_t i = 0;
	my_printf("\n\rid : %x  DLC : %d  Data : ", TxMessage.StdId, TxMessage.DLC);
	for (i=0; i<TxMessage.DLC; i++)
		my_printf("%x ", TxMessage.Data[i]);
	my_printf("\n");
}

/*----------------------------------------------------------------------------
  Display a RX message on the port COM with USART3
 *----------------------------------------------------------------------------*/
void print_msgRX()
{
	uint8_t i = 0;
	my_printf("\n\rid : %x  DLC : %d  Data : ", RxMessage.StdId, RxMessage.DLC);
	for (i=0; i<RxMessage.DLC; i++)
		my_printf("%x ", RxMessage.Data[i]);
	my_printf("\n");
}



