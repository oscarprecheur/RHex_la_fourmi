/*
 * bsp.c
 *
 *  Created on: 28 mai 2016
 *      Author: laurent
 */


#include "stm32f429xx.h"
#include "bsp.h"


/*
 * LED Functions
 */

void BSP_LED_Init()
{
	// Configure PB0, PB7, PB14 as outputs
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

	GPIOB->MODER &= ~(GPIO_MODER_MODER0|GPIO_MODER_MODER7|GPIO_MODER_MODER14);
	GPIOB->MODER   |= 0x01 | (0x01<<14) | (0x01<<28);
	GPIOB->OSPEEDR |= 0x03 | (0x03<<14) | (0x03<<28);
}

/* Push Button function  */
void BSP_PB_Init()
{
	// Configure PC13 as input
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

	GPIOC->MODER &= ~(GPIO_MODER_MODER13);
	GPIOC->MODER   |= (0x00<<26); // mode in
	GPIOC->OSPEEDR |= (0x03<<26); // very hight speed
	GPIOC->PUPDR = 0x00; // No pull-up, pull-down


	//enable SYSCFG clock
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

	//connect exticr4 to PC13
	SYSCFG->EXTICR[3] = SYSCFG_EXTICR4_EXTI13_PC;

	// Enable rising trigger
	EXTI->FTSR &= ~(EXTI_FTSR_TR13);
	EXTI->RTSR |= (EXTI_RTSR_TR13);

	//Activate EXTI0
	EXTI->IMR |= EXTI_IMR_MR13;

	NVIC_SetPriority(EXTI15_10_IRQn, 1);
	NVIC_EnableIRQ(EXTI15_10_IRQn);
}

