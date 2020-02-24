/*
 * bsp.c
 *
 *  Created on: 5 août 2017
 *      Author: Laurent
 */

#include "bsp.h"

/*
 * BSP_LED_Init()
 * Initialize LED pin (PB0, PB7, PB14) as  High-Speed Push-Pull Outputs
 * Set LED initial state to OFF
 */

void BSP_LED_Init()
{
	// Enable GPIOB clock
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

	// Configure PB0, PB7, PB14 as output
	GPIOB->MODER &= ~(GPIO_MODER_MODER0_Msk | GPIO_MODER_MODER7_Msk | GPIO_MODER_MODER14_Msk);
	GPIOB->MODER |=  (0x01 <<GPIO_MODER_MODER0_Pos) | (0x01 <<GPIO_MODER_MODER7_Pos) | (0x01 <<GPIO_MODER_MODER14_Pos);

	// Configure PB0, PB7, PB14 as Push-Pull output
	GPIOB->OTYPER &= ~(GPIO_OTYPER_OT_0 |GPIO_OTYPER_OT_7 | GPIO_OTYPER_OT_14);

	// Configure PB0, PB7, PB14 as High-Speed Output
	GPIOB->OSPEEDR &= ~(GPIO_OSPEEDR_OSPEED0_Msk | GPIO_OSPEEDR_OSPEED7_Msk | GPIO_OSPEEDR_OSPEED14_Msk);
	GPIOB->OSPEEDR |=  (0x03 <<GPIO_OSPEEDR_OSPEED0_Pos) | (0x03 <<GPIO_OSPEEDR_OSPEED7_Pos) | (0x03 <<GPIO_OSPEEDR_OSPEED14_Pos);

	// Disable PB0, PB7, PB14 Pull-up/Pull-down
	GPIOB->PUPDR &= ~(GPIO_PUPDR_PUPD0_Msk | GPIO_PUPDR_PUPD7_Msk | GPIO_PUPDR_PUPD14_Msk);

	// Set Initial State OFF
	GPIOB->BSRR = GPIO_BSRR_BR_0 | GPIO_BSRR_BR_7 | GPIO_BSRR_BR_14;
}

/*
 * BSP_LED_On()
 * Turn LED On
 */

void BSP_LED_On(uint8_t id)
{
	switch (id)
	{
		case 0:
		{
			GPIOB->BSRR = GPIO_BSRR_BS0;
			break;
		}

		case 1:
		{
			GPIOB->BSRR = GPIO_BSRR_BS7;
			break;
		}

		case 2:
		{
			GPIOB->BSRR = GPIO_BSRR_BS14;
			break;
		}
	}
}

/*
 * BSP_LED_Off()
 * Turn LED Off
 */

void BSP_LED_Off(uint8_t id)
{
	switch (id)
	{
		case 0:
		{
			GPIOB->BSRR = GPIO_BSRR_BR0;
			break;
		}

		case 1:
		{
			GPIOB->BSRR = GPIO_BSRR_BR7;
			break;
		}

		case 2:
		{
			GPIOB->BSRR = GPIO_BSRR_BR14;
			break;
		}
	}
}

/*
 * BSP_LED_Toggle()
 * Toggle LED
 */

void BSP_LED_Toggle(uint8_t id)
{
	switch (id)
	{
		case 0:
		{
			GPIOB->ODR ^= GPIO_ODR_ODR_0;
			break;
		}

		case 1:
		{
			GPIOB->ODR ^= GPIO_ODR_ODR_7;
			break;
		}

		case 2:
		{
			GPIOB->ODR ^= GPIO_ODR_ODR_14;
			break;
		}
	}
}

/*
 * BSP_NVIC_Init()
 * Setup NVIC controller for desired interrupts
 */

void BSP_NVIC_Init()
{
	// Set maximum priority for EXTI line 4 interrupts
	NVIC_SetPriority(EXTI4_IRQn, 0);

	// Enable EXTI line 4 (user button on line 4) interrupts
	NVIC_EnableIRQ(EXTI4_IRQn);
}

/*
 * BSP_PB_Init()
 * Initialize Push-Button pin (PC13) as input without Pull-up/Pull-down
 * Enable EXTI13 on rising edge
 */

