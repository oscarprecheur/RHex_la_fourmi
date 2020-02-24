
#ifndef DELAY_H_
#define DELAY_H_

#include "stm32f429xx.h"


// config timer2
#define clock_TIM3 168000000
#define period_TIM3 10000
#define pas_us_TIM3 clock_TIM3/1000000
#define pas_ms_TIM3 clock_TIM3/1000
#define pas_s_TIM3 clock_TIM3


// Header for delay.c functions
void SysTick_Init(void);
void delay_ms(uint32_t ms);


#endif
