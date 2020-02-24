/*
 * main.c
 *
 *  Created on: 18 octobre 2018
 *      Author: Romain
 */

#include "main.h"

// Timer callback function
void vTaskTimer				(TimerHandle_t xTimer);

// Declare Timer Object
TimerHandle_t	my_timer;
TickType_t ticks;

// Trace User Events Channels
traceString ue1;

// Kernel objects
xTaskHandle 		vTaskCAN1_handle;
xTaskHandle 		vTaskCAN2_handle;

xSemaphoreHandle	xCAN1Sem;
xSemaphoreHandle	xCAN2Sem;
xSemaphoreHandle    xConsoleMutex;
xSemaphoreHandle    xConsoleMutex2;

/*
 * Project Entry Point
 */
int main(void)
{

	// Configure System Clock for 168MHz from 8MHz HSE
	SystemClock_Config();

	// initialisation des registres
	Registre_init();

	// Initialize Debug Console
	BSP_Console_Init();
	my_printf("Console Ready!\r\n");
	my_printf("SYSCLK = %d Hz\r\n", SystemCoreClock);

	// Initialize GPIO
	BSP_GPIO_Init();
	my_printf("GPIO Ready!\r\n");

	// Initialize CAN 1
	CAN1_Init();
	my_printf("CAN1 Ready!\r\n");

	// Initialize CAN 2
	CAN2_Init();
	my_printf("CAN2 Ready!\r\n");

	// Initialize CAN filter
	CAN_ConfigFilter();
	my_printf("CAN filter Ready!\r\n");

	// Initialize LED pin
	BSP_LED_Init();

	// Initialize the user Push-Button
	BSP_PB_Init();

	// Start CAN controler
	CAN_Start();
	my_printf("CAN Controler start!\r\n");

	BSP_CAN2_Init();
	ConfigEncodeur(CAN2);

	// Start Trace Recording
	vTraceEnable(TRC_START);

	// Create Semaphore object (this is not a 'give')
	xCAN1Sem 		 = xSemaphoreCreateBinary();
	xCAN2Sem 		 = xSemaphoreCreateBinary();
	xConsoleMutex    = xSemaphoreCreateMutex();
	xConsoleMutex2   = xSemaphoreCreateMutex();

	// Create Timer object
	my_timer = xTimerCreate("my_timer", 200, pdTRUE, NULL, vTaskTimer); //pdTrue=auto reload each 200 OS ticks

	// Start Trace Recording
	vTraceEnable(TRC_START);

	// Start Timer
	xTimerStart(my_timer, 0);
	ticks = xTimerGetExpiryTime(my_timer);

	// Register the Trace User Event Channels
	ue1 = xTraceRegisterString("ticks");

	// Create Tasks
	xTaskCreate(vTask_CAN1, "vTask_CAN1", 256, NULL, 5, NULL);
	xTaskCreate(vTask_CAN2, "vTask_CAN2", 256, NULL, 2, NULL);
	xTaskCreate(vTask_ASSERV, "vTask_ASSERV", 256, NULL, 1, NULL);


	// Start the Scheduler
	vTaskStartScheduler();
	my_printf("FREE RTOS Start!\r\n");

	// Loop forever
	while(1)
	{
		// The program should never be here...
		// If you get there, there's something wrong...
		my_printf("\r\nERROR: FreeRTOS!\r\n");
		// LED signal
		BSP_LED_Toggle(GREEN);
		delay_ms(50);
		BSP_LED_Toggle(BLUE);
		delay_ms(50);
		BSP_LED_Toggle(RED);
		delay_ms(50);
	}
}

/*
 * Timer Callback
 */
void vTaskTimer (TimerHandle_t xTimer)
{

	my_printf("0)Timer callback\r\n");
	ConfigEncodeur(CAN2);
	BSP_LED_Toggle(GREEN);
}

