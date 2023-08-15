/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "main.h"
#include "stm32f4xx_hal_uart.h"
//#include "porting_spi.h"
#include "ps2_dualshock_spi.h"



SPI_HandleTypeDef spi_h;
ps2_dualshock_dev ps2_dev;

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);


/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* Configure the system clock */
	SystemClock_Config();




	GPIO_InitTypeDef GPIO_InitStruct = {0};


	/*##-1- Enable peripherals and GPIO Clocks #################################*/
	/* Enable GPIO TX/RX clock */
	__HAL_RCC_USART1_CLK_ENABLE();	// enable usart1 clock
	__HAL_RCC_GPIOA_CLK_ENABLE();		// enable gpioa clock (for PA9 and PA10,
	// which are usart1 rx and tx

	/*##-2- Configure peripheral GPIO ##########################################*/
	/* UART TX GPIO pin configuration  */
	GPIO_InitStruct.Pin       = GPIO_PIN_9;
	GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull      = GPIO_PULLUP;
	GPIO_InitStruct.Speed     = GPIO_SPEED_FAST;
	GPIO_InitStruct.Alternate = GPIO_AF7_USART1;

	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/* UART RX GPIO pin configuration  */
	GPIO_InitStruct.Pin = GPIO_PIN_10;
	GPIO_InitStruct.Alternate = GPIO_AF7_USART1;

	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);


	UART_HandleTypeDef uart_h = {0};
	uart_h.Instance          = USART1;

	uart_h.Init.BaudRate     = 9600;
	uart_h.Init.WordLength   = UART_WORDLENGTH_8B;
	uart_h.Init.StopBits     = UART_STOPBITS_1;
	uart_h.Init.Parity       = UART_PARITY_NONE;
	uart_h.Init.HwFlowCtl    = UART_HWCONTROL_NONE;
	uart_h.Init.Mode         = UART_MODE_TX_RX;
	uart_h.Init.OverSampling = UART_OVERSAMPLING_16;

	if(HAL_UART_Init(&uart_h) != HAL_OK)
	{
		/* Initialization Error */
		Error_Handler();
	}

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOC_CLK_ENABLE();
	//__HAL_RCC_GPIOD_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);

	/*Configure GPIO pin : PC13 */
	GPIO_InitStruct.Pin = GPIO_PIN_13;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	/* Configure SPI */
	//spi_h = {0};
	spi_h.Instance = SPI1;
	spi_h.Init.Mode = SPI_MODE_MASTER;
	spi_h.Init.Direction = SPI_DIRECTION_2LINES;
	spi_h.Init.DataSize = SPI_DATASIZE_8BIT;
	spi_h.Init.CLKPolarity = SPI_POLARITY_HIGH;
	spi_h.Init.CLKPhase = SPI_PHASE_2EDGE;
	spi_h.Init.NSS = SPI_NSS_SOFT;
	spi_h.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64; //256?128?
	spi_h.Init.FirstBit = SPI_FIRSTBIT_LSB;
	spi_h.Init.TIMode = SPI_TIMODE_DISABLE;
	spi_h.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	spi_h.Init.CRCPolynomial = 10;
	if (HAL_SPI_Init(&spi_h) != HAL_OK)
	{
		Error_Handler();
	}

	//HAL_SPI_MspInit(&spi_h);
	ps2_init(&ps2_dev, &spi_h);


	char idle[20] = "Idle \r\n~";
	char up[20] = "Up \r\n~";
	char down[20] = "Down \r\n~";
	char left[20] = "Left \r\n~";
	char right[20] = "Right \r\n~";
	char cross[20] = "cross \r\n~";
	char circle[20] = "circle \r\n~";
	char square[20] = "square \r\n~";
	char triangle[20] = "triangle \r\n~";
	char start[20] = "start \r\n~";
	char select[20] = "select \r\n~";
	char l_trigger[20] = "l_trigger \r\n~";
	char r_trigger[20] = "r_trigger \r\n~";
	char l_shift[20] = "l_shift \r\n~";
	char r_shift[20] = "r_shift \r\n~";
	char l_stick_press[20] = "l_stick_press \r\n~";
	char r_stick_press[20] = "r_stick_press \r\n~";


	while (1)
	{

		char *current_p = idle;

		if(ps2_main_exchange(&ps2_dev) != 0)
			continue;

		if(ps2_dev.state->is_idle == 1)
			continue;


		if (ps2_dev.state->up)
			current_p = up;
		else if (ps2_dev.state->down)
			current_p = down;
		else if (ps2_dev.state->left)
			current_p = left;
		else if (ps2_dev.state->right)
			current_p = right;
		else if (ps2_dev.state->cross)
			current_p = cross;
		else if (ps2_dev.state->circle)
			current_p = circle;
		else if (ps2_dev.state->square)
			current_p = square;
		else if (ps2_dev.state->triangle)
			current_p = triangle;
		else if (ps2_dev.state->start)
			current_p = start;
		else if (ps2_dev.state->select)
			current_p = select;
		else if (ps2_dev.state->l_trigger)
			current_p = l_trigger;
		else if (ps2_dev.state->r_trigger)
			current_p = r_trigger;
		else if (ps2_dev.state->l_shift)
			current_p = l_shift;
		else if (ps2_dev.state->r_shift)
			current_p = r_shift;
		else if (ps2_dev.state->l_stick_press)
			current_p = l_stick_press;
		else if (ps2_dev.state->r_stick_press)
			current_p = r_stick_press;

		if(current_p != idle) {
			while(*current_p != '~'){
				putchar_uart((uint8_t *)current_p, &uart_h);
				current_p++;
			}
			HAL_Delay(20);
		}
		//HAL_Delay (10);   /* Insert delay 5000 ms */
	}
}

void getchar_uart(uint8_t *char_bits, UART_HandleTypeDef *uart_h) {
	//	uint32_t tickstart = HAL_GetTick();
	//	while (UART_WaitOnFlagUntilTimeout(uart_h, UART_FLAG_RXNE, RESET,
	//					   tickstart, 0xFFFF) != HAL_OK);

	while(__HAL_UART_GET_FLAG(uart_h, UART_FLAG_RXNE) == 0);
	*char_bits = (uint8_t)(uart_h->Instance->DR & (uint8_t)0x00FF);
}

void putchar_uart(uint8_t *char_bits, UART_HandleTypeDef *uart_h) {
	//	uint32_t tickstart = HAL_GetTick();
	//	while (UART_WaitOnFlagUntilTimeout(uart_h, UART_FLAG_TXE, RESET,
	//					   tickstart, 0xFFFF) != HAL_OK);

	while(__HAL_UART_GET_FLAG(uart_h, UART_FLAG_TXE) == 0);
	uart_h->Instance->DR = (uint8_t)(*char_bits & 0xFFU);
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void)
{
	RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

	/** Configure the main internal regulator output voltage
	 */
	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
		|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
	{
		Error_Handler();
	}
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1)
	{
	}
	/* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
	/* USER CODE BEGIN 6 */
	/* User can add his own implementation to report the file name and line number,
ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

	while(1);

	/* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
