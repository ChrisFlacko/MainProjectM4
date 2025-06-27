/*
 * hal_memorymap.h
 *
 *  Created on: Jun 10, 2025
 *      Author: chris
 */

#ifndef HAL_MEMORYMAP_H_
#define HAL_MEMORYMAP_H_
#include <stdint.h>

#define __IO					volatile

#define APB1_BASE_ADDR			0x40000000UL
#define APB2_BASE_ADDR			0x40010000UL
#define AHB1_BASE_ADDR			0x40020000UL
#define AHB2_BASE_ADDR			0x48000000UL
#define AHB3_BASE_ADDR			0x50000000UL
#define AHB4_BASE_ADDR			0x60000000UL


//#define TIM2_BASE_ADDR			()
//#define TIM3_BASE_ADDR
//#define TIM4_BASE_ADDR
//#define TIM6_BASE_ADDR
//#define TIM7_BASE_ADDR
//#define RTC_BASE_ADDR
//#define WWDG_BASE_ADDR
//#define IWDG_BASE_ADDR
//#define I2S2ext_BASE_ADDR
//#define SPI2_BASE_ADDR
//#define SPI3_BASE_ADDR
//#define I2S3ext_BASE_ADDR
#define USART2_BASE_ADDR		(APB1_BASE_ADDR + 0x00004400)
#define USART3_BASE_ADDR		(APB1_BASE_ADDR + 0x00004800)
#define I2C1_BASE_ADDR			(APB1_BASE_ADDR + 0x00005400)

#define SYSCFG_BASE_ADDR		(APB2_BASE_ADDR)
#define EXTI_BASE_ADDR			(APB2_BASE_ADDR + 0x00000400)


#define RCC_BASE_ADDR			(AHB1_BASE_ADDR + 0x00001000)
#define DMA1_BASE_ADDR			(AHB1_BASE_ADDR)

#define GPIOA_BASE_ADDR			(AHB2_BASE_ADDR)
#define GPIOB_BASE_ADDR			(AHB2_BASE_ADDR + 0x00000400)
#define GPIOC_BASE_ADDR			(AHB2_BASE_ADDR + 0x00000800)

#define ADC1_BASE_ADDR			(AHB3_BASE_ADDR)

#define NVIC_ISER0				(*(volatile uint32_t*) 0xE000E100)
#define NVIC_ISER1				(*(volatile uint32_t*) 0xE000E104)
#define SYSTICK_BASE			(*(volatile uint32_t*) 0xE000E010)



#endif /* HAL_MEMORYMAP_H_ */
