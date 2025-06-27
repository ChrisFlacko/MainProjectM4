/*
 * hal_uart.h
 *
 *  Created on: Jun 10, 2025
 *      Author: chris
 */

#ifndef HAL_UART_H_
#define HAL_UART_H_

#include "hal_memorymap.h"
#include "hal_gpio.h"



typedef struct
{
	__IO uint32_t CR1;
	__IO uint32_t CR2;
	__IO uint32_t CR3;
	__IO uint32_t BRR;
	__IO uint32_t GTPR;
	__IO uint32_t RTOR;
	__IO uint32_t RQR;
	__IO uint32_t ISR;
	__IO uint32_t ICR;
	__IO uint32_t RDR;
	__IO uint32_t TDR;

}TypeDef_USART2;



#define USART2	((TypeDef_USART2*) USART2_BASE_ADDR)

#define USART3	((TypeDef_USART2*) USART3_BASE_ADDR)

void Hal_USART3_vInit(void);

void Hal_USART3_vWriteFunction(int ch);

void Hal_USART2_vEnableSystemInterrupt(void);

#endif /* HAL_UART_H_ */
