/*
 * hal_adc.c
 *
 *  Created on: Jun 23, 2025
 *      Author: chris
 */

#include "hal_adc.h"


/*
 * Initialization of the ADC1
 * 	- Setup the voltage regulator
 * 	- Calibrate ADC
 * 	- Configure channel
 * 	- Configure sample rate
 * 	- Configure resolution
 * 	- Enable ADC and wait till its ready
 */
void Hal_ADC_vInit(void)
{
	ADC_MASTER->CCR &= ~(0x3 << 16);
	ADC_MASTER->CCR |= (0x1 << 16);		// HCLK/1
    if (ADC1->CR & (1U << 0))  // Check ADEN
    {
        ADC1->CR |= (1U << 1); // Set ADDIS to disable ADC
        while (ADC1->CR & (1U << 0));  // Wait until ADEN == 0
    }

    // 2. Enable voltage regulator
    ADC1->CR &= ~(0b11 << 28);      // Clear bits 28 and 29
    ADC1->CR |=  (0b01 << 28);      // Set ADVREGEN = 01
    for (volatile int i = 0; i < 10000; ++i);  // Short delay (10+ µs needed)

    // 3. Calibrate ADC
    ADC1->CR &= ~(1U << 30);   // Single-ended calibration
    ADC1->CR |= (1U << 31);    // Start calibration

    while (ADC1->CR & (1U << 31));  // Wait for calibration to finish

    // 4. Enable ADC
    ADC1->CR |= (1U << 0);  // ADEN
    while (!(ADC1->ISR & (1U << 0)));  // Wait for ADRDY

    // 5. Configure channel, resolution, sample time (same as before)
    ADC1->SQR1 &= ~(0xF << 0);		// 1 conversion
    ADC1->SQR1 |= (1U << 6);  		// Rank 1 = channel 1

    ADC1->SMPR1 &= ~(0x7 << 3);
    ADC1->SMPR1 |= (0b111 << 3);	// Long sample time

    ADC1->CFGR &= ~(0x3 << 3);		// 12-bit resolution
    ADC1->CFGR |= (1U << 0);		// Enable DMA
    ADC1->CFGR &= ~(1U << 1);		// DMA one shot

    ADC1->CFGR |= (1U << 13);  // CONT = 1 => Continuous conversion mode
}

void Hal_ADC_vStart(void)
{
	ADC1->CR |= (1U << 2);  // ADSTART = 1
}

uint16_t Hal_ADC_u16ReadChannel(void)
{
    ADC1->CR |= (1U << 2);                // Start conversion
    while (!(ADC1->ISR & (1U << 2)));     // Wait for EOC
    return (uint16_t)ADC1->DR;
}
