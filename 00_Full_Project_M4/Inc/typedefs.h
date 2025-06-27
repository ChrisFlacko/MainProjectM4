/*
 * types.h
 *
 *  Created on: Jun 27, 2025
 *      Author: chris
 */

#ifndef TYPEDEFS_H_
#define TYPEDEFS_H_

#include "memorymap.h"

/**********************************************Analog-Digital-Converter**********************************************************************/

typedef struct
{
	__IO uint32_t ISR;
	__IO uint32_t IER;
	__IO uint32_t CR;
	__IO uint32_t CFGR;
	__IO uint32_t reserved1;
	__IO uint32_t SMPR1;
	__IO uint32_t SMPR2;
	__IO uint32_t reserved2;
	__IO uint32_t TR1;
	__IO uint32_t TR2;
	__IO uint32_t TR3;
	__IO uint32_t reserved3;
	__IO uint32_t SQR1;
	__IO uint32_t SQR2;
	__IO uint32_t SQR3;
	__IO uint32_t SQR4;
	__IO uint32_t DR;
	__IO uint32_t reserved4[2];
	__IO uint32_t JSQR;
	__IO uint32_t reserved5[4];
	__IO uint32_t OFR1;
	__IO uint32_t OFR2;
	__IO uint32_t OFR3;
	__IO uint32_t OFR4;
	__IO uint32_t reserved6[4];
	__IO uint32_t JDR1;
	__IO uint32_t JDR2;
	__IO uint32_t JDR3;
	__IO uint32_t JDR4;
	__IO uint32_t reserved7[4];
	__IO uint32_t AWD2CR;
	__IO uint32_t AWD3CR;
	__IO uint32_t reserved8[2];
	__IO uint32_t DIFSEL;
	__IO uint32_t CALFACT;
}TypeDef_ADC;

typedef struct
{
	__IO uint32_t CSR;
	__IO uint32_t reserved;
	__IO uint32_t CCR;
	__IO uint32_t CDR;
}TypeDef_ADC_Master;

/******************************************************GPIO***********************************************************************************/

typedef struct
{
	__IO int MODER;
	__IO int OTYPER;
	__IO int OSPEEDR;
	__IO int PUPDR;
	__IO int IDR;
	__IO int ODR;
	__IO int BSRR;
	__IO int LCKR;
	__IO int AFRL;
	__IO int AFRH;
	__IO int BRR;
}TypeDef_GPIO;

/**********************************************Direct-Memory-Access*************************************************************************/

typedef struct
{
	__IO uint32_t ISR;
	__IO uint32_t IFCR;
	__IO uint32_t CCR1;
	__IO uint32_t CNDTR1;
	__IO uint32_t CPAR1;
	__IO uint32_t CMAR1;
	__IO uint32_t reserved1;
	__IO uint32_t CCR2;
	__IO uint32_t CNDTR2;
	__IO uint32_t CPAR2;
	__IO uint32_t CMAR2;
	__IO uint32_t reserved2;
	__IO uint32_t CCR3;
	__IO uint32_t CNDTR3;
	__IO uint32_t CPAR3;
	__IO uint32_t CMAR3;
	__IO uint32_t reserved3;
	__IO uint32_t CCR4;
	__IO uint32_t CNDTR4;
	__IO uint32_t CPAR4;
	__IO uint32_t CMAR4;
	__IO uint32_t reserved4;
	__IO uint32_t CCR5;
	__IO uint32_t CNDTR5;
	__IO uint32_t CPAR5;
	__IO uint32_t CMAR5;
	__IO uint32_t reserved5;
	__IO uint32_t CCR6;
	__IO uint32_t CNDTR6;
	__IO uint32_t CPAR6;
	__IO uint32_t CMAR6;
	__IO uint32_t reserved6;
	__IO uint32_t CCR7;
	__IO uint32_t CNDTR7;
	__IO uint32_t CPAR7;
	__IO uint32_t CMAR7;
}TypeDef_DMA1;

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

typedef struct
{
	__IO uint32_t CR;
	__IO uint32_t CFGR;
	__IO uint32_t CIR;
	__IO uint32_t APB2RSTR;
	__IO uint32_t APB1SRTR;
	__IO uint32_t AHBENR;
	__IO uint32_t APB2ENR;
	__IO uint32_t APB1ENR;
	__IO uint32_t BDCR;
	__IO uint32_t CSR;
	__IO uint32_t AHBRSTR;
	__IO uint32_t CFGR2;
	__IO uint32_t CFGR3;
}TypeDef_RCC;

typedef struct SysTick
{
	__IO uint32_t CTRL;
	__IO uint32_t LOAD;
	__IO uint32_t VAL;
	__IO uint32_t CALIB;

}TypeDef_SysTick;

typedef struct
{
	__IO uint32_t CFGR1;
	__IO uint32_t RCR;
	__IO uint32_t EXTICR1;
	__IO uint32_t EXTICR2;
	__IO uint32_t EXTICR3;
	__IO uint32_t EXTICR4;
	__IO uint32_t CFGR2;
	__IO uint32_t reserved[0xE];
	__IO uint32_t CFGR3;
	__IO uint32_t CFGR4;
}TypeDef_SYSCFG;

typedef struct
{
	__IO uint32_t IMR;
	__IO uint32_t EMR1;
	__IO uint32_t RTSR1;
	__IO uint32_t FTSR1;
	__IO uint32_t SWIER1;
	__IO uint32_t PR1;
	__IO uint32_t IMR2;
	__IO uint32_t EMR2;
	__IO uint32_t RTSR2;
	__IO uint32_t FTSR2;
	__IO uint32_t SWIER2;
	__IO uint32_t PR2;
}TypeDef_EXTI;

typedef struct
{
	__IO uint32_t CR1;
	__IO uint32_t CR2;
	__IO uint32_t CR3;
	__IO uint32_t BRR;
	__IO uint32_t GTPR;
	__IO uint32_t RTOR;
	__IO uint32_t RQR;
	__IO uint32_t ISR;
	__IO uint32_t ICR;
	__IO uint32_t RDR;
	__IO uint32_t TDR;

}TypeDef_USART;

#endif /* TYPEDEFS_H_ */
