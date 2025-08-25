/*
 * os.h
 *
 *  Created on: Jul 15, 2025
 *      Author: chris
 */

#ifndef OS_H_
#define OS_H_

#include "memorymap.h"
#include "typedefs.h"
#include "peripherals.h"
#include "../Inc/hal_gpio.h"

/* Stack size frame */
#define STACK_SIZE 		250U

/* Task control block */
typedef struct tcb
{
	uint32_t *psp;
	struct tcb *nextPt;

}TCB;

/* Tasks */
extern TCB task1;
extern TCB task2;
extern TCB *currentTask;

/* Reserve the memory space for the two tasks */
/* Make sure they are 8byte aligned */
extern __attribute__((aligned(8))) uint32_t u32Task1Stack[STACK_SIZE];
extern __attribute__((aligned(8))) uint32_t u32Task2Stack[STACK_SIZE];

/* Functions for RTOS */
/*
 * This function provides the initial stack frame for the second task, so the task switch from task1 to task2 is working just fine.
 */
void OS_vInitialStackFrame(void);


void OS_vStartRTOS(void);

void Task1Func(void);
void Task2Func(void);

void OS_vAddThreads(void);



#endif /* OS_H_ */
