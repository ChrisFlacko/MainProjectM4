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
		GPIOA->MODER &= GPIO_MODER_RESET(u8PinNumber);
		GPIOA->MODER |= GPIO_MODER_SET(u8PinNumber, u8Type);
		break;

	case GPIO_B:
		GPIOB->MODER &= GPIO_MODER_RESET(u8PinNumber);
		GPIOB->MODER |= GPIO_MODER_SET(u8PinNumber, u8Type);
		break;

	case GPIO_C:
		GPIOC->MODER &= GPIO_MODER_RESET(u8PinNumber);
		GPIOC->MODER |= GPIO_MODER_SET(u8PinNumber, u8Type);
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
		GPIOA->OTYPER &= GPIO_OTYPER_RESET(u8PinNumber);
		GPIOA->OTYPER |= GPIO_OTYPER_SET(u8PinNumber, u8Typ);
		break;

	case GPIO_B:
		GPIOB->OTYPER &= GPIO_OTYPER_RESET(u8PinNumber);
		GPIOB->OTYPER |= GPIO_OTYPER_SET(u8PinNumber, u8Typ);
		break;

	case GPIO_C:
		GPIOC->OTYPER &= GPIO_OTYPER_RESET(u8PinNumber);
		GPIOC->OTYPER |= GPIO_OTYPER_SET(u8PinNumber, u8Typ);
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
	GPIOA->OSPEEDR |= GPIO_OPSPEED_RESET(u8PinNumber);
	GPIOA->OSPEEDR |= GPIO_OPSPEED_SET(u8OutputSpeed, u8PinNumber);
}

void Hal_GPIO_vPullUpPullDown(short u8PinNumber, short u8PullUpPullDown, GPIO_X gpio)
{
	switch(gpio)
	{
	case GPIO_A:
		GPIOA->PUPDR &= GPIO_PUPD_RESET(u8PinNumber);
		GPIOA->PUPDR |= GPIO_PUPD_SET(u8PullUpPullDown, u8PinNumber);
		break;

	case GPIO_B:
		GPIOB->PUPDR &= GPIO_PUPD_RESET(u8PinNumber);
		GPIOB->PUPDR |= GPIO_PUPD_SET(u8PullUpPullDown, u8PinNumber);
		break;

	case GPIO_C:
		GPIOC->PUPDR &= GPIO_PUPD_RESET(u8PinNumber);
		GPIOC->PUPDR |= GPIO_PUPD_SET(u8PullUpPullDown, u8PinNumber);
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
		GPIOA->BSRR = GPIO_BSSR_SET(u8PinNumber, GPIO_PIN_EN);
		break;

	case GPIO_B:
		GPIOB->BSRR = GPIO_BSSR_SET(u8PinNumber, GPIO_PIN_EN);
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
		GPIOB->BSRR = ~(GPIOB->ODR);
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

void Hal_GPIO_vSetupAlternateFunction(uint8_t u8Pin, uint8_t u8AltFunc, GPIO_X gpio)
{
	switch (gpio){
		case GPIO_A:
			if (u8Pin <= 7)
			{
			    GPIOA->AFRL &= ~(0xF << (u8Pin*4));
			    GPIOA->AFRL |=  (u8AltFunc << (u8Pin*4));
			}
			else
			{
			    GPIOA->AFRH &= ~(0xF << ((u8Pin-8)*4));
			    GPIOA->AFRH |=  (u8AltFunc << ((u8Pin-8)*4));
			}
			break;

		case GPIO_B:
			if (u8Pin <= 7)
			{
			    GPIOB->AFRL &= ~(0xF << (u8Pin*4));
			    GPIOB->AFRL |=  (u8AltFunc << (u8Pin*4));
			}
			else
			{
			    GPIOB->AFRH &= ~(0xF << ((u8Pin-8)*4));
			    GPIOB->AFRH |=  (u8AltFunc << ((u8Pin-8)*4));
			}
			break;

		case GPIO_C:
			if (u8Pin <= 7)
			{
			    GPIOC->AFRL &= ~(0xF << (u8Pin*4));  // Clear AFR for PB9
			    GPIOC->AFRL |=  (u8AltFunc << (u8Pin*4));  // AF7 = USART3
			}
			else
			{
			    GPIOC->AFRH &= ~(0xF << ((u8Pin-8)*4));  // Clear AFR for PB9
			    GPIOC->AFRH |=  (u8AltFunc << ((u8Pin-8)*4));
			}
			break;

		case GPIO_D:
			if (u8Pin <= 7)
			{
			    GPIOD->AFRL &= ~(0xF << (u8Pin*4));  // Clear AFR for PB9
			    GPIOD->AFRL |=  (u8AltFunc << (u8Pin*4));  // AF7 = USART3
			}
			else
			{
			    GPIOD->AFRH &= ~(0xF << ((u8Pin-8)*4));  // Clear AFR for PB9
			    GPIOD->AFRH |=  (u8AltFunc << ((u8Pin-8)*4));
			}
			break;

		case GPIO_E:
			if (u8Pin <= 7)
			{
			    GPIOE->AFRL &= ~(0xF << (u8Pin*4));  // Clear AFR for PB9
			    GPIOE->AFRL |=  (u8AltFunc << (u8Pin*4));  // AF7 = USART3
			}
			else
			{
			    GPIOE->AFRH &= ~(0xF << ((u8Pin-8)*4));  // Clear AFR for PB9
			    GPIOE->AFRH |=  (u8AltFunc << ((u8Pin-8)*4));
			}
			break;

		case GPIO_H:
			if (u8Pin <= 7)
			{
			    GPIOH->AFRL &= ~(0xF << (u8Pin*4));  // Clear AFR for PB9
			    GPIOH->AFRL |=  (u8AltFunc << (u8Pin*4));  // AF7 = USART3
			}
			else
			{
			    GPIOH->AFRH &= ~(0xF << ((u8Pin-8)*4));  // Clear AFR for PB9
			    GPIOH->AFRH |=  (u8AltFunc << ((u8Pin-8)*4));
			}
			break;

		default:

			break;
	}
}
