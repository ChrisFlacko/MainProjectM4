/*
 * hal_rcc.c
 *
 *  Created on: Jun 18, 2025
 *      Author: chris
 */


#include "hal_rcc.h"

void hal_vEnableRCCclock(void)
{
	/* Enable all necessary clocks */
	RCC->CR |= (1U << 0); 			// HSI clock, 8 MHz
	RCC->CFGR &= ~(0xF << 4);		// HSI clock not divided
    RCC->APB1ENR |= (1U << 17);     // USART2EN
    RCC->APB1ENR |= (1U << 18);     // USART3EN
    RCC->AHBENR |= (1U << 17);		// GPIOA clock enable
    RCC->AHBENR |= (1U << 18);
    RCC->AHBENR |= (1U << 19);		// GPIOC
    RCC->APB2ENR |= (1U << 0);		// SYSCFG
    RCC->AHBENR |= (1U << 0);		// DMA1 enable
    RCC->APB1ENR |= (1U << 21);		// I2C1
    RCC->AHBENR |= (1U << 28);		// ADC1 & 2
    RCC->APB2ENR |= (1U << 12);		// SPI 1 enable
    RCC->APB1ENR |= (1U << 15);
}
