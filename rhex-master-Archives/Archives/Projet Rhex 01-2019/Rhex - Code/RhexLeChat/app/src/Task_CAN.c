/*
 * Task_CAN.c
 *
 *  Created on: 5 déc. 2018
 *      Author: romain
 */

#include "Task_CAN.h"

void vTask_CAN1 (void *pvParameters)
{
	// CAN 1 GPIO Configuration
	// PB8 --> CAN1_RX
	// PB9 --> CAN1_TX
	BSP_CAN1_Init();

	ConfigEncodeur(CAN1);

	// Enable PB4 and PB1 EXTI interrupts
	NVIC_SetPriority(CAN1_RX0_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY+2);
	NVIC_EnableIRQ(CAN1_RX0_IRQn);

	// Take the semaphore once to make sure it is empty
	//xSemaphoreTake(xCAN1Sem, 0);

	my_printf("CAN1 Task init OK\r\n");


	while(1)
	{

		// Wait for the CAN1 interrupt semaphore
		 // en mutex à cause des deux interruptions
		// Take Mutex

			if (CAN_RF0R_FMP0_Pos==1)   // deuxieme message dans la fifo 0
			{
				/*
				xSemaphoreTake(xCAN1Sem,portMAX_DELAY);
				*/
			}
			/*if (CAN_RF0R_FMP0_Pos==3)                        // troisieme message dans la fifo 0
			{

			}*/

		//xSemaphoreTake(xConsoleMutex, portMAX_DELAY);

		my_printf("CAN1_tram1 Task\r\n");

		// recuperer la première tram dans la fifo envoyé par l'encodeur
		// mettre dans les registres
		//CAN_RxMessage();

		/*if(id== idEncodeur1) /// trouver les id des encodeurs
		{
			regs.current_pos1=Data;
		}

*/

		// Release Mutex
		/*
		xSemaphoreGive(xConsoleMutex);
*/
		vTaskDelay(20);
		//CAN_RxMessage();
		/*
		if(id== idEncodeur1)
		{
			regs.current_pos1=
		}
		elseif(id== idEncodeur1)
		{
			regs.current_pos2=
		}
		*/
	}
}


void vTask_CAN2 (void *pvParameters)
{
	// CAN 1 GPIO Configuration
	// PB8 --> CAN1_RX
	// PB9 --> CAN1_TX
	BSP_CAN2_Init();

	ConfigEncodeur(CAN2);

	// Enable PB4 and PB1 EXTI interrupts
	NVIC_SetPriority(CAN2_RX1_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY+2);
	NVIC_EnableIRQ(CAN2_RX1_IRQn);

	// Take the semaphore once to make sure it is empty


	/*if (CAN_RF1R_FMP1_Pos==3)                       // troisieme message dans la fifo 1
		{

		}*/
	/*
	xSemaphoreTake(xCAN2Sem, 0);
*/
	my_printf("CAN2 Task init OK\r\n");


	while(1)
	{
		// Wait for the CAN1 interrupt semaphore
		if (CAN_RF1R_FMP1_Pos==1)   // premier message dans la fifo 1
					{
			//xSemaphoreTake(xCAN2Sem,portMAX_DELAY);
					}


		// Take Mutex
		//xSemaphoreTake(xConsoleMutex2, portMAX_DELAY);
		my_printf("CAN2_tram1 Task\r\n");

		//CAN_RxMessage();
		/*
		if(id== idEncodeur1)
		{
			regs.current_pos3=
		}
		elseif(id== idEncodeur2)
		{
			regs.current_pos4=
		}

		if(id== idEncodeur3)
		{
			regs.current_pos3=Data;
		}
		*/
		// Release Mutex
		//xSemaphoreGive(xConsoleMutex2);

		vTaskDelay(20);
	}
}