void BSP_ADC_Init()
{
	// 4 channels ADC + DMA setup
	//
	// ADC1 Channel 4  -> PA4
	// ADC1 Channel 5  -> PA5
	// ADC1 Channel 6  -> PA6
	// ADC1 Channel 7  -> PA7
	//
	// DMA2: Stream 0, Channel 0

	/* Configure PA4, PA5, PA6 and PA7 as analog input*/
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

	GPIOA->MODER &= ~(GPIO_MODER_MODER4|GPIO_MODER_MODER5|GPIO_MODER_MODER6|GPIO_MODER_MODER7);
	GPIOA->MODER |= (0x03<<8) | (0x03<<10) | (0x03<<12) | (0x03<<14);

	// Disable any pull resistor
	GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPDR4|GPIO_PUPDR_PUPDR5|GPIO_PUPDR_PUPDR6|GPIO_PUPDR_PUPDR7);


	// Enable DMA2 clock
	RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN;

	// ADC1 is on DMA 2, Stream 0, Channel 0
	DMA2_Stream0->CR = 0x00000000;

	// Select Channel 0
	DMA2_Stream0->CR |= 0x00 << 25;

	// Set priority level to 'high'
	DMA2_Stream0->CR |= 0x02 << 16;

	// Memory data size is 16 bit
	DMA2_Stream0->CR |= 0x01 << 13; // half-word (16-bit)

	// Peripheral data size is 16 bit
	DMA2_Stream0->CR |= 0x01 << 11; // half-word (16-bit)

	// Memory increment mode enabled
	DMA2_Stream0->CR |= DMA_SxCR_MINC;

	// Peripheral increment mode disabled
	DMA2_Stream0->CR &= ~DMA_SxCR_PINC;

	// Circular mode enabled
	DMA2_Stream0->CR |= DMA_SxCR_CIRC;

	// Peripheral to memory direction
	DMA2_Stream0->CR |= 0x00 << 6; // Peripheral-to-memory

	// Number of data items to transfer
	DMA2_Stream0->NDTR = (uint32_t)4;

	// Peripheral address
	DMA2_Stream0->PAR =  (uint32_t) &ADC1->DR;

	// Memory address
	DMA2_Stream0->M0AR = (uint32_t) &adc_buffer[0];


	// Enable ADC1 clock
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;

	// ADC common configuration
	ADC->CCR = 0x00000000;

	// Select PCLK2/8
	ADC->CCR |= 0x03 <<16;

	// ADC1 configuration
	ADC1->CR1 = 0x00000000;
	ADC1->CR2 = 0x00000000;

	// Resolution is 12 bits
	ADC1->CR1 &= ~(ADC_CR1_RES);

	// Scan mode
	ADC1->CR1 |= ADC_CR1_SCAN;

	// Continuous mode
	ADC1->CR2 |= ADC_CR2_CONT;

	// Data align right
	ADC1->CR2 &= ~(ADC_CR2_ALIGN);

	// Sequence length is 4 conversions
	ADC1->SQR1 = (4 - 1) <<20;

	// Channels for conversions 7 to 12
	ADC1->SQR2 = 0x00000000;

	// Channels for conversions 1 to 6
	// 4 conversions : order : channel 4, 5, 6, 7
	ADC1->SQR3 = (0x04 <<0) | (0x05 <<5) | (0x06 <<10) | (0x07 <<15)  | (0x00 <<20)  | (0x00 <<25) ;

	// Specify sampling time -> 144 cycles (for channels 10 -> 18
	ADC1->SMPR1 = (0b110 <<0) | (0b110 <<3) | (0b110 <<6) | (0b110 <<9) | (0b110 <<12) | (0b110 <<15) | (0b110 <<18) | (0b110 <<21) | (0b110 <<24);

	// Specify sampling time -> 144 cycles (for channels 0 -> 9
	ADC1->SMPR2 = (0b110 <<0) | (0b110 <<3) | (0b110 <<6) | (0b110 <<9) | (0b110 <<12) | (0b110 <<15) | (0b110 <<18) | (0b110 <<21) | (0b110 <<24) | (0b110 <<27);


	// Keep sending DMA requests after completing 6 conversions
	ADC1->CR2 |= ADC_CR2_DDS;

	// Enable DMA2 Stream 0
	DMA2_Stream0->CR |= DMA_SxCR_EN;

	// Enable ADC1 DMA requests
	ADC1->CR2 |= ADC_CR2_DMA;

	// Enable ADC1
	ADC1->CR2 |= ADC_CR2_ADON;

	// Start conversion
	ADC1->CR2 |= ADC_CR2_SWSTART;
}

//******* LED *******
void BSP_LED_On(uint8_t n)
{
	switch (n)
	{
		case 0:
		{
			GPIOB->ODR |= GPIO_ODR_ODR_0;
			break;
		}

		case 1:
		{
			GPIOB->ODR |= GPIO_ODR_ODR_7;
			break;
		}

		case 2:
		{
			GPIOB->ODR |= GPIO_ODR_ODR_14;
			break;
		}
	}
}

void BSP_LED_Off(uint8_t n)
{
	switch (n)
	{
		case 0:
		{
			GPIOB->ODR &= ~GPIO_ODR_ODR_0;
			break;
		}

		case 1:
		{
			GPIOB->ODR &= ~GPIO_ODR_ODR_7;
			break;
		}

		case 2:
		{
			GPIOB->ODR &= ~GPIO_ODR_ODR_14;
			break;
		}
	}
}

