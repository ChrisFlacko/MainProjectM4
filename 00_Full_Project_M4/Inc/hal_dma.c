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

uint16_t dataADC = 0;

void Hal_DMA_1_vInitChannel2(void)
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

void Hal_DMA_1_vInitChannel3(void)
{
	// Disable DMA1
	DMA1->CCR3 &= ~(1U << 0);						// EN = 0

	// Set peripheral register address (ADC1->DR)
	DMA1->CPAR3 = (uint32_t)&ADC1->DR;		// 0x40 is the offset to DR

	// Set memory address (array address)
	DMA1->CMAR3 = (uint32_t)&dataADC;

	// Configure the total numbers of data to transfer
	DMA1->CNDTR3 = 1U;								// One data transfer

	// Configure the CCR1 register
	DMA1->CCR3 |= (1U<<1) 							// Transfer complete interrupt
			| (0U << 5)								// Non-Circular mode
			| (1U << 12);							// Priority mode medium

	DMA1->CCR3 &= ~ (1U << 4);						// Read from peripheral
	DMA1->CCR3 &= ~ (1U << 6);						// Disable increment

	DMA1->CCR3 &= ~(0x3 << 8);						// Reset Peripheral size
	DMA1->CCR3 |= (1U << 8);						// Peripheral size 16 bit

	DMA1->CCR3 &= ~(0x3 << 10);						// Reset memory size
	DMA1->CCR3 |= (1U << 10);						// Memory size 16 bit
}

void Hal_vEnableDMAChannel2(void)
{
    // Disable DMA before reconfiguring
    DMA1->CCR2 &= ~(1U << 0);        // Clear EN

	// Reset the transfer count
	DMA1->CNDTR2 = 10;

	// Activate DMA again
	DMA1->CCR2 |= (1U << 0);
}

void Hal_vEnableDMAChannel3(void)
{
    // Disable DMA before reconfiguring
    DMA1->CCR3 &= ~(1U << 0);        // Clear EN

	// Reset the transfer count
	DMA1->CNDTR3 = 1;

	// Activate DMA again
	DMA1->CCR3 |= (1U << 0);
}

void Hal_DMA1_vCorruptData(void)
{
	TransmitData[0] = ~TransmitData[0];
}

uint32_t* Hal_DMA1_vGetTransmitData(void)
{
	return (&TransmitData);
}

uint16_t* Hal_DMA1_vGetADCData(void)
{
	return (&dataADC);
}
