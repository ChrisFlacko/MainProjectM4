/*
 * hal_adc.h
 *
 *  Created on: Jun 23, 2025
 *      Author: chris
 */

#ifndef HAL_ADC_H_
#define HAL_ADC_H_

#include "hal_memorymap.h"

typedef struct
{
	__IO uint32_t ISR;
	__IO uint32_t IER;
	__IO uint32_t CR;
	__IO uint32_t CFGR;
	__IO uint32_t reserved1;
	__IO uint32_t SMPR1;
	__IO uint32_t SMPR2;
	__IO uint32_t reserved2;
	__IO uint32_t TR1;
	__IO uint32_t TR2;
	__IO uint32_t TR3;
	__IO uint32_t reserved3;
	__IO uint32_t SQR1;
	__IO uint32_t SQR2;
	__IO uint32_t SQR3;
	__IO uint32_t SQR4;
	__IO uint32_t DR;
	__IO uint32_t reserved4[2];
	__IO uint32_t JSQR;
	__IO uint32_t reserved5[4];
	__IO uint32_t OFR1;
	__IO uint32_t OFR2;
	__IO uint32_t OFR3;
	__IO uint32_t OFR4;
	__IO uint32_t reserved6[4];
	__IO uint32_t JDR1;
	__IO uint32_t JDR2;
	__IO uint32_t JDR3;
	__IO uint32_t JDR4;
	__IO uint32_t reserved7[4];
	__IO uint32_t AWD2CR;
	__IO uint32_t AWD3CR;
	__IO uint32_t reserved8[2];
	__IO uint32_t DIFSEL;
	__IO uint32_t CALFACT;
}TypeDef_ADC;

typedef struct
{
	__IO uint32_t CSR;
	__IO uint32_t reserved;
	__IO uint32_t CCR;
	__IO uint32_t CDR;

}TypeDef_ADC_Master;

#define ADC1		((TypeDef_ADC*) ADC1_BASE_ADDR)
#define ADC_MASTER ((TypeDef_ADC_Master*)(ADC1_BASE_ADDR + 0x300))


void Hal_ADC_vInit(void);

void Hal_ADC_vStart(void);

uint16_t Hal_ADC_u16ReadChannel(void);


#endif /* HAL_ADC_H_ */
