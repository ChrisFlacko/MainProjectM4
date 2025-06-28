/*
 * hal_i2c.c
 *
 *  Created on: Jun 19, 2025
 *      Author: chris
 */

#include "hal_i2c.h"


uint8_t SSD1306_Numbers[10][8] = {
    // 0
    {0x18, 0x24, 0x42, 0x81, 0x81, 0x42, 0x24, 0x18},
    // 1
    {0x00, 0x00, 0x00, 0x02, 0xFF, 0x00, 0x00, 0x00},
    // 2
    {0x00, 0x00, 0x81, 0xC1, 0xA2, 0x9C, 0x00, 0x00},
    // 3
    {0x00, 0x00, 0x00, 0x81, 0x99, 0x5A, 0x24, 0x00},
    // 4
    {0x10, 0x30, 0x50, 0x90, 0xFF, 0x10, 0x10, 0x00},
    // 5
    {0xFE, 0x82, 0x82, 0x82, 0x82, 0x42, 0x3C, 0x00},
    // 6
    {0x3C, 0x42, 0x81, 0x81, 0x81, 0x42, 0x00, 0x00},
    // 7
    {0x80, 0x80, 0x87, 0x98, 0xA0, 0xC0, 0x80, 0x00},
    // 8
    {0x36, 0x49, 0x89, 0x89, 0x89, 0x49, 0x36, 0x00},
    // 9
    {0x04, 0x4A, 0x89, 0x89, 0x89, 0x4A, 0x3C, 0x00}
};

uint8_t SSD1306_Letters[26][8] = {
		{0xF8, 0x14, 0x12, 0x11, 0x11, 0x12, 0x14, 0xF8}
};

/* Configure the CR2 register for master transmission */
void Hal_I2C_vInitMaster(uint8_t address)
{
	I2C1->TIMINGR |= (0x1 < 28);		// PRESC
	I2C1->TIMINGR |= (0x4 < 20);		// SCLDEL
	I2C1->TIMINGR |= (0x2 < 26);		// SDADEL
	I2C1->TIMINGR |= (0xF < 8);			// SCLH
	I2C1->TIMINGR |= (0x13 < 0);		// SCLL

	I2C1->CR2 |= (address << 1); // Set the slave address
	I2C1->CR2 &= ~(1U << 10);	// Master request write transfer
	I2C1->CR2 &= ~(1U << 11);	// 7bit addressing
	I2C1->CR2 |= (8 << 16); 	// 8 bytes to send

	I2C1->CR1 |= (1U << 0);  // Enable peripheral
}

void Hal_I2C_vWriteCommand(uint8_t addr, uint8_t cmd)
{
    // Clear previous settings
    I2C1->CR2 = 0;

    // Set slave address (bits [7:1]) and number of bytes (bits [23:16])
    I2C1->CR2 = ((addr << 1) & 0xFE) | (2 << 16); // 2 bytes (control + data)

    // Set START bit (bit 13)
    I2C1->CR2 |= (1U << 13);

    // Wait until TXIS (bit 1 of ISR) is set — ready to transmit
    while (!(I2C1->ISR & (1U << 1)));

    // Send control byte (0x00 = command)
    I2C1->TXDR = 0x00;

    // Wait for next TXIS
    while (!(I2C1->ISR & (1U << 1)));

    // Send actual command byte
    I2C1->TXDR = cmd;

    // Wait until TC (bit 6 of ISR) = Transfer Complete
    while (!(I2C1->ISR & (1U << 6)));

    // Set STOP (bit 14 of CR2)
    I2C1->CR2 |= (1U << 14);
}

void SSD1306_vInit(void)
{
    Hal_I2C_vWriteCommand(OLED, 0xAE); // Display off
    Hal_I2C_vWriteCommand(OLED, 0xD5); Hal_I2C_vWriteCommand(OLED, 0x80); // Clock divide
    Hal_I2C_vWriteCommand(OLED, 0xA8); Hal_I2C_vWriteCommand(OLED, 0x1F); // Multiplex = 32
    Hal_I2C_vWriteCommand(OLED, 0xD3); Hal_I2C_vWriteCommand(OLED, 0x00); // Offset
    Hal_I2C_vWriteCommand(OLED, 0x40); // Start line
    Hal_I2C_vWriteCommand(OLED, 0x8D); Hal_I2C_vWriteCommand(OLED, 0x14); // Charge pump on
    Hal_I2C_vWriteCommand(OLED, 0x20); Hal_I2C_vWriteCommand(OLED, 0x00); // Horizontal addressing
    Hal_I2C_vWriteCommand(OLED, 0xA1); // Segment remap
    Hal_I2C_vWriteCommand(OLED, 0xC8); // COM scan direction
    Hal_I2C_vWriteCommand(OLED, 0xDA); Hal_I2C_vWriteCommand(OLED, 0x02); // COM config
    Hal_I2C_vWriteCommand(OLED, 0x81); Hal_I2C_vWriteCommand(OLED, 0x8F); // Contrast
    Hal_I2C_vWriteCommand(OLED, 0xD9); Hal_I2C_vWriteCommand(OLED, 0xF1); // Precharge
    Hal_I2C_vWriteCommand(OLED, 0xDB); Hal_I2C_vWriteCommand(OLED, 0x40); // VCOM detect
    Hal_I2C_vWriteCommand(OLED, 0xA4); // Resume RAM content
    Hal_I2C_vWriteCommand(OLED, 0xA6); // Normal display
    Hal_I2C_vWriteCommand(OLED, 0xAF); // Display ON
}

