/*
 * hal_dma.h
 *
 *  Created on: Jun 21, 2025
 *      Author: chris
 */

#ifndef HAL_DMA_H_
#define HAL_DMA_H_

#include <memorymap.h>
#include "typedefs.h"
#include "peripherals.h"

void Hal_DMA1_vInit(void);

void Hal_vEnableDMA(void);

void Hal_DMA1_vCorruptData(void);

uint32_t* Hal_DMA1_vGetTransmitData(void);


#endif /* HAL_DMA_H_ */
