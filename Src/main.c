/****************************************FILE DESCRIPTION**************************************/
/* FILE 		: main.c
* PROJECT 		: HAL Library for STM32F4xx
* PROGRAMMER 	: Brijesh Mehta
* DESCRIPTION 	: main c file
*/
/*********************************************************************************************/

#include <stdint.h>
#include "main.h"

void systemClockConfig(void);
void spi1Init(void);
void gpioConfig(void);
void lcdConfig(void);

SPI_Handle_t spiHandleStruct = {0};
GPIO_Init_t gpioInitStrcut = {0};

int main(void)
{
	systemClockConfig();

	systickInit();

	lcdConfig();

	lcdInit(&spiHandleStruct);

	//Setting the Background
	lcdFill(&spiHandleStruct, BG);

	//Displaying the Time
	lcdWriteString(&spiHandleStruct, "9:30" , (Font_Handler_t*)Arial24x24_t, BLACK, 2, 10, 10);

	//Displaying Network
	lcdWriteArea(&spiHandleStruct, (uint8_t*)full_network, 1152, 179, 202, 10, 33);
	lcdWriteArea(&spiHandleStruct, (uint8_t*)battery_box, 1536, 209, 240, 10, 33);

	//Displaying Battery
	lcdWriteArea(&spiHandleStruct, (uint8_t*)battery_100, 1000, 211, 235, 12, 31);	//Battery less than 100%
	lcdWriteString(&spiHandleStruct, "100%" , (Font_Handler_t*)Arial24x24_t, BLACK, 2, 245, 10);

	//Displaying Enter Number
	lcdWriteString(&spiHandleStruct, "ENTER NUMBER", (Font_Handler_t*)Arial24x24_t, BLACK, 3, 10, 100);

	while(1)
	{

	}
}

void systemClockConfig(void)
{
	/*
	 * System Clock = 168Mhz
	 * AHB Clock Speed = 168Mhz
	 * APB1 Clock Speed = 42Mhz
	 * APB2 Clock Speed = 84Mhz
	 */
	RCC_OscInit_t RCC_OscInitStruct = {0};

	RCC_OscInitStruct.oscillatorType = RCC_OSCILLATOR_TYPE_HSE | RCC_OSCILLATOR_TYPE_PLL;
	RCC_OscInitStruct.hseState = RCC_HSE_ON;
	RCC_OscInitStruct.pll.pllSource = RCC_PLL_SOURCE_HSE;
	RCC_OscInitStruct.pll.pllState = RCC_PLL_ON;
	RCC_OscInitStruct.pll.pllM = 8U;
	RCC_OscInitStruct.pll.pllN = 336U;
	RCC_OscInitStruct.pll.pllP = RCC_PLLP_DIV2;

	if(RCC_OscillatorConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		ErrorHandler();
	}

	RCC_ClkInit_t RCC_ClkInitStruct = {0};

	RCC_ClkInitStruct.clockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.sysClkSource = RCC_SYSCLKSOURCE_PLL;
	RCC_ClkInitStruct.apb1ClkDivider = RCC_CFGR_PPRE1_DIV4;
	RCC_ClkInitStruct.apb2ClkDivider = RCC_CFGR_PPRE2_DIV2;

	if(RCC_ClockConfig(&RCC_ClkInitStruct,FLASH_ACR_LATENCY_5WS) != HAL_OK)
	{
		ErrorHandler();
	}
}


void lcdConfig(void)
{
	/****************Configuring the GPIO Pins as Alternate Function***************/
	RCC_GPIOA_CLOCK_ENABLE();

	GPIO_Init_t gpioInitStruct = {0};

	gpioInitStruct.Mode = GPIO_MODE_ALTFUNC_PUSHPULL;
	gpioInitStruct.Pull = GPIO_NOPULL;
	gpioInitStruct.Alternate = GPIO_AF5;

	//SCK 	---> PA5
	gpioInitStruct.Pin = LCD_SCK_PIN;
	gpioInit(LCD_SCK_PORT,&gpioInitStruct);

	//MISO ---> PA6
	gpioInitStruct.Pin = LCD_MISO_PIN;
	gpioInit(LCD_MISO_PORT,&gpioInitStruct);

	//MOSI ---> PA7
	gpioInitStruct.Pin = LCD_MOSI_PIN;
	gpioInit(LCD_MOSI_PORT,&gpioInitStruct);

	gpioInitStruct.Mode = GPIO_MODE_OUTPUT_PUSHPULL;
	gpioInitStruct.Pull = GPIO_NOPULL;
	gpioInitStruct.Speed = GPIO_SPEED_LOW;
	gpioInitStruct.Alternate = 0;

	//CSX ---> PA4
	gpioInitStruct.Pin = LCD_CSX_PIN;
	gpioInit(LCD_CSX_PORT, &gpioInitStruct);

	//DCX ---> PA2
	gpioInitStruct.Pin = LCD_DCX_PIN;
	gpioInit(LCD_DCX_PORT, &gpioInitStruct);

	//RESX ---> PA3
	gpioInitStruct.Pin = LCD_RESX_PIN;
	gpioInit(LCD_RESX_PORT, &gpioInitStruct);

	/****************Configuring the SPI as Full Duplex Master*************************/
	spiHandleStruct.SPIx = SPI1;
	spiHandleStruct.Init.Mode = SPI_MODE_MASTER;
	spiHandleStruct.Init.Direction = SPI_DIRECTION_2LINE;
	spiHandleStruct.Init.DataSize = SPI_DATA_SIZE_8BIT;
	spiHandleStruct.Init.CLKPolarity = SPI_POLARITY_LOW;
	spiHandleStruct.Init.CLKPhase = SPI_PHASE_1EDGE;
	spiHandleStruct.Init.NSS = SPI_NSS_SOFTWARE;
	spiHandleStruct.Init.BaudRatePrescaler = SPI_BAUDRATE_PRESCALAR_2;
	spiHandleStruct.Init.FirstBit = SPI_MSB_FIRST;

	spiInit(&spiHandleStruct);
}

