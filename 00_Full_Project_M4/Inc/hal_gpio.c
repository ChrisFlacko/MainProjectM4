/*
 * hal_gpio.c
 *
 *  Created on: Jun 10, 2025
 *      Author: chris
 */

#include "hal_gpio.h"

void Hal_GPIO_vEnable(short u8PinNumber, char u8Type, GPIO_X gpio)
{
	switch(gpio)
	{
	case GPIO_A:
		GPIOA->MODER &= ~(3U << (2 * u8PinNumber));
		GPIOA->MODER |= ((u8Type & 0x3U) << 2*u8PinNumber);
		break;

	case GPIO_B:
		GPIOB->MODER &= ~(3U << (2 * u8PinNumber));
		GPIOB->MODER |= ((u8Type & 0x3U) << 2*u8PinNumber);
		break;

	case GPIO_C:
		GPIOC->MODER &= ~(3U << (2 * u8PinNumber));
		GPIOC->MODER |= ((u8Type & 0x3U) << 2*u8PinNumber);
		break;

	case GPIO_D:
	case GPIO_E:
	case GPIO_H:
	default:
		break;
	}
}

void Hal_GPIO_vTyp(short u8PinNumber, short u8Typ, GPIO_X gpio)
{
	switch(gpio)
	{
	case GPIO_A:
		GPIOA->OTYPER &= ~(1U << u8PinNumber);
		GPIOA->OTYPER |= ((u8Typ & 0x1) << u8PinNumber);
		break;

	case GPIO_B:
		GPIOB->OTYPER &= ~(1U << u8PinNumber);
		GPIOB->OTYPER |= ((u8Typ & 0x1) << u8PinNumber);
		break;

	case GPIO_C:
		GPIOC->OTYPER &= ~(1U << u8PinNumber);
		GPIOC->OTYPER |= ((u8Typ & 0x1) << u8PinNumber);
		break;

	case GPIO_D:
	case GPIO_E:
	case GPIO_H:
	default:
		break;
	}
}

void Hal_GPIO_vOutputSpeed(short u8PinNumber, short u8OutputSpeed)
{
	GPIOA->OSPEEDR |= (u8OutputSpeed << u8PinNumber);
}

void Hal_GPIO_vPullUpPullDown(short u8PinNumber, short u8PullUpPullDown, GPIO_X gpio)
{
	switch(gpio)
	{
	case GPIO_A:
		GPIOA->PUPDR |= (u8PullUpPullDown << u8PinNumber);
		break;

	case GPIO_B:
		GPIOB->PUPDR |= (u8PullUpPullDown << u8PinNumber);
		break;

	case GPIO_C:
		GPIOC->PUPDR |= (u8PullUpPullDown << u8PinNumber);
		break;

	case GPIO_D:
	case GPIO_E:
	case GPIO_H:
	default:
		break;
	}
}

void Hal_GPIO_vOutputEnable(short u8PinNumber, GPIO_X gpio)
{
	switch(gpio)
	{
	case GPIO_A:
		GPIOA->BSRR = (GPIO_PIN_EN << u8PinNumber);
		break;

	case GPIO_B:
		GPIOB->BSRR = (GPIO_PIN_EN << u8PinNumber);
		break;

	case GPIO_D:
	case GPIO_E:
	case GPIO_H:
	default:
		break;
	}
}

void Hal_GPIO_vOutputToggle(short u8PinNumber, GPIO_X gpio)
{
	switch(gpio)
	{
	case GPIO_A:
		GPIOA->BSRR = ~(GPIOA->ODR);
		break;

	case GPIO_B:
		GPIOB->BSRR = (GPIO_PIN_EN << u8PinNumber);
		break;

	case GPIO_D:
	case GPIO_E:
	case GPIO_H:
	default:
		break;
	}
}

void Hal_GPIO_vOutputDisable(short u8PinNumber, GPIO_X gpio)
{
	switch(gpio)
	{
	case GPIO_A:
		GPIOA->BSRR = (1U << (u8PinNumber + 16));
		break;

	case GPIO_B:
		GPIOB->BSRR = (1U << (u8PinNumber + 16));
		break;

	case GPIO_D:
	case GPIO_E:
	case GPIO_H:
	default:
		break;
	}
}

void Config_vSetupGPIO(uint8_t u8Pin, uint8_t u8PinType, uint8_t u8Typ, uint8_t u8PuPd, GPIO_X gpio)
{
	Hal_GPIO_vEnable(u8Pin, u8PinType, gpio);
	Hal_GPIO_vTyp(u8Pin, u8Typ, gpio);
	Hal_GPIO_vPullUpPullDown(u8Pin, u8PuPd, gpio);
}