void BSP_PB_Init()
{
	// Enable GPIOC clock
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

	// Configure PC13 as input
	GPIOC->MODER &= ~GPIO_MODER_MODER13_Msk;
	GPIOC->MODER |= (0x00 <<GPIO_MODER_MODER13_Pos);

	// Disable PC13 Pull-up/Pull-down
	GPIOC->PUPDR &= ~GPIO_PUPDR_PUPD13_Msk;

	// Enable SYSCFG clock
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

	// Select Port C as interrupt source for EXTI line 13
	SYSCFG->EXTICR[3] &= ~ SYSCFG_EXTICR4_EXTI13_Msk;
	SYSCFG->EXTICR[3] |=   SYSCFG_EXTICR4_EXTI13_PC;

	// Enable EXTI line 13
	EXTI->IMR |= EXTI_IMR_IM13;

	// Disable Rising / Enable Falling trigger
	EXTI->RTSR &= ~EXTI_FTSR_TR13;
	EXTI->FTSR |=  EXTI_RTSR_TR13;
}


/*
 * BSP_PB_GetState()
 * Returns the state of the button (0=released, 1=pressed)
 */

uint8_t	BSP_PB_GetState()
{
	uint8_t state;

	if ((GPIOC->IDR & GPIO_IDR_ID13) == GPIO_IDR_ID13)
	{
		state = 1;
	}
	else
	{
		state = 0;
	}

	return state;
}

/*
 * BSP_Console_Init()
 * USART3 @ 115200 Full Duplex
 * 1 start - 8-bit - 1 stop
 * TX -> PD8 (AF7)
 * RX -> PD9 (AF7)
 */

void BSP_Console_Init()
{
	// Enable GPIOD clock
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;

	// Configure PD8, PD9 as AF mode
	GPIOD->MODER &= ~(GPIO_MODER_MODER8_Msk | GPIO_MODER_MODER9_Msk);
	GPIOD->MODER |=  (0x02 <<GPIO_MODER_MODER8_Pos) | (0x02 <<GPIO_MODER_MODER9_Pos);

	// Connect to USART3 TX (AF7)
	GPIOD->AFR[1] &= ~(0x000000FF);
	GPIOD->AFR[1] |=   0x00000077;

	// Enable USART3 Clock
	RCC->APB1ENR |= RCC_APB1ENR_USART3EN;

	// Disable USART3 and clears CR1 register
	// Default is 1S|8B|1S, no parity
	USART3->CR1 = 0x00000000;
	USART3->CR2 = 0x00000000;
	USART3->CR3 = 0x00000000;

	// Enable Receiver and Transmitter mode
	USART3->CR1 |= USART_CR1_RE | USART_CR1_TE;

	// Baudrate = 115200
	// OVER8 = 0 -> USARTDIV = 42MHz / (8*2*115200) = 22.78645
	// DIV_Fraction = 16*0.78645 = 12.583 -> 0x0C
	// DIV_Mantissa = 22 = 0x16
	USART3->CR1 &= ~USART_CR1_OVER8;
	USART3->BRR = 0x16 <<4 | 0x0C;

	// Enable USART3
	USART3->CR1 |= USART_CR1_UE;
}

/*
 * BSP_GPIO_Init()
 * Configure pins as
 * 	- Analog
 * 	- Input
 * 	- Output
 * 	- Event_OUT
 * 	- EXTI
 *
 *
 *
 * PA4 PA8 PA10 PA11 PA12 PA9
 *
 * PB14 PB7
 *
 * PC13
 *
 * PG6 PG7
 */
