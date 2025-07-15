/*
 * hal_gpio.h
 *
 *  Created on: Jun 10, 2025
 *      Author: chris
 */
#ifndef HAL_GPIO_H_
#define HAL_GPIO_H_

#include <memorymap.h>
#include "typedefs.h"
#include "peripherals.h"
#include "hal_uart.h"
#include "../Inc/Drivers/gpio_driver.h"

/*
 * GPIO mode
 */
#define GPIO_INPUT	0
#define GPIO_OUTPUT	1
#define GPIO_AF		2
#define GPIO_ANALOG	3

/*
 * GPIO Typ
 */
#define GPIO_PUSHPULL	0
#define GPIO_OPENDRAIN	1

/*
 * GPIO output speed
 */
#define GPIO_LOW		0
#define GPIO_MEDIUM		1
#define GPIO_HIGH		2
#define GPIO_VHIGH		3

/*
 * GPIO Pull-up/Pull-down
 */
#define GPIO_NON		0
#define GPIO_PULLUP		1
#define GPIO_PULLDOWN	2

/*
 * GPIO activate
 */
#define GPIO_PIN_EN		1
#define GPIO_PIN_DIS	1

typedef enum
{
	GPIO_A,
	GPIO_B,
	GPIO_C,
	GPIO_D,
	GPIO_E,
	GPIO_H
}GPIO_X;

/* Enable GPIO pin */
void Hal_GPIO_vEnable(short u8PinNumber, char u8Type, GPIO_X gpio);

/* Set GPIO pin output typ */
void Hal_GPIO_vTyp(short u8PinNumber, short u8Typ, GPIO_X gpio);

/* Set GPIO pin output speed */
void Hal_GPIO_vOutputSpeed(short u8PinNumber, short u8OutputSpeed);

/* Set GPIO pull-up/pull-down register */
void Hal_GPIO_vPullUpPullDown(short u8PinNumber, short u8PullUpPullDown, GPIO_X gpio);

/* Activate the GPIO pin output */
void Hal_GPIO_vOutputEnable(short u8PinNumber, GPIO_X gpio);

void Hal_GPIO_vOutputToggle(short u8PinNumber, GPIO_X gpio);

/* Deactivate the GPIO pin output */
void Hal_GPIO_vOutputDisable(short u8PinNumber, GPIO_X gpio);

void Config_vSetupGPIO(uint8_t u8Pin, uint8_t u8PinType, uint8_t u8Typ, uint8_t u8PuPd, GPIO_X gpio);

/* Setup for the alternate function pin */
void Hal_GPIO_vSetupAlternateFunction(uint8_t u8Pin, uint8_t u8AltFunc, GPIO_X gpio);

#endif /* HAL_GPIO_H_ */
