/*
 * hal_rcc.h
 *
 *  Created on: Jun 18, 2025
 *      Author: chris
 */

#ifndef HAL_RCC_H_
#define HAL_RCC_H_

#include "hal_memorymap.h"

typedef struct
{
	__IO uint32_t CR;
	__IO uint32_t CFGR;
	__IO uint32_t CIR;
	__IO uint32_t APB2RSTR;
	__IO uint32_t APB1SRTR;
	__IO uint32_t AHBENR;
	__IO uint32_t APB2ENR;
	__IO uint32_t APB1ENR;
	__IO uint32_t BDCR;
	__IO uint32_t CSR;
	__IO uint32_t AHBRSTR;
	__IO uint32_t CFGR2;
	__IO uint32_t CFGR3;
}TypeDef_RCC;



#define RCC			((TypeDef_RCC*)RCC_BASE_ADDR)


void hal_vEnableRCCclock(void);

#endif /* HAL_RCC_H_ */
