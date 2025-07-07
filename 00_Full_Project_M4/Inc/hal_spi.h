/*
 * hal_spi.h
 *
 *  Created on: Jun 29, 2025
 *      Author: chris
 */

#ifndef HAL_SPI_H_
#define HAL_SPI_H_

#include "memorymap.h"
#include "peripherals.h"

void Hal_SPI_vInitReceiver(void);

uint16_t Hal_vSPIStartReceive(void);

#endif /* HAL_SPI_H_ */
