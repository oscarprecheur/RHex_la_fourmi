/*
 * bsp.c
 *
 *  Created on: 28 mai 2016
 *      Author: laurent
 */


#include "stm32f4xx.h"
#include "bsp.h"

#include "delay.h"

/*
 * LED Functions
 */




// NUCLEO F429ZI
#define LED1 GPIO_ODR_ODR_0
#define LED2 GPIO_ODR_ODR_7
#define LED3 GPIO_ODR_ODR_14


void BSP_LED_Init()
{
	// PB0 and PB1 as LED output

	//RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

	//GPIOB->MODER &= ~(GPIO_MODER_MODER0 | GPIO_MODER_MODER1);
	//GPIOB->MODER   |=  (0x01 <<0U) | (0x01 <<2U) ;
	//GPIOB->OSPEEDR |=  (0x03 <<0U) | (0x01 <<2U) ;
}




void BSP_LED_On(uint8_t n)
{
	switch (n)
	{
		case 1:  //vert
		{
			GPIOB->ODR |= LED1;
			break;
		}

		case 2:  //bleu
		{
			GPIOB->ODR |= LED2;
			break;
		}

		case 3: //rouge
		{
			GPIOB->ODR |= LED3;
			break;
		}
	}
}


void BSP_LED_Off(uint8_t n)
{
	switch (n)
	{
		case 1:
		{
			GPIOB->ODR &= ~LED1;
			break;
		}

		case 2:
		{
			GPIOB->ODR &= ~LED2;
			break;
		}
		case 3:
		{
			GPIOB->ODR &= ~LED3;
			break;
		}
	}
}


void BSP_LED_Toggle(uint8_t n)
{
	switch (n)
	{
		case 1:
		{
			GPIOB->ODR ^= LED1;
			//HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_0);
			break;
		}

		case 2:
		{
			//HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_7);
			GPIOB->ODR ^= LED2;
			break;
		}
		case 3:
		{
			//HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_14);
			GPIOB->ODR ^= LED3;
			break;
		}
	}
}

/*
 *  User Button functions
 */

void BSP_UBTN_Init()
{
	// User Button on PC13 with external Pull-up

	// Enable GPIOC clock
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

	// Configure PC13 as input without pull resistor
	GPIOC->MODER  &= ~(GPIO_MODER_MODER13);
	GPIOC->PUPDR  &= ~(GPIO_PUPDR_PUPDR13);
}


/*
 * Console Functions
 */

void BSP_CONSOLE_TX_Init()
{
	// USART2 TX for console messages
	//
	// USART2_TX -> PA2
	// 115200 bauds


	// Enable GPIOA clock
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

	// Configure PA2 as AF mode
	GPIOA->MODER &= ~(GPIO_MODER_MODER2);
	GPIOA->MODER |= (0x02 <<4U);

	// Connect to USART2 TX (AF7)
	GPIOA->AFR[0] &= ~(0x00000F00);
	GPIOA->AFR[0] |=   0x00000700;

	// Enable USART2 Clock
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

	// Disable USART2 and clears CR1 register
	// Default is 1S|8B|1S, no parity
	USART2->CR1 = 0x00000000;
	USART2->CR2 = 0x00000000;
	USART2->CR3 = 0x00000000;

	// Enable Transmitter mode
	USART2->CR1 |= USART_CR1_TE;

	// Baudrate = 115200

	// @ 42MHz (APB1 -> USART2)
	// OVER8 = 0 -> USARTDIV = 42MHz / (8*2*115200) = 22.78645
	// DIV_Fraction = 16*0.78645 = 12.583 -> 0x0C
	// DIV_Mantissa = 22 = 0x16

	// @ 84MHz (APB2 -> USART1)
	// OVER8 = 0 -> USARTDIV = 84MHz / (8*2*115200) = 45.5729
	// DIV_Fraction = 16*0.5729 = 9.1664 -> 0x09
	// DIV_Mantissa = 45 = 0x2D

	USART2->CR1 &= ~USART_CR1_OVER8;
	USART2->BRR = 0x16 <<4 | 0x0C;

	// Enable USART2
	USART2->CR1 |= USART_CR1_UE;
}

void BSP_RN42_USART_Init()
{
	// USART1 for Bluetooth Module
	//
	// USART1_TX  -> PA9  (AF7)
	// USART1 RX  -> PA10 (AF7)
	// USART1_CTS -> PA11 (AF7)
	// USART2_RTS -> PA12 (AF7)

	// 115200 bauds


	// Enable GPIOA clock
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

	// Configure PA9, PA10, PA11, PA12 as AF mode
	GPIOA->MODER &= ~(GPIO_MODER_MODER9 | GPIO_MODER_MODER10 | GPIO_MODER_MODER11 | GPIO_MODER_MODER12);
	GPIOA->MODER |=  (0x02 <<18U) | (0x02 <<20U) | (0x02 <<22U) | (0x02 <<24U);

	// Connect to USART1 (AF7)
	GPIOA->AFR[1] &= ~(0x000FFFF0);
	GPIOA->AFR[1] |=   0x00077770;

	// Enable USART1 Clock
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

	// Disable USART2 and clears CR1 register
	// Default is 1S|8B|1S, no parity
	USART1->CR1 = 0x00000000;
	USART1->CR2 = 0x00000000;
	USART1->CR3 = 0x00000000;

	// Enable both Transmitter and Receiver modes
	USART1->CR1 |= USART_CR1_TE | USART_CR1_RE;

	// Baudrate = 115200

	// @ 42MHz (APB1 -> USART2)
	// OVER8 = 0 -> USARTDIV = 42MHz / (8*2*115200) = 22.78645
	// DIV_Fraction = 16*0.78645 = 12.583 -> 0x0C
	// DIV_Mantissa = 22 = 0x16

	// @ 84MHz (APB2 -> USART1)
	// OVER8 = 0 -> USARTDIV = 84MHz / (8*2*115200) = 45.5729
	// DIV_Fraction = 16*0.5729 = 9.1664 -> 0x09
	// DIV_Mantissa = 45 = 0x2D

	USART1->CR1 &= ~USART_CR1_OVER8;
	USART1->BRR = 0x02D9;
	//USART1->BRR = 0x222E;

	// Enable USART1
	USART1->CR1 |= USART_CR1_UE;
}

