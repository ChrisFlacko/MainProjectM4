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
#include "../Inc/hal_spi.h"
#include "../Inc/hal_rcc.h"

#include "../Inc/Drivers/gpio_driver.h"
#include "../Inc/Drivers/clock_driver.h"

#include "main.h"
#include "stdint.h"


/*********************************************************************************************************************************
 * Defines and Typedefs
 *********************************************************************************************************************************/



/*********************************************************************************************************************************
 * Interrupt Handlers
 *********************************************************************************************************************************/

// SysTick interrupt
void SysTick_Handler(void)
{
	volatile uint16_t dataSPI = Hal_vSPIStartReceive();
	if (dataSPI != 0)
	{
        Hal_GPIO_vOutputToggle(5, GPIO_A);  // Your action
	}
	Hal_vEnableDMAChannel2();
	Hal_vEnableDMAChannel3();
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
	/* Activate all clocks which are needed */
	ClockDriver_vClockSelect();

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

    // ADC1 Init
    Hal_ADC_vInit();

	// DMA1 Init
	Hal_DMA_1_vInitChannel2();
	Hal_DMA_1_vInitChannel3();

	// I2C Init
    Hal_I2C_vInitMaster(OLED);

    // SPI Receiver Init
    Hal_SPI_vInitReceiver();

    // OLED SSD Init
    SSD1306_vInit();

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
//	Config_vSetupGPIO(9, GPIO_AF, GPIO_PUSHPULL, GPIO_PULLUP, GPIO_B);
//	Hal_GPIO_vSetupAlternateFunction(9, 7, GPIO_B);
	GPIOB->MODER &= ~(3U << 18);
	GPIOB->MODER |= (1U << 19);
	GPIOB->OTYPER &= ~(1U << 9);
	GPIOB->PUPDR &= ~(3U << 18);
	GPIOB->OSPEEDR &= ~(3U << 18);
    GPIOB->AFRH &= ~(0xF << 4);  // Clear AFR for PB9
    GPIOB->AFRH |=  (0x7 << 4);  // AF7 = USART3

	/* Using PB6 SCL and PB7 SDA, because the other ones interfere with debug */
	Config_vSetupGPIO(6, GPIO_AF, GPIO_PUSHPULL, GPIO_PULLUP, GPIO_B);
	Hal_GPIO_vSetupAlternateFunction(6, 4, GPIO_B);

	Config_vSetupGPIO(7, GPIO_AF, GPIO_PUSHPULL, GPIO_PULLUP, GPIO_B);
	Hal_GPIO_vSetupAlternateFunction(7, 4, GPIO_B);

    // Activate PA0 for the ADC as Analog input
	Config_vSetupGPIO(0, GPIO_ANALOG, GPIO_PUSHPULL, GPIO_NON, GPIO_A);

	// PB3 SPI1 SCLK, PB4 SPI1 MISO, PB5 SPI1 MOSI -> AF5
	GPIOB->MODER &= ~(3U << 10);
	GPIOB->MODER |= (1U << 11);
	GPIOB->OTYPER &= ~(1U << 5);
	GPIOB->PUPDR &= ~(3U << 10);
	GPIOB->OSPEEDR &= ~(3U << 10);
    GPIOB->AFRL &= ~(0xF << 12);
    GPIOB->AFRL |=  (0x5 << 12);  // AF5 = SPI1

	GPIOB->MODER &= ~(3U << 12);
	GPIOB->MODER |= (1U << 13);
	GPIOB->OTYPER &= ~(1U << 6);
	GPIOB->PUPDR &= ~(3U << 12);
	GPIOB->OSPEEDR &= ~(3U << 12);
    GPIOB->AFRL &= ~(0xF << 16);
    GPIOB->AFRL |=  (0x5 << 16);  // AF5 = SPI1

	GPIOB->MODER &= ~(3U << 14);
	GPIOB->MODER |= (1U << 15);
	GPIOB->OTYPER &= ~(1U << 7);
	GPIOB->PUPDR &= ~(3U << 14);
	GPIOB->OSPEEDR &= ~(3U << 14);
    GPIOB->AFRL &= ~(0xF << 20);
    GPIOB->AFRL |=  (0x5 << 20);  // AF5 = SPI1
}



