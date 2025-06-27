/*
 * hal_systick.h
 *
 *  Created on: Jun 1, 2025
 *      Author: chris
 */

#ifndef HAL_SYSTICK_H_
#define HAL_SYSTICK_H_

#include "hal_memorymap.h"
#include "hal_rcc.h"
#include "hal_gpio.h"

/*
 * The Systick is a register inside the Cortex M0+. Therefore, you have to configure it directly there.
 * You need the ARM Cortex-M0+ Technical Reference Manual (TRM) for more information.
 * The systick is part of the SCS register, which is located at the address: 0xFFF0F003.
 * From there, the systick registers are divided by an offset.
 */
#define HCLK_FREQ     	16000000  // 16 MHz
#define TICK_HZ       	1000      // 1 ms tick
#define RELOAD_VAL    	((HCLK_FREQ / TICK_HZ))
#define CTRL_ENABLE		(1U<<0)
#define CTRL_TICKINT	(1U<<1)
#define CTRL_CLKSRC		(1U<<2)
#define CTRL_COUNTFLAG	(1U<<16)

typedef struct SysTick
{
	__IO uint32_t CTRL;
	__IO uint32_t LOAD;
	__IO uint32_t VAL;
	__IO uint32_t CALIB;

}TypeDef_SysTick;

#define SYSTCK ((TypeDef_SysTick*) SYSTICK_BASE)
#define STK_CTRL	(*(volatile uint32_t*)0xE000E010)
#define STK_LOAD	(*(volatile uint32_t*)0xE000E014)
#define STK_VAL		(*(volatile uint32_t*)0xE000E018)

void Hal_SysTick_vInit(void);

void Hal_ButtonInterrupt_vInit(void);



typedef struct
{
	__IO uint32_t CFGR1;
	__IO uint32_t RCR;
	__IO uint32_t EXTICR1;
	__IO uint32_t EXTICR2;
	__IO uint32_t EXTICR3;
	__IO uint32_t EXTICR4;
	__IO uint32_t CFGR2;
	__IO uint32_t reserved[0xE];
	__IO uint32_t CFGR3;
	__IO uint32_t CFGR4;
}TypeDef_SYSCFG;

#define SYSCFG	((TypeDef_SYSCFG*) SYSCFG_BASE_ADDR)

typedef struct
{
	__IO uint32_t IMR;
	__IO uint32_t EMR1;
	__IO uint32_t RTSR1;
	__IO uint32_t FTSR1;
	__IO uint32_t SWIER1;
	__IO uint32_t PR1;
	__IO uint32_t IMR2;
	__IO uint32_t EMR2;
	__IO uint32_t RTSR2;
	__IO uint32_t FTSR2;
	__IO uint32_t SWIER2;
	__IO uint32_t PR2;
}TypeDef_EXTI;

#define EXTI	((TypeDef_EXTI*) EXTI_BASE_ADDR)

#endif /* HAL_SYSTICK_H_ */
