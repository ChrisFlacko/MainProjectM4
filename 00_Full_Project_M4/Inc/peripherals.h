/*
 * peripherals.h
 *
 *  Created on: Jun 27, 2025
 *      Author: chris
 */

#ifndef PERIPHERALS_H_
#define PERIPHERALS_H_

#include "memorymap.h"
#include "typedefs.h"

/* ADC */
#define ADC1		((TypeDef_ADC*) ADC1_BASE_ADDR)
#define ADC_MASTER	((TypeDef_ADC_Master*)(ADC1_BASE_ADDR + 0x300))

/* GPIO */
#define GPIOA ((TypeDef_GPIO*) GPIOA_BASE_ADDR)
#define GPIOB ((TypeDef_GPIO*) GPIOB_BASE_ADDR)
#define GPIOC ((TypeDef_GPIO*) GPIOC_BASE_ADDR)
#define GPIOD ((TypeDef_GPIO*) GPIOD_BASE_ADDR)
#define GPIOE ((TypeDef_GPIO*) GPIOE_BASE_ADDR)
#define GPIOH ((TypeDef_GPIO*) GPIOH_BASE_ADDR)

/* DMA */
#define DMA1		((TypeDef_DMA1*) DMA1_BASE_ADDR)

/* I2C */
#define I2C1		((TypeDef_I2C1*) I2C1_BASE_ADDR)

/* RCC */
#define RCC			((TypeDef_RCC*)RCC_BASE_ADDR)

/* SYSCFG */
#define SYSCFG	((TypeDef_SYSCFG*) SYSCFG_BASE_ADDR)

/* EXTI */
#define EXTI	((TypeDef_EXTI*) EXTI_BASE_ADDR)

/* USART */
#define USART2	((TypeDef_USART*) USART2_BASE_ADDR)
#define USART3	((TypeDef_USART*) USART3_BASE_ADDR)

/* SPI */
#define SPI1	((TypeDef_SPI*) SPI1_BASE_ADDR)
#define SPI2	((TypeDef_SPI*) SPI2_BASE_ADDR)
#define SPI3	((TypeDef_SPI*) SPI3_BASE_ADDR)

#endif /* PERIPHERALS_H_ */
