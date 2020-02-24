/*
 * Sampler.c
 */
// Set Timer3 interrupt for sampling the feedback

#include "Sampler.h"

void TIM3_Init(uint16_t dt)
{
	// La precisition est a verifier !!!


	// Enable TIM3 clock (APB1 timers = 48MHz)
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;

	// Configure TIM3 : upcounting mode, update event enabled
	TIM3->CR1 =  0x0004;

	// Set prescaler to /42000 -> 1ms counting period
	TIM3->PSC = 48000 - 1;

	// Set Auto-Reload value to dt
	TIM3->ARR = 2*dt; //  this isn't correct but it will do for our purpose

	TIM3->EGR = TIM_EGR_UG;

	// Enable the TIM3 global Interrupt
	NVIC_SetPriority(TIM3_IRQn, 0);
	NVIC_EnableIRQ(TIM3_IRQn);

	/* Enable interrupt timer */
	// bit 0x0001 : UIE from register DIER (UIE = Update interrupt enable)
	TIM3->DIER = 0x0001;

	// Enable TIM3
	TIM3->CR1 |= TIM_CR1_CEN;

}

