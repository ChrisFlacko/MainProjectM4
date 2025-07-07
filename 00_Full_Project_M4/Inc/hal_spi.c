/*
 * hal_spi.c
 *
 *  Created on: Jun 29, 2025
 *      Author: chris
 */


#include "hal_spi.h"

void Hal_SPI_vInitReceiver(void)
{
	SPI3->CR1 &= ~(0x7 << 3); // Baudrate: clock/2
	SPI3->CR1 |= (1U << 0)	  // Second clock is first data capture and clock to 1 when idle
			| (1U << 1);
	SPI3->CR1 &= ~(1U << 2);  // Clear MSTR bit → Set slave mode
	SPI3->CR1 &= ~(1U << 7);  // Use MSB first (standard)
	SPI3->CR1 &= ~(1U << 11);  // 8-bit data

	SPI3->CR1 &= ~(1U << 8);  // SSM = 0
	SPI3->CR1 |= (1U << 9);   // SSI = 1 (drive NSS high internally)

    // Enable SPI
	SPI3->CR1 |= (1U << 6);  // SPE
}


uint16_t Hal_vSPIStartReceive(void)
{
//    while (!(SPI3->SR & (1U << 0)));  // Wait for RXNE
    return (uint8_t)SPI3->DR;
}
