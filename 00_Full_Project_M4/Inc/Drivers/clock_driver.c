/*
 * clock_driver.c
 *
 *  Created on: Jul 4, 2025
 *      Author: chris
 */
#include "clock_driver.h"

void ClockDriver_vEnable_Peripheral_Clocks(TypeDef_Peripheral_Bus* periph)
{
	uint8_t size = 0;

	/* System clock */
	RCC->CR |= (1U << 0); 			// HSI clock, 8 MHz
	RCC->CFGR &= ~(0xF << 4);		// HSI clock not divided

	/* AHB1 bus clocks */
	size = periph->SizeAHB1;

	for (int i = 0; i < size; i++)
	{
		RCC->AHBENR |= (1U << periph->AHB1Bus[i]);
	}

	/* AHB2 bus clocks */
	size = periph->SizeAHB2;
	for (int i = 0; i < size; i++)
	{
		RCC->AHBENR |= (1U << periph->AHB2Bus[i]);
	}

	/* AHB3 bus clocks */
	size = periph->SizeAHB3;
	for (int i = 0; i < size; i++)
	{
		RCC->AHBENR |= (1U << periph->AHB3Bus[i]);
	}

	/* APB1 bus clocks */
	size = periph->SizeAPB1;
	for (int i = 0; i < size; i++)
	{
		RCC->APB1ENR |= (1U << (uint8_t)((periph->APB1Bus[i]) & 0x00FF));
	}

	/* APB2 bus clocks */
	size = periph->SizeAPB2;
	for (int i = 0; i < size; i++)
	{
		RCC->APB2ENR |= (1U << (uint8_t)((periph->APB2Bus[i]) & 0x00FF));
	}
}

void ClockDriver_vClockSelect(void)
{
	TypeDef_Peripheral_Bus peripherals;
	peripherals.SizeAHB1 = 1;
	peripherals.AHB1Bus[0] = DMA1_Clock;

	peripherals.SizeAHB2 = 3;
	peripherals.AHB2Bus[0] = GPIOA_Clock;
	peripherals.AHB2Bus[1] = GPIOB_Clock;
	peripherals.AHB2Bus[2] = GPIOC_Clock;

	peripherals.SizeAHB3 = 1;
	peripherals.AHB3Bus[0] = ADC12_Clock;

	peripherals.SizeAPB1 = 3;
	peripherals.APB1Bus[0] = SPI3_Clock;
	peripherals.APB1Bus[1] = USART3_Clock;
	peripherals.APB1Bus[2] = I2C1_Clock;

	peripherals.SizeAPB2 = 2;
	peripherals.APB2Bus[0] = SYSCFG_Clock;
	peripherals.APB2Bus[1] = EXTI_Clock;

	ClockDriver_vEnable_Peripheral_Clocks(&peripherals);
}
