/*
 * Register.h
 *
 *  Created on: 23 déc. 2018
 *      Author: romain
 */

#ifndef APP_INC_REGISTER_H_
#define APP_INC_REGISTER_H_

#include "main.h"

typedef struct regs{
	uint8_t v1,v2;
	uint8_t patte,opmode,status;

	float vlimit1,vlimit2,vlimit3,vlimit4;
	int16_t max_pos1,min_pos1;
	int16_t max_pos2,min_pos2;
	int16_t max_pos3,min_pos3;
	int16_t max_pos4,min_pos4;

	int16_t current_pos1;
	int16_t current_pos2;
	int16_t current_pos3;
	int16_t current_pos4;

	float current_x;
	float current_y;
	float current_z;

	int16_t goal_pos1;
	int16_t goal_pos2;
	int16_t goal_pos3;
	int16_t goal_pos4;

	float goal_x;
	float goal_y;
	float goal_z;

	float kp1,kp2,kp3,kp4;
	float ki1,ki2,ki3,ki4;

}regs_t;

// Global variables
regs_t REGS;

/* initialisations des registres*/
void Registre_init(void);

#endif /* APP_INC_REGISTER_H_ */