/*
 * 	Clock configuration for the Nucleo STM32F429ZI board
 * 	HSE input Bypass Mode 				-> 8MHz
 * 	SYSCLK, AHB							-> 168MHz
 * 	APB1								-> 42MHz (periph) 84MHz  (timers)
 * 	APB2								-> 84MHz (periph) 168MHz (timers)
 * 	SDIO, USB							-> 48MHz from PLLQ
 *
 * 	Note : CPU can operate at 180MHz but such setting is not suitable for a 48MHz on USB/SDIO
 */
uint8_t SystemClock_Config()
{
	uint32_t	status;
	uint32_t	timeout;

	// Start HSE in Bypass Mode
	RCC->CR |= RCC_CR_HSEBYP;
	RCC->CR |= RCC_CR_HSEON;

	// Wait until HSE is ready
	timeout = 1000;

	do
	{
		status = RCC->CR & RCC_CR_HSERDY_Msk;
		timeout--;
	} while ((status == 0) && (timeout > 0));

	if (timeout == 0) return (1);	// HSE error


	// Enable the power regulator scale mode 1
	RCC->APB1ENR |= RCC_APB1ENR_PWREN;
	PWR->CR |= 0x03 <<14;

	// Configure the main PLL
	#define PLL_M	8		// 8MHz HSE down-to 1MHz PLL input
	#define PLL_N	336		// 336 MHz VCO output
	#define PLL_P	2		// 168 MHz PLL output
	#define PLL_Q	7		// 48  MHz (USB)

	RCC->PLLCFGR = PLL_M | (PLL_N <<6) | (((PLL_P >> 1) -1) << 16) | (RCC_PLLCFGR_PLLSRC_HSE) | (PLL_Q << 24);

	// Enable the main PLL
	RCC-> CR |= RCC_CR_PLLON;

	// Start Over-Drive power mode
	PWR->CR |= PWR_CR_ODEN;

	// Wait until Over-Drive is started
	timeout = 1000;

	do
	{
		status = PWR->CSR & PWR_CSR_ODRDY_Msk;
		timeout--;
	} while ((status == 0) && (timeout > 0));

	if (timeout == 0) return (2);	// PWR error


	// Switch power to Over-Drive source
	PWR->CR |= PWR_CR_ODSWEN;

	// Wait until power source has been switched
	timeout = 1000;

	do
	{
		status = PWR->CSR & PWR_CSR_ODSWRDY_Msk;
		timeout--;
	} while ((status == 0) && (timeout > 0));

	if (timeout == 0) return (2);	// PWR error


	// Enable FLASH Instruction Cache and Data Cache
	FLASH->ACR |= FLASH_ACR_DCEN | FLASH_ACR_ICEN;

	// Configure Prefetch and wait state
	FLASH->ACR = FLASH_ACR_PRFTEN | FLASH_ACR_LATENCY_4WS;

	// Configure AHB/APB prescalers
	// AHB  Prescaler = /1	-> 168 MHz
	// APB1 Prescaler = /4  -> 42  MHz
	// APB2 Prescaler = /2  -> 84 MHz

	RCC->CFGR |= RCC_CFGR_HPRE_DIV1;
	RCC->CFGR |= RCC_CFGR_PPRE2_DIV2;
	RCC->CFGR |= RCC_CFGR_PPRE1_DIV4;

	// Wait until PLL is ready
	timeout = 1000;

	do
	{
		status = RCC->CR & RCC_CR_PLLRDY_Msk;
		timeout--;
	} while ((status == 0) && (timeout > 0));

	if (timeout == 0) return (3);	// PLL error


	// Select the main PLL as system clock source
	RCC->CFGR &= ~RCC_CFGR_SW;
	RCC->CFGR |= RCC_CFGR_SW_PLL;

	// Wait until PLL becomes main switch input
	timeout = 1000;

	do
	{
		status = (RCC->CFGR & RCC_CFGR_SWS_Msk);
		timeout--;
	} while ((status != RCC_CFGR_SWS_PLL) && (timeout > 0));

	if (timeout == 0) return (4);	// SW error


	// Update System core clock
	SystemCoreClockUpdate();
	return (0);
}
