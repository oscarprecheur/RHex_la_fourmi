/*
 * main.h
 *
 *  Created on: 17 octobre 2018
 *      Author: Romain
 */

#ifndef APP_INC_MAIN_H_
#define APP_INC_MAIN_H_

/* Standard includes. */
#include "stdlib.h"
#include "string.h"

/* Device header */
#include "stm32f4xx.h"
//#include "stm32f4xx_hal.h"

/* BSP functions */
#include "bsp.h"

/* DELAY functions */
#include "delay.h"

/* CAN functions */
#include "can.h"

/* Encodeur functions */
#include "encodeur.h"

#include "GlobalParameters.h"
#include "Register.h"

/* FreeRTOS headers */
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"
#include "queue.h"

/* Tasks */
#include "Task_CAN.h"
#include "Task_ASSERV.h"
//#include "Task_UDP.h"

/* SOCKET */
//#include "lwip/sys.h"
//#include "lwip/sockets.h"

/* Global functions */

uint8_t SystemClock_Config(void);
int my_printf	(const char *format, ...);
int my_sprintf	(char *out, const char *format, ...);

#endif /* APP_INC_MAIN_H_ */
