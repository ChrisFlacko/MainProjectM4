/*
 * hal_dma.h
 *
 *  Created on: Jun 21, 2025
 *      Author: chris
 */

#ifndef HAL_DMA_H_
#define HAL_DMA_H_

#include "hal_memorymap.h"

typedef struct
{
	__IO uint32_t ISR;
	__IO uint32_t IFCR;
	__IO uint32_t CCR1;
	__IO uint32_t CNDTR1;
	__IO uint32_t CPAR1;
	__IO uint32_t CMAR1;
	__IO uint32_t reserved1;
	__IO uint32_t CCR2;
	__IO uint32_t CNDTR2;
	__IO uint32_t CPAR2;
	__IO uint32_t CMAR2;
	__IO uint32_t reserved2;
	__IO uint32_t CCR3;
	__IO uint32_t CNDTR3;
	__IO uint32_t CPAR3;
	__IO uint32_t CMAR3;
	__IO uint32_t reserved3;
	__IO uint32_t CCR4;
	__IO uint32_t CNDTR4;
	__IO uint32_t CPAR4;
	__IO uint32_t CMAR4;
	__IO uint32_t reserved4;
	__IO uint32_t CCR5;
	__IO uint32_t CNDTR5;
	__IO uint32_t CPAR5;
	__IO uint32_t CMAR5;
	__IO uint32_t reserved5;
	__IO uint32_t CCR6;
	__IO uint32_t CNDTR6;
	__IO uint32_t CPAR6;
	__IO uint32_t CMAR6;
	__IO uint32_t reserved6;
	__IO uint32_t CCR7;
	__IO uint32_t CNDTR7;
	__IO uint32_t CPAR7;
	__IO uint32_t CMAR7;

}TypeDef_DMA1;


#define DMA1		((TypeDef_DMA1*) DMA1_BASE_ADDR)

void Hal_DMA1_vInit(void);

void Hal_vEnableDMA(void);

void Hal_DMA1_vCorruptData(void);

uint32_t* Hal_DMA1_vGetTransmitData(void);


#endif /* HAL_DMA_H_ */
