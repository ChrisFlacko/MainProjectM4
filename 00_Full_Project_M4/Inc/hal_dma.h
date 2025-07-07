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

void Hal_DMA_1_vInitChannel2(void);

void Hal_DMA_1_vInitChannel3(void);

void Hal_vEnableDMAChannel2(void);

void Hal_vEnableDMAChannel3(void);

void Hal_DMA1_vCorruptData(void);

uint32_t* Hal_DMA1_vGetTransmitData(void);

uint16_t* Hal_DMA1_vGetADCData(void);


#endif /* HAL_DMA_H_ */
