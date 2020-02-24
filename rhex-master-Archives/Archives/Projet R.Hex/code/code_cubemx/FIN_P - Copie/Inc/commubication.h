/*
 * commubication.h
 *
 *  Created on: 8 nov. 2017
 *      Author: ludovic.hembert
 */

#ifndef APP_INC_COMMUBICATION_H_
#define APP_INC_COMMUBICATION_H_
#include "encoder_fct.h"
#include "commubication.h"


void message_receive();
void message_send();
void read_position(); //section critique
void read_angles(); //section critique
void watchdog();
void command_position(int x, int y, int z);
void command_angles(float a0, float a1, float a2, float a3);


#endif /* APP_INC_COMMUBICATION_H_ */
