/*
 * commubication.c
 *
 *  Created on: 8 nov. 2017
 *      Author: ludovic.hembert
 */
//#include "encoder_fct.h"
#include "commubication.h"
#include "encoder_fct.h"
#include "math.h"
#include "freertos.h"
#include "task.h"


/*

int tab_pos[3];

void message_receive()
{

}

void message_send()
{

}
void read_position() //section critique
{
	//fonction
	read_angles();
	//utiliser le MGD
	//Stocker MGD dans tab_pos;

}*/
void read_angles_task(float q3, float q2, float q1, float q0){//section critique

	get_2Angles(CAN1, TPDO1, &q3, &q2); // get angle 3F & 3E from CAN1
	get_2Angles(CAN2, TPDO1, &q0, &q1); // get angle 3F & 3E from CAN2

	int q0_int=floor(q0);
	int q0_dec=(int)((q0-q0_int)*1000);
	int q1_int=floor(q1);
	int q1_dec=(int)((q1-q1_int)*1000);
	int q3_int=floor(q3);
	int q3_dec=(int)((q3-q3_int)*1000);
	int q2_int=floor(q2);
	int q2_dec=(int)((q2-q2_int)*1000);
	//qs = q2;
	my_printf("\n\r c1 q0 : ");
	my_printf("%d,%d",q0_int,q0_dec);
	my_printf("\n\r c1 q1 : ");
	my_printf("%d,%d",q1_int,q1_dec);
	my_printf("\n\r c2 q2 : ");
	my_printf("%d,%d",q3_int,q3_dec);
	my_printf("\n\r c2 q3 :");
	my_printf("%d,%d",q2_int,q2_dec);
	my_printf("\n\rfin fin\n");
	vTaskDelay(2000);

}/*
void watchdog()
{
	//freertOS
}
void command_position(int x, int y, int z)
{
	//MGI stocker dans a0,a1,a2,a3

	int a0, a1, a2, a3;

	set_motor(1, &(TIM1->CCR1), q0, a0);
	set_motor(2, &(TIM1->CCR2), q1, a1);
	set_motor(3, &(TIM1->CCR3), q2, a2);
	set_motor(4, &(TIM1->CCR4), q3, a3);


}
void command_angles(float a0, float a1, float a2, float a3)
{
	set_motor(1, &(TIM1->CCR1), q0, a0);
	set_motor(2, &(TIM1->CCR2), q1, a1);
	set_motor(3, &(TIM1->CCR3), q2, a2);
	set_motor(4, &(TIM1->CCR4), q3, a3);
}
*/