void BSP_LED_Toggle(uint8_t n)
{
	switch (n)
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
 * Console Functions
 */

void BSP_CONSOLE_TX_Init()
{
	// USART3 TX for console messages
	//
	// USART3_TX -> PD8
	// 115200 bauds


	// Enable GPIOD clock
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;

	// Configure PD8 as AF mode
	GPIOD->MODER &= ~(GPIO_MODER_MODER8);
	GPIOD->MODER |= (0x02 << 16);

	// Connect to USART3 TX (AF7)
	GPIOD->AFR[1] &= ~(0x0000000F);
	GPIOD->AFR[1] |= 0x00000007;

	// Enable USART3 Clock
	RCC->APB1ENR |= RCC_APB1ENR_USART3EN;

	// Disable USART3 and clears CR1 register
	// Default is 1S|8B|1S, no parity
	USART3->CR1 = 0x00000000;
	USART3->CR2 = 0x00000000;
	USART3->CR3 = 0x00000000;

	// Enable Transmitter mode
	USART3->CR1 |= USART_CR1_TE;

	// Baudrate = 115200
	// OVER8 = 0 -> USARTDIV = 42MHz / (8*2*115200) = 22.78645
	// DIV_Fraction = 16*0.78645 = 12.583 -> 0x0C
	// DIV_Mantissa = 22 = 0x16
	USART3->CR1 &= ~USART_CR1_OVER8;
	USART3->BRR = 0x16 <<4 | 0x0C;

	// Enable USART3
	USART3->CR1 |= USART_CR1_UE;
}

void BSP_USART_PC_Init(){

	// USART3 matlab_com
	// USART3_TX -> PD8
	// USART3_RX -> PD9

	// Enable GPIOD clock
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;

	// Configure PD8, PD9 as AF mode
	GPIOD->MODER &= ~(GPIO_MODER_MODER8 | GPIO_MODER_MODER9);
	GPIOD->MODER |= (0x02 << 16) | (0x02 << 18);

	// Connect to USART3 (AF7)
	GPIOD->AFR[1] &= ~(0x000000FF);
	GPIOD->AFR[1] |=   0x00000077;

	// Enable USART3 Clock
	RCC->APB1ENR |= RCC_APB1ENR_USART3EN;

	// Disable USART3 and clears CR1 register
	// Default is 1S|8B|1S, no parity
	USART3->CR1 = 0x00000000;
	USART3->CR2 = 0x00000000;
	USART3->CR3 = 0x00000000;

	// Enable both Tx and Rx modes
	USART3->CR1 |= USART_CR1_TE | USART_CR1_RE;

	// Baudrate = 115200
	// OVER8 = 0 -> USARTDIV = 42MHz / (8*2*115200) = 22.78645
	// DIV_Fraction = 16*0.78645 = 12.583 -> 0x0C
	// DIV_Mantissa = 22 = 0x16
	USART3->CR1 &= ~USART_CR1_OVER8;
	USART3->BRR = 0x16 <<4 | 0x0C;

	// Enable DMA1 clock
	RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN;

	// UART3_RX is on DMA1, Stream 1, Channel 4
	DMA1_Stream1->CR = 0x00000000;

	// Select Channel 4
	DMA1_Stream1->CR |= 0x04 << 25;

	// Set priority level to 'high'
	DMA1_Stream1->CR |= 0x02 << 16;

	// Memory data size is 8 bit
	DMA1_Stream1->CR |= 0x00 << 13;

	// Peripheral data size is 8 bit
	DMA1_Stream1->CR |= 0x00 << 11;

	// Memory increment mode enabled
	DMA1_Stream1->CR |= DMA_SxCR_MINC;

	// Peripheral increment mode disabled
	DMA1_Stream1->CR &= ~DMA_SxCR_PINC;

	// Circular mode enabled
	DMA1_Stream1->CR |= DMA_SxCR_CIRC;

	// Peripheral to memory direction
	DMA1_Stream1->CR |= 0x00 << 6;

	// Number of data items to transfer
	DMA1_Stream1->NDTR = (uint32_t)Matlab_RX_BUFFER_SIZE;

	// Peripheral address
	DMA1_Stream1->PAR =  (uint32_t) &USART3->DR;

	// Memory address
	DMA1_Stream1->M0AR = (uint32_t) &matlab_rx_buffer[0];

	// Enable both HT and TC interrupts
	DMA1_Stream1->CR |= DMA_SxCR_HTIE | DMA_SxCR_TCIE;

	// Enable DMA1 Stream 2
	DMA1_Stream1->CR |= DMA_SxCR_EN;

	// Enable UART3 RX DMA Requests
	USART3->CR3 |= USART_CR3_DMAR;

	// Enable USART3
	USART3->CR1 |= USART_CR1_UE;

}



