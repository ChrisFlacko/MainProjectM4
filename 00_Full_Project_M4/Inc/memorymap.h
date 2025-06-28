/*
 * hal_memorymap.h
 *
 *  Created on: Jun 10, 2025
 *      Author: chris
 *
 *  Description:
 *		This file contains all the necessary addresses of the Nucleo-F303RE evaluation board.
 */

#ifndef MEMORYMAP_H_
#define MEMORYMAP_H_
#include <stdint.h>

#define __IO					volatile

/* Bus addresses */
#define APB1_BASE_ADDR			0x40000000UL
#define APB2_BASE_ADDR			0x40010000UL
#define AHB1_BASE_ADDR			0x40020000UL
#define AHB2_BASE_ADDR			0x48000000UL
#define AHB3_BASE_ADDR			0x50000000UL
#define AHB4_BASE_ADDR			0x60000000UL

/* APB1 bus modules */
#define USART2_BASE_ADDR		(APB1_BASE_ADDR + 0x00004400)
#define USART3_BASE_ADDR		(APB1_BASE_ADDR + 0x00004800)
#define I2C1_BASE_ADDR			(APB1_BASE_ADDR + 0x00005400)

/* APB2 bus modules */
#define SYSCFG_BASE_ADDR		(APB2_BASE_ADDR)
#define EXTI_BASE_ADDR			(APB2_BASE_ADDR + 0x00000400)

/* AHB1 bus modules */
#define RCC_BASE_ADDR			(AHB1_BASE_ADDR + 0x00001000)
#define DMA1_BASE_ADDR			(AHB1_BASE_ADDR)

/* AHB2 bus modules */
#define GPIOA_BASE_ADDR			(AHB2_BASE_ADDR)
#define GPIOB_BASE_ADDR			(AHB2_BASE_ADDR + 0x00000400)
#define GPIOC_BASE_ADDR			(AHB2_BASE_ADDR + 0x00000800)
#define GPIOD_BASE_ADDR			(AHB2_BASE_ADDR + 0x00000C00)
#define GPIOE_BASE_ADDR			(AHB2_BASE_ADDR + 0x00001000)
#define GPIOH_BASE_ADDR			(AHB2_BASE_ADDR + 0x00001400)

/* AHB3 bus modules */
#define ADC1_BASE_ADDR			(AHB3_BASE_ADDR)

/* Internal processor registers */
#define NVIC_ISER0				(*(volatile uint32_t*)0xE000E100)
#define NVIC_ISER1				(*(volatile uint32_t*)0xE000E104)
#define SYSTICK_BASE			(*(volatile uint32_t*)0xE000E010)
#define SYSTCK 					((TypeDef_SysTick*) SYSTICK_BASE)
#define STK_CTRL				(*(volatile uint32_t*)0xE000E010)
#define STK_LOAD				(*(volatile uint32_t*)0xE000E014)
#define STK_VAL					(*(volatile uint32_t*)0xE000E018)
#define SCB_ICSR 				(*(volatile uint32_t*)0xE000E00C)
#define SCB_SHPR3				(*(volatile uint32_t*)0xE000ED20)



#endif /* MEMORYMAP_H_ */
