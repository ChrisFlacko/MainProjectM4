/*
 * hal_systick.c
 *
 *  Created on: Jun 1, 2025
 *      Author: chris
 */

#include "hal_systick.h"


void Hal_SysTick_vInit(void)
{
	STK_LOAD = RELOAD_VAL;
	STK_VAL = 0;
	STK_CTRL = CTRL_ENABLE | CTRL_TICKINT | CTRL_CLKSRC;
}

void Hal_ButtonInterrupt_vInit(void)
{
	// Configure SYSCFG
	SYSCFG->EXTICR4 &= ~(0xF << 4);
	SYSCFG->EXTICR4 |= (0x2 << 4);
	// Configure EXTI13 line
    EXTI->IMR  |=  (1U << 13);         // Unmask interrupt
    EXTI->FTSR1 |=  (0U << 13);         // Falling edge trigger
    EXTI->RTSR1 |= (1U << 13);         // (optional) Disable rising edge

	// Configure NVIC
    NVIC_ISER1 |= (1U << (8));  // Enable IRQ 40 (EXTI15_10)
}
