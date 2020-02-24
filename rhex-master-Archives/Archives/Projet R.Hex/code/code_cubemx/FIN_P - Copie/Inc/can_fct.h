/*
 * can_fct.h
 *
 *  Created on: 20 déc. 2016
 *      Author: quentin.massone
 */


#ifndef ENCODER_FCT_H_
#define ENCODER_FCT_H_

//#include "stm32f4xx_gpio.h"
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_can.h"
#include "bsp.h"
#include "delay.h"

/* Pin assignment possible for CAN1 and CAN2
 * CAN1 : RX->PA11 	RX->PB8	 RX->PD0  RX->PI9
 * 		  TX->PA12	TX->PB9	 TX->PD1  TX->PH13
 *
 * CAN2 : RX->PB5	RX->PB12
 * 		  TX->PB6	TX->PB13
 */
/* Pin assignment chosen for CAN1 and CAN2
 * CAN1 : RX->PB8
 * 		  TX->PB9
 *
 * CAN2 : RX->PB12
 * 		  TX->PB13
 */

//#define CAN1_GPIO_PORT             GPIOD
//#define CAN1_GPIO_CLK              RCC_AHB1ENR_GPIODEN
//#define CAN1_CLK                   RCC_APB1ENR_CAN1EN
//#define CAN1_RX_PIN                (uint8_t)0x00	// pin 0
//#define CAN1_TX_PIN                (uint8_t)0x01	// pin 1


/* CAN1 : RX=PB8 TX=PB9 */
#define CAN1_GPIO_PORT             GPIOB
#define CAN1_GPIO_CLK              RCC_AHB1ENR_GPIOBEN
#define CAN1_CLK                   RCC_APB1ENR_CAN1EN
#define CAN1_RX_PIN                (uint8_t)0x08	// pin 8
#define CAN1_TX_PIN                (uint8_t)0x09	// pin 9

/* CAN2 : RX=PB12 TX=PB13 */
#define CAN2_GPIO_PORT             GPIOB
#define CAN2_GPIO_CLK              RCC_AHB1ENR_GPIOBEN
#define CAN2_CLK                   RCC_APB1ENR_CAN2EN
#define CAN2_RX_PIN                (uint8_t)0x0C	// pin 12
#define CAN2_TX_PIN                (uint8_t)0x0D	// pin 13

#define APB1_Clock				   ((uint16_t)42000)// the frequency of APB1 clock is 42MHz


typedef enum
{
  BaudRate_10kb   = (uint16_t)10,
  BaudRate_20kb   = (uint16_t)20,
  BaudRate_50kb   = (uint16_t)50,
  BaudRate_100kb  = (uint16_t)100,
  BaudRate_125kb  = (uint16_t)125,
  BaudRate_250kb  = (uint16_t)250,
  BaudRate_500kb  = (uint16_t)500,
  BaudRate_1000kb = (uint16_t)1000
}CAN_BaudRate;


/* fct CAN  */
void CAN_BaudRate_Init(CAN_TypeDef* CANx, CAN_BaudRate BaudRate);

void CAN1_GPIO_Config();
void CAN2_GPIO_Config();

void CAN_Filter_Config(CAN_TypeDef* CANx);

void CAN_Config(CAN_BaudRate BR_CAN1, CAN_BaudRate BR_CAN2);

uint8_t write_msg(CAN_TypeDef* CANx, uint16_t id, uint8_t DLC, uint64_t Data, uint8_t display);
CanRxMsg read_msg(CAN_TypeDef* CANx, uint8_t display);
uint8_t RTR(CAN_TypeDef* CANx, uint32_t id);

void print_msgTX();
void print_msgRX();

#endif /* ENCODER_FCT_H_ */
