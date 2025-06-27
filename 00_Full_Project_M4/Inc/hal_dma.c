/*
 * hal_dma.c
 *
 *  Created on: Jun 21, 2025
 *      Author: chris
 */

#include "hal_dma.h"
#include "hal_uart.h"

/*
 * Using DMA 1 to automatically store a value from memory to a peripheral
 * The bytes which gets send out should be automatically stored in the USART transmit buffer
 * DMA1 channel 2 is needed, see DMA1 request mapping. Ch2 is for USART3_TX
 */

uint8_t TransmitData[10] =
		{0xBB, 0xB1, 0xB2, 0xBC, 0xFB, 0xEF, 0xCC, 0xDD, 0xBB, 0x22};

void Hal_DMA1_vInit(void)
{
	// Disable DMA1
	DMA1->CCR2 &= ~(1U << 0);						// EN = 0

	// Set peripheral register address (USART3->TDR)
	DMA1->CPAR2 = (USART3_BASE_ADDR + 0x28);		// 0x28 is the offset to TDR

	// Set memory address (array address)
	DMA1->CMAR2 = (uint32_t)&TransmitData;

	// Configure the total numbers of data to transfer
	DMA1->CNDTR2 = 10U;								// One byte to send

	// Configure the CCR1 register
	DMA1->CCR2 |= (1U<<1) 							// Transfer complete interrupt
			| (1U << 4)								// Read from memory
			| (0U << 5)								// Non-Circular mode
			| (1U << 7)								// Memory increment mode
			| (1U << 12);							// Priority mode medium

	DMA1->CCR2 &= ~(0x3 << 8);						// Peripheral size 8 bit
	DMA1->CCR2 &= ~(0x3 << 10);						// Memory size 8 bit

//	DMA1->CCR2 |= (1U << 0);						// Enable DMA

    USART3->CR3 |= (1U << 7);
}

void Hal_vEnableDMA(void)
{
    // Disable DMA before reconfiguring
    DMA1->CCR2 &= ~(1U << 0);        // Clear EN

	// Reset the transfer count
	DMA1->CNDTR2 = 10;

	// Activate DMA again
	DMA1->CCR2 |= (1U << 0);
}

void Hal_DMA1_vCorruptData(void)
{
	TransmitData[0] = ~TransmitData[0];
}

uint32_t* Hal_DMA1_vGetTransmitData(void)
{
	return (&TransmitData);
}
