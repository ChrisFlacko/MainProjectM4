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
#include "typedefs.h"

void Hal_SPI_vInitReceiver(void);

uint16_t Hal_vSPIStartReceive(void);

void Hal_SPI2_vInitReceiver(void);

uint16_t Hal_vSPI2_StartReceive(void);


#endif /* HAL_SPI_H_ */
