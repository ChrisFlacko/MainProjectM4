/*
 * hal_spi.c
 *
 *  Created on: Jun 29, 2025
 *      Author: chris
 */


#include "hal_spi.h"

void Hal_SPI_vInitReceiver(void)
{
	SPI3->CR1 |= (1U << 0)	  // Second clock is first data capture and clock to 1 when idle
			| (1U << 1);
	SPI3->CR1 &= ~(1U << 2);  // Clear MSTR bit → Set slave mode
	SPI3->CR1 &= ~(1U << 7);  // Use MSB first (standard)
	SPI3->CR1 |= (1U << 11);  // Set 16-bit data

	SPI3->CR1 |= (1U << 8);  // SSM = 1
	SPI3->CR1 |= (1U << 9);  // SSI = 1

    // Enable SPI
	SPI3->CR1 |= (1U << 6);  // SPE
}


uint16_t Hal_vSPIStartReceive(void)
{
    while (!(SPI3->SR & (1U << 0)));  // Wait for RXNE
    return (uint8_t)SPI3->DR;
}


void Hal_SPI2_vInitReceiver(void)
{
	SPI2->CR1 |= (1U << 0)	  // Second clock is first data capture and clock to 1 when idle
			| (1U << 1);
	SPI2->CR1 &= ~(1U << 2);  // Clear MSTR bit → Set slave mode
	SPI2->CR1 &= ~(1U << 7);  // Use MSB first (standard)
	SPI2->CR1 |= (1U << 11);  // Set 16-bit data
	SPI2->CR1 &= ~(1U << 15);	// 2 line unidirectional mode
	SPI2->CR1 &= ~(1U << 10);   // RXONLY = 1 → Receive-only mode

	SPI2->CR1 &= ~(1U << 8);  // SSM = 0 → hardware NSS

    // Enable SPI
	SPI2->CR1 |= (1U << 6);  // SPE
}


uint16_t Hal_vSPI2_StartReceive(void)
{
    while (!(SPI2->SR & (1U << 0)));  // Wait for RXNE
    return (uint8_t)SPI2->DR;
}
