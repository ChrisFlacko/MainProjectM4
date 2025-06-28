/*
 * hal_i2c.h
 *
 *  Created on: Jun 19, 2025
 *      Author: chris
 */

#ifndef HAL_I2C_H_
#define HAL_I2C_H_

#include <memorymap.h>
#include "typedefs.h"
#include "peripherals.h"
#include "hal_rcc.h"

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
