/*
 * main.h
 *
 *  Created on: Jun 22, 2025
 *      Author: chris
 */

#ifndef MAIN_H_
#define MAIN_H_



void Main_vSetupGPIOs(void);

void vEnable_Peripheral_Clocks(TypeDef_Peripheral_Bus* periph);

void vClockSelect(void);

#endif /* MAIN_H_ */
