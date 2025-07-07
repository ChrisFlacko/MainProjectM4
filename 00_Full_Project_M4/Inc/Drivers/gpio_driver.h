/*
 * gpio_driver.h
 *
 *  Created on: Jul 2, 2025
 *      Author: chris
 */

#ifndef DRIVERS_GPIO_DRIVER_H_
#define DRIVERS_GPIO_DRIVER_H_

#include "../memorymap.h"
#include "../peripherals.h"
#include "../typedefs.h"

#define GPIO_MODER_RESET(Pin) 				(~(0x3U << ((Pin) << 1)))
#define GPIO_MODER_SET(Pin, Mode)			((Mode & 0x3U) << (0x2 * Pin))
#define GPIO_OTYPER_RESET(Pin)				(~(0x1U << Pin))
#define GPIO_OTYPER_SET(Pin, Mode)			((Mode & 0x1) << Pin)
#define GPIO_PUPD_RESET(Pin)				(~(0x1U << Pin))
#define GPIO_PUPD_SET(Pin, Mode)			(Mode << Pin)
#define GPIO_OPSPEED_RESET(Pin)				(~(0x1U << Pin))
#define GPIO_OPSPEED_SET(Pin, Mode)			(Mode << Pin)
#define GPIO_BSSR_SET(Pin, Mode)			(Mode << Pin)

#endif /* DRIVERS_GPIO_DRIVER_H_ */