void BSP_GPIO_Init()
{

	// Enable GPIOA clock
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

	// Enable GPIOB clock
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

	// Enable GPIOC clock
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

	// Enable GPIOG clock
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN;

	/*****************************
	 * 			PA4
	 *****************************/
	// Configure PA4 as output
	GPIOA->MODER &= ~ GPIO_MODER_MODER4;
	GPIOA->MODER |=  (0x01 <<GPIO_MODER_MODER4_Pos);

	// Configure PA4 as Push-Pull output
	GPIOA->OTYPER &= ~(GPIO_OTYPER_OT_4);

	// Configure PA4 as Low-Speed Output
	GPIOA->OSPEEDR &= ~ GPIO_OSPEEDR_OSPEED4_Msk;
	GPIOA->OSPEEDR |=  (0x00 <<GPIO_OSPEEDR_OSPEED4_Pos);

	// Disable PA4 Pull-up/Pull-down
	GPIOA->PUPDR &= ~ GPIO_PUPDR_PUPD4_Msk;

	// Set Initial State OFF
	GPIOA->BSRR = GPIO_BSRR_BR_4;

	/*****************************
	 * 		PA8,PA10,PA11,PA12
	 *****************************/
	// Configure PA8,PA10,PA11,PA12 as Alternate Function
	GPIOA->MODER &= ~ (GPIO_MODER_MODER8 | GPIO_MODER_MODER10 | GPIO_MODER_MODER11 | GPIO_MODER_MODER12);
	GPIOA->MODER |=  (0x02 <<GPIO_MODER_MODER8_Pos)|(0x02 <<GPIO_MODER_MODER10_Pos)|(0x02 <<GPIO_MODER_MODER11_Pos)|(0x02 <<GPIO_MODER_MODER12_Pos);

	// Configure PA8,PA10,PA11,PA12 as Alternate Function 10 (AF10)
	GPIOA->AFR[1] &= ~(0x000FFF0F);
	GPIOA->AFR[1] |=  (0x000AAA0A);

	// Configure PA8,PA10,PA11,PA12 as Push-Pull output
	GPIOA->OTYPER &= ~(GPIO_OTYPER_OT_8 | GPIO_OTYPER_OT_10 | GPIO_OTYPER_OT_11 | GPIO_OTYPER_OT_12);

	// Configure PA8,PA10,PA11,PA12 as High-Speed Output
	GPIOA->OSPEEDR &= ~ (GPIO_OSPEEDR_OSPEED8_Msk | GPIO_OSPEEDR_OSPEED10_Msk | GPIO_OSPEEDR_OSPEED11_Msk | GPIO_OSPEEDR_OSPEED12_Msk);
	GPIOA->OSPEEDR |=  (0x03 <<GPIO_OSPEEDR_OSPEED8_Pos)|(0x03 <<GPIO_OSPEEDR_OSPEED10_Pos)|(0x03 <<GPIO_OSPEEDR_OSPEED11_Pos)|(0x03 <<GPIO_OSPEEDR_OSPEED12_Pos);

	// Disable PA8,PA10,PA11,PA12 Pull-up/Pull-down
	GPIOA->PUPDR &= ~ (GPIO_PUPDR_PUPD8_Msk | GPIO_PUPDR_PUPD10_Msk | GPIO_PUPDR_PUPD11_Msk | GPIO_PUPDR_PUPD12_Msk );

	// Set Initial State OFF
	GPIOA->BSRR = GPIO_BSRR_BR_8 | GPIO_BSRR_BR_10 | GPIO_BSRR_BR_11 | GPIO_BSRR_BR_12 ;

	/*****************************
	 * 			PA9
	 *****************************/
	// Configure PA9 as Input
	GPIOA->MODER &= ~ GPIO_MODER_MODER9_Msk;
	GPIOA->MODER |=  (0x00 <<GPIO_MODER_MODER9_Pos);

	// Configure PA9 as Push-Pull output
	GPIOA->OTYPER &= ~(GPIO_OTYPER_OT_9);

	// Configure PA9 as Low-Speed Output
	GPIOA->OSPEEDR &= ~ GPIO_OSPEEDR_OSPEED9_Msk;
	GPIOA->OSPEEDR |=  (0x00 <<GPIO_OSPEEDR_OSPEED9_Pos);

	// Disable PA9 Pull-up/Pull-down
	GPIOA->PUPDR &= ~ GPIO_PUPDR_PUPD9_Msk;

	// Set Initial State OFF
	GPIOA->BSRR = GPIO_BSRR_BR_9;

	/*****************************
	* 		PB7 & PB14
	*****************************/
	// Configure PB7, PB14 as output
	GPIOB->MODER &= ~( GPIO_MODER_MODER7_Msk | GPIO_MODER_MODER14_Msk );
	GPIOB->MODER |=  (0x01 <<GPIO_MODER_MODER7_Pos)| (0x01 <<GPIO_MODER_MODER14_Pos);

	// Configure PB7, PB14 as Push-Pull output
	GPIOB->OTYPER &= ~(GPIO_OTYPER_OT_7 | GPIO_OTYPER_OT_14);

	// Configure PB7, PB14 as Low-Speed Output
	GPIOB->OSPEEDR &= ~ (GPIO_OSPEEDR_OSPEED7_Msk | GPIO_OSPEEDR_OSPEED14_Msk);
	GPIOB->OSPEEDR |=  (0x00 <<GPIO_OSPEEDR_OSPEED4_Pos)|(0x00 <<GPIO_OSPEEDR_OSPEED14_Pos);

	// Disable PB7, PB14 Pull-up/Pull-down
	GPIOB->PUPDR &= ~ (GPIO_PUPDR_PUPD7_Msk | GPIO_PUPDR_PUPD14_Msk);

	// Set Initial State OFF
	GPIOB->BSRR = GPIO_BSRR_BR_7 | GPIO_BSRR_BR_14;

	/*****************************
	 * 			PG6
	 *****************************/
	// Configure PG6 as output
	GPIOG->MODER &= ~GPIO_MODER_MODER6_Msk;
	GPIOG->MODER |=  (0x01 <<GPIO_MODER_MODER6_Pos);

	// Configure PG6 as Push-Pull output
	GPIOG->OTYPER &= ~(GPIO_OTYPER_OT_6);

	// Configure PG6 as Low-Speed Output
	GPIOG->OSPEEDR &= ~ GPIO_OSPEEDR_OSPEED6_Msk;
	GPIOG->OSPEEDR |=  (0x00 <<GPIO_OSPEEDR_OSPEED6_Pos);

	// Disable PG6 Pull-up/Pull-down
	GPIOG->PUPDR &= ~ GPIO_PUPDR_PUPD6_Msk;

	// Set Initial State OFF
	GPIOG->BSRR = GPIO_BSRR_BR_6;

	/*****************************
	 * 			PG7
	 *****************************/
	// Configure PG7 as Input
	GPIOG->MODER &= ~GPIO_MODER_MODER7_Msk;
	GPIOG->MODER |=  (0x00 <<GPIO_MODER_MODER7_Pos);

	// Configure PG7 as Push-Pull output
	GPIOG->OTYPER &= ~(GPIO_OTYPER_OT_7);

	// Configure PG7 as Low-Speed Output
	GPIOG->OSPEEDR &= ~ GPIO_OSPEEDR_OSPEED7_Msk;
	GPIOG->OSPEEDR |=  (0x00 <<GPIO_OSPEEDR_OSPEED7_Pos);

	// Disable PG7 Pull-up/Pull-down
	GPIOG->PUPDR &= ~ GPIO_PUPDR_PUPD7_Msk;

	// Set Initial State OFF
	GPIOG->BSRR = GPIO_BSRR_BR_7;

}

