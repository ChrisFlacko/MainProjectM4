/*
 * hal_uart.h
 *
 *  Created on: Jun 10, 2025
 *      Author: chris
 */

#ifndef HAL_UART_H_
#define HAL_UART_H_

#include <memorymap.h>
#include "typedefs.h"
#include "peripherals.h"
#include "hal_gpio.h"

void Hal_USART3_vInit(void);

void Hal_USART3_vWriteFunction(int ch);

void Hal_USART2_vEnableSystemInterrupt(void);

void Hal_USART3_WaitForTxReady(void);

#endif /* HAL_UART_H_ */
