/*
 * hal_adc.h
 *
 *  Created on: Jun 23, 2025
 *      Author: chris
 */

#ifndef HAL_ADC_H_
#define HAL_ADC_H_

#include <memorymap.h>
#include <typedefs.h>
#include <peripherals.h>

void Hal_ADC_vInit(void);

void Hal_ADC_vStart(void);

/* Read out the ADC1 channel */
uint16_t Hal_ADC_u16ReadChannel(void);


#endif /* HAL_ADC_H_ */
