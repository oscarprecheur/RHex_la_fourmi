/*
 * Task_ASSERV.c
 *
 *  Created on: 5 déc. 2018
 *      Author: romain
 */

#include "Task_ASSERV.h"

void vTask_ASSERV (void *pvParameters)
{
	float DeltaPos1, DeltaPos2, DeltaPos3, DeltaPos4;
	float vitesse1,vitesse2,vitesse3,vitesse4;
	/* BSP_PWM_Init()
	 * TIM1 Channels 1, 2, 3, 4 is used to control 4 PWM for motor
	 * Channel 1 -> PE9		10 KHz OK
	 * Channel 2 -> PE11    10 KHz OK
	 * Channel 3 -> PE13    10 KHz OK
	 * Channel 4 -> PE14    10 KHz OK
	 */
	BSP_PWM_Init();

	// Take the semaphore once to make sure it is empty
	//xSemaphoreTake(xASSERVSem, 0);

	// Set initial values
	DeltaPos1 = 0;
	DeltaPos2 = 0;
	DeltaPos3 = 0;
	DeltaPos4 = 0;

	my_printf("ASSERV Task init OK\r\n");

	while(1)
	{
		// Wait for the CAN1 interrupt semaphore
		//xSemaphoreTake(xASSERVSem,portMAX_DELAY);

		my_printf("ASSERV Task\r\n");

		DeltaPos1 += REGS.goal_pos1-REGS.current_pos1;
		DeltaPos2 += REGS.goal_pos2-REGS.current_pos2;
		DeltaPos3 += REGS.goal_pos3-REGS.current_pos3;
		DeltaPos4 += REGS.goal_pos4-REGS.current_pos4;

		vitesse1=(REGS.goal_pos1-REGS.current_pos1)*REGS.kp1+DeltaPos1*REGS.ki1;
		vitesse2=(REGS.goal_pos2-REGS.current_pos2)*REGS.kp2+DeltaPos2*REGS.ki2;
		vitesse3=(REGS.goal_pos3-REGS.current_pos3)*REGS.kp3+DeltaPos3*REGS.ki3;
		vitesse4=(REGS.goal_pos4-REGS.current_pos4)*REGS.kp4+DeltaPos4*REGS.ki4;

		if (vitesse1 > VMAX) vitesse1=VMAX;
		if (vitesse1 < -VMAX) vitesse1=-VMAX;

		if (vitesse2 > VMAX) vitesse2=VMAX;
		if (vitesse2 < -VMAX) vitesse2=-VMAX;

		if (vitesse3 > VMAX) vitesse3=VMAX;
		if (vitesse3 < -VMAX) vitesse3=-VMAX;

		if (vitesse4 > VMAX) vitesse4=VMAX;
		if (vitesse4 < -VMAX) vitesse4=-VMAX;

		//PATTE4
		//T1=4200+(v1*VA);//  (-)4230-4235    |4235-4236  |   (+)
		//T2=4200+(v2*VA);//  (-)4240    | 4243 |   4245 (+)
		//T3=4200-(v3*VA);//  (-)4240    | 4243 |   4245(+)
		//T4=4200-(v4*VA);//	(-)4240    |      |4242   4245(+)

		TIM1->CCR1 = 4200+(vitesse1*VA);    // PE9    : q0 -> CAN2_3F
		TIM1->CCR2 = 4200+(vitesse2*VA);    // PE11   : q1 -> CAN2_3E
		TIM1->CCR3 = 4200-(vitesse3*VA);    // PE13   : q2 -> CAN1_3E
		TIM1->CCR4 = 4200-(vitesse4*VA);    // PE14   : q3 -> CAN1_3F
		vTaskDelay(20);
	}

}
