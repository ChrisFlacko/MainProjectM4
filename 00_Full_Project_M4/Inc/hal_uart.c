/*
 * hal_uart.c
 *
 *  Created on: Jun 10, 2025
 *      Author: chris
 */

#include "hal_uart.h"
#include "hal_rcc.h"
#include <stdio.h>

/*
 * USART2 Pins
 * CTS: PA0
 * RTS: PA1
 * TX: PA2 -> D1
 * RX: PA3 -> D0
 * CK: PA4
 *
 */

/*
 * USART 3 Tx Init
 */

void Hal_USART3_vInit(void)
{
	/* USART2 configuration */
	USART3->CR1 &= ~(1U << 0);      // UE = 0 (disable)
    USART3->CR1 &= ~(1U << 12);     // M = 0 (8-bit)
    USART3->CR1 &= ~(1U << 10);     // PCE = 0 (no parity)
    USART3->CR2 &= ~(3U << 12);     // STOP[1:0] = 00 (1 stop bit)
    // Baud = 115200 @ PCLK2 = 16 MHz
    uint32_t u32PeriphClock = 8000000;
    uint32_t u32BaudRate = 115200;
    uint16_t brr = (u32PeriphClock + (u32BaudRate/2))/u32BaudRate;
    USART3->BRR = brr;

    // Enable DMA for transmit (DMAT)
    USART3->CR3 |= (1U << 7);

    /* Transfer direction */
	USART3->CR1 |= (1U<<3);

    /* Enable the module */
    USART3->CR1 |= (1U << 0);   // UE = 1
}


void Hal_USART3_vWriteFunction(int ch)
{
	/* Transmit register must be empty */
	while (!(USART3->ISR & 0x80)){} // bit 7 = TXE
	/* Write to transmit register */
	USART3->TDR = (ch & 0xFF);
}

void Hal_USART2_vEnableSystemInterrupt(void)
{
	// Activate Interrupt in NVIC (Only NVIC is needed, no GPIO interrupt)
	NVIC_ISER1 |= (1U << 7); // Interrupt 38
	NVIC_ISER1 |= (1U << 6);
}
