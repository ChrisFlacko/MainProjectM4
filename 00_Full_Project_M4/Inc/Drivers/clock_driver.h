/*
 * clock_driver.h
 *
 *  Created on: Jul 4, 2025
 *      Author: chris
 */

#ifndef DRIVERS_CLOCK_DRIVER_H_
#define DRIVERS_CLOCK_DRIVER_H_

#include "../memorymap.h"
#include "../peripherals.h"
#include "../typedefs.h"

/* Format, 0xRRBB
 * B = bits
 * R = Bus (00 = AHB, 01 = APB1, 10 = APB2) */
typedef enum
{
	GPIOA_Clock = 0x0011,
	GPIOB_Clock = 0x0012,
	GPIOC_Clock = 0x0013,
	GPIOD_Clock = 0x0014,
	GPIOE_Clock = 0x0015,
	GPIOH_Clock = 0x0010,
	USART1_Clock = 0x100E,		// Bit 14
	USART2_Clock = 0x0111,		// Bit 17
	USART3_Clock = 0x0112,		// Bit 18
	SPI1_Clock = 0x100C,		// Bit 12
	SPI2_Clock = 0x010E,		// Bit 14
	SPI3_Clock = 0x010F,		// Bit 15
	I2C1_Clock = 0x1015,		// Bit 21
	I2C2_Clock = 0x0116,		// Bit 22
	I2C3_Clock,
	DMA1_Clock = 0x0000,
	DMA2_Clock = 0x0001,
	ADC12_Clock = 0x001C,
	ADC34_Clock = 0x001D,
	SYSCFG_Clock = 0x1000,		// Bit 0
	RCC_Clock,
	EXTI_Clock
}TypeDef_Peripherals;

typedef struct
{
	uint8_t SizeAHB1;
	uint8_t SizeAHB2;
	uint8_t SizeAHB3;
	uint8_t SizeAPB1;
	uint8_t SizeAPB2;
	TypeDef_Peripherals AHB1Bus[6];
	TypeDef_Peripherals AHB2Bus[6];
	TypeDef_Peripherals AHB3Bus[2];
	TypeDef_Peripherals APB1Bus[23];
	TypeDef_Peripherals APB2Bus[9];

}TypeDef_Peripheral_Bus;


void ClockDriver_vEnable_Peripheral_Clocks(TypeDef_Peripheral_Bus* periph);

void ClockDriver_vClockSelect(void);


#endif /* DRIVERS_CLOCK_DRIVER_H_ */