/*
 * SPI2 Common initializations for MPU9250 - ADXL343 - BMA280
 */

void BSP_SPI2_Common_Init()
{
	// SPI_SCK  -> PB13 (AF5)
	// SPI_MISO -> PB14 (AF5)
	// SPI_MOSI -> PB15 (AF5)

	// Enable GPIOB clock
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

	// Configure PB13, PB14, PB15 as AF mode
	GPIOB->MODER &= ~(GPIO_MODER_MODER13 | GPIO_MODER_MODER14 | GPIO_MODER_MODER15);
	GPIOB->MODER |= (0x02 <<26U) |(0x02 <<28U) |(0x02 <<30U);

	// Connect to SPI2 (AF5)
	GPIOB->AFR[1] &= ~(0xFFF00000);
	GPIOB->AFR[1] |=  (0x55500000);

	// Enable SPI2 Clock
	RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;

	// Configure SPI
	// Default config -> Full-duplex, 8-bit, no CRC, MSB first,...
	SPI2->CR1 = 0x0000;
	SPI2->CR2 = 0x0000;

	// Set the baudrate to 84MHz /128
	SPI2->CR1 |= 0x06 <<3;

	// Set as master (SSI must be high)
	SPI2->CR1 |= SPI_CR1_MSTR | SPI_CR1_SSI;

	// Set software management of NSS
	SPI2->CR1 |= SPI_CR1_SSM;

	// Enable SPI2
	SPI2->CR1 |= SPI_CR1_SPE;
}

/*
 * SPI CS Pins for MPU9250 - ADXL343 - BMA280
 */

void BSP_SPI2_CSPins_Init()
{
	// PC3 -> MPU9250
	// PC4 -> BMA280
	// PC5 -> ADXL343

	// Enable GPIOC clock
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

	// Configure the CS pin (PC3)
	GPIOC->MODER  &= ~(GPIO_MODER_MODER3 | GPIO_MODER_MODER4 | GPIO_MODER_MODER5);	// PC3 as output
	GPIOC->MODER  |=  (0x01 <<6U) | (0x01 <<8U) | (0x01 <<10U);
	GPIOC->OTYPER &= ~(GPIO_OTYPER_OT_3 | GPIO_OTYPER_OT_4 | GPIO_OTYPER_OT_5);		// Push-pull
	GPIOC->PUPDR  &= ~(GPIO_PUPDR_PUPDR3 | GPIO_PUPDR_PUPDR4 | GPIO_PUPDR_PUPDR5);	// No Pull resistor
	GPIOC->OSPEEDR |= (0x03 <<6U) | (0x03 <<8U) | (0x03 <<10U);						// High-speed

	// Reset all CS high
	GPIOC->ODR |= GPIO_ODR_ODR_3 | GPIO_ODR_ODR_4 | GPIO_ODR_ODR_5;
}


void BSP_I2C2_Init()
{
	// Pin configuration for I2C2 pins
	// SDA -> PB11
	// SCL -> PB10

	// Enable GPIOB clock
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

	// Enable I2C2 clock
	RCC->APB1ENR |= RCC_APB1ENR_I2C2EN;

	// Configure PB10, PB11 as AF mode
	GPIOB->MODER &= ~(GPIO_MODER_MODER10 | GPIO_MODER_MODER11);
	GPIOB->MODER |= (0x02 << 20) | (0x02 << 22);

	// Connect to I2C2 (AF4)
	GPIOB->AFR[1] &= ~(0x0000FF00);
	GPIOB->AFR[1] |=   0x00004400;

	// Setup Open-Drain
	GPIOB->OTYPER |= GPIO_OTYPER_OT_10 | GPIO_OTYPER_OT_11;

	// Apply I2C software reset
	I2C2->CR1 |= I2C_CR1_SWRST;
	delay_ms(10);
	I2C2->CR1 &= ~I2C_CR1_SWRST;
	delay_ms(10);

	// I2C2 Configuration
	I2C2->CR1 = 0x00000000;
	I2C2->CR2 = 0x00000000;

	// Setup APB1 frequency (42 MHz)
	I2C2->CR2 |= (42 <<0);

	// Setup High/Low level to 5�s (100kHz) -> 210 periods of main clock
	I2C2->CCR |= 0xD2;

	// Enable I2C2
	I2C2->CR1 |= I2C_CR1_PE;
}

