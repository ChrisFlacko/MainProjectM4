/**
 ******************************************************************************
 * @file           : main.c
 * @author         : chris
 * @brief          : Main
 ******************************************************************************
 */
#include <../Inc/peripherals.h>
#include <../Inc/typedefs.h>
#include <../Inc/memorymap.h>

#include "../Inc/hal_gpio.h"
#include "../Inc/hal_uart.h"
#include "../Inc/hal_systick.h"
#include "../Inc/hal_dma.h"
#include "../Inc/hal_i2c.h"
#include "../Inc/hal_adc.h"

#include "main.h"
#include "stdint.h"

/*********************************************************************************************************************************
 * Interrupt Handlers
 *********************************************************************************************************************************/
uint16_t dataADC = 0;

// SysTick interrupt
void SysTick_Handler(void)
{
	Hal_vEnableDMA();
	uint32_t* prData = Hal_DMA1_vGetTransmitData();
	int j = 0;
	for (int i = 0; i < 10; i++)
	{
		SSD1306_vWriteDisplay(0, i, prData[j]);
		j++;
	}
    dataADC = Hal_ADC_u16ReadChannel();
    if (dataADC != 0)
    {
        Hal_GPIO_vOutputToggle(5, GPIO_A);  // Your action
    }

	/* Trigger PendSV to keep SysTick predictable */
	SCB_SHPR3 |= (0xFF << 16);  // Bits[23:16] = PendSV priority
	SCB_ICSR |= (1U << 28);
}

void PendSV_Handler()
{

}

// Button interrupt
void EXTI15_10_IRQHandler(void)
{
    if (EXTI->PR1 & (1U << 13))  // Check if EXTI13 triggered
    {
        EXTI->PR1 |= (1U << 13);  // Clear pending bit by writing 1
        Hal_DMA1_vCorruptData();
        Hal_GPIO_vOutputToggle(5, GPIO_A);  // Your action
    }
}

/*********************************************************************************************************************************
 * Main Function
 *********************************************************************************************************************************/

int main(void)
{
	// Activate all system clocks which are needed
	hal_vEnableRCCclock();

	// Activate all GPIOs needed
	Main_vSetupGPIOs();

	/***************************************************
	 * Activate all the peripherals:
	 * 	- USART3
	 * 	- DMA1
	 * 	- I2C1
	 * 	- ADC1
	 ***************************************************/

	// USART3 Init
	Hal_USART3_vInit();

	// DMA1 Init
	Hal_DMA1_vInit();

	// I2C Init
    Hal_I2C_vInitMaster(OLED);

    // OLED SSD Init
    SSD1306_vInit();

    // ADC1 Init
    Hal_ADC_vInit();

	/***************************************************
	 * Initial functions
	 ***************************************************/

    // Reset Display
    SSD1306_vResetDisplay();

    // Start ADC1
    Hal_ADC_vStart();

	/***************************************************
	 * Activate the interrupts (system and peripherals)
	 ***************************************************/

    // Enable Interrupts globally
    __asm volatile ("CPSIE i");

    // Enable Button interrupt
    Hal_ButtonInterrupt_vInit();

    // Enable SysTick interrupt
	Hal_SysTick_vInit();


    while(1)
    {

    }
}

/*********************************************************************************************************************************
 * Main Functions
 *********************************************************************************************************************************/

void Main_vSetupGPIOs(void)
{
	// Activate button at PC13
	Config_vSetupGPIO(13, GPIO_INPUT, GPIO_PUSHPULL, GPIO_PULLUP, GPIO_C);

	// Set LED at GPIOA on Pin5 to output
	Config_vSetupGPIO(5, GPIO_OUTPUT, GPIO_PUSHPULL, GPIO_PULLUP, GPIO_A);

	// Activate PB9 for USART3 Tx
	Config_vSetupGPIO(9, GPIO_AF, GPIO_PUSHPULL, GPIO_PULLUP, GPIO_B);
	Hal_GPIO_vSetupAlternateFunction(9, 7, GPIO_B);

	/* Using PB6 SCL and PB7 SDA, because the other ones interfere with debug */
	Config_vSetupGPIO(6, GPIO_AF, GPIO_PUSHPULL, GPIO_PULLUP, GPIO_B);
	Hal_GPIO_vSetupAlternateFunction(6, 4, GPIO_B);

	Config_vSetupGPIO(7, GPIO_AF, GPIO_PUSHPULL, GPIO_PULLUP, GPIO_B);
	Hal_GPIO_vSetupAlternateFunction(7, 4, GPIO_B);

    // Activate PA0 for the ADC as Analog input
	Config_vSetupGPIO(0, GPIO_ANALOG, GPIO_PUSHPULL, GPIO_NON, GPIO_A);
}
