/*
 * functions.c
 *
 *  Created on: Jul 7, 2025
 *      Author: chris
 */

#include <../Inc/peripherals.h>
#include <../Inc/typedefs.h>
#include <../Inc/memorymap.h>

#include "functions.h"

#include "../Inc/hal_adc.h"
#include "../Inc/hal_i2c.h"
#include "../Inc/hal_uart.h"


void SendADCtoSlaveUSART(void)
{
	/* 1) Read out ADC data */
	uint16_t adcData = Hal_ADC_u16ReadChannel();

	/* 2) Check, that data is valid */
	if (adcData != 0)
	{
		/* 3) Start USART */
		Hal_USART3_vWriteFunction((uint8_t)(adcData >> 8));	// Send the upper bits first
		Hal_USART3_WaitForTxReady();
		Hal_USART3_vWriteFunction((uint8_t)(adcData));	// Send the lower bits last

		/* 4) Display the number on the OLED */
		SSD1306_vSendData((uint8_t)(adcData >> 8));
		SSD1306_vSendData((uint8_t)adcData);
	}
}