/* BSP_PWM_Init()
 * TIM1 Channels 1, 2, 3, 4 is used to control 4 PWM for motor
 * Channel 1 -> PE9		10 KHz OK
 * Channel 2 -> PE11    10 KHz OK
 * Channel 3 -> PE13    10 KHz OK
 * Channel 4 -> PE14    10 KHz OK
 */
void BSP_PWM_Init()
{
	// Enable GPIO
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;

	// Configure PE9, PE11, PE13, PE14 as AF mode
	GPIOE->MODER &= ~(GPIO_MODER_MODER9 | GPIO_MODER_MODER11 |GPIO_MODER_MODER13 |GPIO_MODER_MODER14 );
    GPIOE->MODER |= (0x02 << GPIO_MODER_MODER9_Pos) | (0x02 << GPIO_MODER_MODER11_Pos) | (0x02 << GPIO_MODER_MODER13_Pos) | (0x02<< GPIO_MODER_MODER14_Pos);

	// Connect to TIM1 (AF1)
	GPIOE->AFR[1] &= ~(0x0FF0F0F0);
	GPIOE->AFR[1] |=  (0x01101010);

	// Enable TIM1 clock (APB2 timers = 84MHz)
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;

	// Configure TIM1
	TIM1->CR1 = 0x0000;
	TIM1->SMCR = 0x0000;
	TIM1->DIER = 0x0000;
	TIM1->EGR = 0x0000;

	// Enable Auto-Reload Preload register
	TIM1->CR1 |= TIM_CR1_ARPE;

	// Set prescaler to /1 -> 84MHz counting frequency ( 120 micro s resolution)
	TIM1->PSC = 1;

	// Set Auto-Reload value to 8400 -> PWM frequency is  10 000 Hz
	TIM1->ARR = 8400;

	// Output, PWM mode x
	TIM1->CCMR1= 0x00000000;
	TIM1->CCMR2= 0x00000000;

	TIM1->CCMR1= (0x06 <<4) | TIM_CCMR1_OC1PE | (0x06 <<12) | TIM_CCMR1_OC2PE;
	TIM1->CCMR2= (0x06 <<4) | TIM_CCMR2_OC3PE | (0x06 <<12) | TIM_CCMR2_OC4PE;;

	// Set Default PWM values
	TIM1->CCR1 = 5000;
	TIM1->CCR2 = 5000;
	TIM1->CCR3 = 5000;
	TIM1->CCR4 = 5000;

	// Enable Outputs
	TIM1->CCER |= TIM_CCER_CC1E | TIM_CCER_CC2E | TIM_CCER_CC3E | TIM_CCER_CC4E ;

	// Main output enable
	TIM1->BDTR |= TIM_BDTR_MOE;

	// Set the UG bit
	TIM1->EGR = TIM_EGR_UG;

	// Enable TIM1
	TIM1->CR1 |= TIM_CR1_CEN;
}

