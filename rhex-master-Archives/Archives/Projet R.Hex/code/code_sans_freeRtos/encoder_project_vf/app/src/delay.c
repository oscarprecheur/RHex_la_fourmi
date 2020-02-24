
#include "delay.h"

static volatile uint32_t 	timer=0;
extern uint32_t				SystemCoreClock;



// Systick Initialization

void SysTick_Init()
{
	SystemCoreClockUpdate();
	while (SysTick_Config(SystemCoreClock/1000) != 0);	// 1ms resolution
}

// Systick Interrupt Handler

void SysTick_Handler(void)
{
	if (timer !=0)
	{
		timer--;
	}
}

// Basic delay function

void delay_ms(uint32_t ms)
{
	timer = ms;
	while(timer != 0);
}



