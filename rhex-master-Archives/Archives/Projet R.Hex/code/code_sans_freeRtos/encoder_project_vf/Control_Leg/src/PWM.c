/*
 * PWM.c
 *
 *  Created on: 16 mars 2017
 *      Author: Maxime
 */
#include "../../Control_Leg/inc/PWM.h"

// TIM1, Channel 1,2,3,4 PWM mode
// Channel 1 --> PE9
// Channel 2 --> PE11
// Channel 3 --> PE13
// Channel 4 --> PE14


void Motor1234_PWM_Init()
{
	// Enable GPIOA clock
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;

	// Configure PE9, PE11, PE13 & PE14 as AF mode
	GPIOE->MODER &= ~(GPIO_MODER_MODER9 | GPIO_MODER_MODER11 | GPIO_MODER_MODER13 | GPIO_MODER_MODER14 );
	GPIOE->MODER |= (0x02 << 18) | (0x02 << 22) | (0x02 << 26) | (0x02 << 28) ;

	// Connect to TIM1 (AF1)
	GPIOE->AFR[1] &= ~(0x0FF0F0F0);
	GPIOE->AFR[1] |=  (0x01101010);

	// Enable TIM1 clock (APB2 timers = 168MHz)
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;

	// Configure TIM1
	TIM1->CR1 =  0x0000;
	TIM1->SMCR = 0x0000;
	TIM1->DIER = 0x0000;
	TIM1->EGR  = 0x0000;

	// Enable Auto-Reload Preload register
	TIM1->CR1 |= TIM_CR1_ARPE;

	// Set prescaler to /4 -> 42MHz counting frequency
	// Set prescaler to /3 -> 56MHz counting frequency
	TIM1->PSC = 3000 - 1;

	// Set Auto-Reload value to period_PWM
	TIM1->ARR = period_PWM - 1;


	// Output, PWM mode 1
	TIM1->CCMR1 = 0x00000000;
	TIM1->CCMR2 = 0x00000000;

	TIM1->CCMR1 = (0x06 <<4)  | TIM_CCMR1_OC1PE | (0x06 <<12) | TIM_CCMR1_OC2PE;
	TIM1->CCMR2 = (0x06 <<4)  | TIM_CCMR2_OC3PE | (0x06 <<12) | TIM_CCMR2_OC4PE;

	// Set default PWM values
	TIM1->CCR1 = 0; // PE9
	TIM1->CCR2 = 0; // PE11
	TIM1->CCR3 = 0; // PE13
	TIM1->CCR4 = 0; // PE14

	// Enable Outputs
	TIM1->CCER |= TIM_CCER_CC1E | TIM_CCER_CC2E | TIM_CCER_CC3E | TIM_CCER_CC4E;

	// Main output enable
	TIM1->BDTR |= TIM_BDTR_MOE;

	// Set the UG bit
	TIM1->EGR |= TIM_EGR_UG;

	// Enable TIM1
	TIM1->CR1 |= TIM_CR1_CEN;
}