/* CAN 1 GPIO Configuration
 *	PB8 --> CAN1_RX
 *	PB9 --> CAN1_TX
 */
void BSP_CAN1_Init()
{
	/* Peripheral clock enable */
	RCC->APB1ENR |= RCC_APB1ENR_CAN1EN;

	// Configure PB8,PB9 as Alternate Function
	GPIOB->MODER &= ~ (GPIO_MODER_MODER8 | GPIO_MODER_MODER9);
	GPIOB->MODER |=  (0x02 <<GPIO_MODER_MODER8_Pos)|(0x02 <<GPIO_MODER_MODER9_Pos);

	// Configure PB8,PB9 as Alternate Function 9 (AF9)
	GPIOB->AFR[1] &= ~(0x000000FF);
	GPIOB->AFR[1] |=  (0x00000099);

	// Configure PB8,PB9 as Push-Pull output
	GPIOB->OTYPER &= ~(GPIO_OTYPER_OT_8 | GPIO_OTYPER_OT_9);

	// Configure PB8,PB9 as High-Speed Output
	GPIOB->OSPEEDR &= ~ (GPIO_OSPEEDR_OSPEED8_Msk | GPIO_OSPEEDR_OSPEED9_Msk);
	GPIOB->OSPEEDR |=  (0x03 <<GPIO_OSPEEDR_OSPEED8_Pos)|(0x03 <<GPIO_OSPEEDR_OSPEED9_Pos);

	// Disable PB8,PB9 Pull-up/Pull-down
	GPIOB->PUPDR &= ~ (GPIO_PUPDR_PUPD8_Msk | GPIO_PUPDR_PUPD9_Msk );

	// Set Initial State OFF
	GPIOB->BSRR = GPIO_BSRR_BR_8 | GPIO_BSRR_BR_9;
}

/* CAN 2 GPIO Configuration
 *	PB12 --> CAN2_RX
 *	PB6 --> CAN2_TX
 */
void BSP_CAN2_Init()
{
	/* Peripheral clock enable */
	RCC->APB1ENR |= RCC_APB1ENR_CAN2EN;

	// Configure PB6,PB12 as Alternate Function
	GPIOB->MODER &= ~ (GPIO_MODER_MODER6 | GPIO_MODER_MODER12);
	GPIOB->MODER |=  (0x02 <<GPIO_MODER_MODER6_Pos)|(0x02 <<GPIO_MODER_MODER12_Pos);

	// Configure PB6,PB12 as Alternate Function 9 (AF9)
	GPIOB->AFR[0] &= ~(0x0F000000);
	GPIOB->AFR[0] |=  (0x09000000);

	GPIOB->AFR[1] &= ~(0x000F0000);
	GPIOB->AFR[1] |=  (0x00090000);

	// Configure PB6,PB12 as Push-Pull output
	GPIOB->OTYPER &= ~(GPIO_OTYPER_OT_6 | GPIO_OTYPER_OT_12);

	// Configure PB6,PB12 as High-Speed Output
	GPIOB->OSPEEDR &= ~ (GPIO_OSPEEDR_OSPEED6_Msk | GPIO_OSPEEDR_OSPEED12_Msk);
	GPIOB->OSPEEDR |=  (0x03 <<GPIO_OSPEEDR_OSPEED6_Pos)|(0x03 <<GPIO_OSPEEDR_OSPEED12_Pos);

	// Disable PB6,PB12 Pull-up/Pull-down
	GPIOB->PUPDR &= ~ (GPIO_PUPDR_PUPD6_Msk | GPIO_PUPDR_PUPD12_Msk );

	// Set Initial State OFF
	GPIOB->BSRR = GPIO_BSRR_BR_6 | GPIO_BSRR_BR_12;
}


