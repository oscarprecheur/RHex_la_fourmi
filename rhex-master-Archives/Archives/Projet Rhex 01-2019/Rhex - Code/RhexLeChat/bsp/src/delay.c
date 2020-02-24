/*
 * delay.c
 *
 *  Created on: 6 août 2017
 *      Author: Laurent
 */

#include "delay.h"

/*
 *  Basic delay functions
 */

void delay_ms(uint32_t delay)
{
	uint32_t	i;
	for(i=0; i<(delay*7000); i++);		// Tuned for ms @ 168MHz
}

void delay_us(uint32_t delay)
{
	uint32_t	i;
	for(i=0; i<(delay*7); i++);			// Tuned for µs
}