void SSD1306_vWriteData(uint8_t addr, uint8_t data)
{
    // Clear previous transfer settings
    I2C1->CR2 = 0;

    // Set slave address and number of bytes to send (2 bytes: control + data)
    I2C1->CR2 = ((addr << 1) & 0xFE) | (2 << 16); // 7-bit address, write mode

    // Start the transmission
    I2C1->CR2 |= (1U << 13); // START

    // Wait for TXIS (ready to transmit)
    while (!(I2C1->ISR & (1U << 1)));

    // Send control byte: 0x40 indicates "data" follows
    I2C1->TXDR = 0x40;

    // Wait for TXIS again
    while (!(I2C1->ISR & (1U << 1)));

    // Send actual data byte
    I2C1->TXDR = data;

    // Wait until transfer is complete
    while (!(I2C1->ISR & (1U << 6))); // TC

    // Send STOP condition
    I2C1->CR2 |= (1U << 14);
}

void SSD1306_vSendCommandBlock(uint8_t page, uint8_t columnLow, uint8_t columnHigh)
{
    Hal_I2C_vWriteCommand(OLED, 0xB0 | (page & 0x03));     // Page address
    Hal_I2C_vWriteCommand(OLED, 0x00 | (columnLow & 0x0F)); // Lower column
    Hal_I2C_vWriteCommand(OLED, 0x10 | (columnHigh & 0x0F)); // Upper column
}

void SSD1306_vSendData(uint8_t data)
{
	// Send the data
	SSD1306_vWriteData(OLED, data);
}

void SSD1306_vResetDisplay(void)
{
    for (int k = 0; k < 4; k++)
    {
        for (int i = 0; i<128; i++)
        {
        	uint8_t lower = (i & 0x0F);
        	uint8_t upper = ((i >> 4) & 0x0F);
            SSD1306_vSendCommandBlock(k, lower, upper);
            SSD1306_vSendData(0x00);
        }
    }
}

void SSD1306_vWriteDisplay(uint8_t row, uint8_t position, uint8_t number)
{
	/* The position range for element 0 is 0-7 */
	/* Depending on the position, 8 needs to be added for the cases */

	// Get the starting bit
	uint8_t AdjPosition = (position*8);
	switch (row)
	{
		case 0:
			uint8_t count = 0;
			for (int i = AdjPosition; i < (AdjPosition+8); i++)
			{
	        	uint8_t lower = (i & 0x0F);
	        	uint8_t upper = ((i >> 4) & 0x0F);
	            SSD1306_vSendCommandBlock(row, lower, upper);
	            SSD1306_vSendData(SSD1306_Numbers[number][count]);
	            count++;

			}
			break;

		case 1:
			uint8_t count1 = 0;
			for (int i = AdjPosition; i < (AdjPosition+8); i++)
			{
	        	uint8_t lower = (i & 0x0F);
	        	uint8_t upper = ((i >> 4) & 0x0F);
	            SSD1306_vSendCommandBlock(row, lower, upper);
	            SSD1306_vSendData(SSD1306_Numbers[number][count1]);
	            count1++;

			}
			break;

		case 2:
			uint8_t count2 = 0;
			for (int i = AdjPosition; i < (AdjPosition+8); i++)
			{
	        	uint8_t lower = (i & 0x0F);
	        	uint8_t upper = ((i >> 4) & 0x0F);
	            SSD1306_vSendCommandBlock(row, lower, upper);
	            SSD1306_vSendData(SSD1306_Numbers[number][count2]);
	            count2++;

			}
			break;

		case 3:
			uint8_t count3 = 0;
			for (int i = AdjPosition; i < (AdjPosition+8); i++)
			{
	        	uint8_t lower = (i & 0x0F);
	        	uint8_t upper = ((i >> 4) & 0x0F);
	            SSD1306_vSendCommandBlock(row, lower, upper);
	            SSD1306_vSendData(SSD1306_Numbers[number][count3]);
	            count3++;

			}
			break;

	}
}


