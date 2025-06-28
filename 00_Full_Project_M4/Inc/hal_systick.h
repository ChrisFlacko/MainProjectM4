/*
 * hal_systick.h
 *
 *  Created on: Jun 1, 2025
 *      Author: chris
 */

#ifndef HAL_SYSTICK_H_
#define HAL_SYSTICK_H_

#include <memorymap.h>
#include "typedefs.h"
#include "peripherals.h"
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

void Hal_SysTick_vInit(void);

void Hal_ButtonInterrupt_vInit(void);

#endif /* HAL_SYSTICK_H_ */
