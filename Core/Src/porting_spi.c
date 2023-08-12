#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include "stm32f4xx_hal.h"
#include "porting_spi.h"
#include "main.h"


void delay_ms(uint32_t period, void *spi_h)
{
	HAL_Delay(period);
}


int8_t tx_rx(void *ps2_dualshock_h, uint8_t *tx_buf, uint8_t *rx_buf,
	    uint32_t transfer_size, const void *spi_h)
{
    return 0;
}

