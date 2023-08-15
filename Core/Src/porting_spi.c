#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include "stm32f4xx_hal.h"
#include "porting_spi.h"
#include "main.h"


void delay_ms(uint32_t period, void *any_ptr)
{
	HAL_Delay(period);
}

uint8_t tx_rx(const void *spi_h, uint8_t *tx_buf, uint8_t *rx_buf,
	    uint32_t transfer_size, uint32_t timeout)
{
	HAL_GPIO_TogglePin (GPIOC, GPIO_PIN_13);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET); // NSS low
	HAL_Delay (1);
	if(HAL_SPI_TransmitReceive((SPI_HandleTypeDef *) spi_h, tx_buf, rx_buf,
				transfer_size, timeout) != HAL_OK) {
		return 1;
	}
	while(((SPI_HandleTypeDef *) spi_h)->State == HAL_SPI_STATE_BUSY);  // wait for xmission complete
	HAL_Delay (1);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET); // NSS high

	return 0;
}

