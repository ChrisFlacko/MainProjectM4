/*
 * hal_i2c.h
 *
 *  Created on: Jun 19, 2025
 *      Author: chris
 */

#ifndef HAL_I2C_H_
#define HAL_I2C_H_

#include "hal_memorymap.h"
#include "hal_rcc.h"

typedef struct
{
	__IO uint32_t CR1;
	__IO uint32_t CR2;
	__IO uint32_t OAR1;
	__IO uint32_t OAR2;
	__IO uint32_t TIMINGR;
	__IO uint32_t TIMEOUTR;
	__IO uint32_t ISR;
	__IO uint32_t ICR;
	__IO uint32_t PEC;
	__IO uint32_t RXDR;
	__IO uint32_t TXDR;
}TypeDef_I2C1;

#define I2C1		((TypeDef_I2C1*) I2C1_BASE_ADDR)

#define OLED		0x3C

void Hal_I2C_vInitMaster(uint8_t address);

void Hal_I2C_vWriteCommand(uint8_t addr, uint8_t cmd);

void SSD1306_vInit(void);

void SSD1306_vWriteData(uint8_t addr, uint8_t data);

void SSD1306_vSendCommandBlock(uint8_t page, uint8_t columnLow, uint8_t columnHigh);

void SSD1306_vSendData(uint8_t data);

void SSD1306_vResetDisplay(void);

void SSD1306_vWriteDisplay(uint8_t row, uint8_t position, uint8_t number);


#endif /* HAL_I2C_H_ */
