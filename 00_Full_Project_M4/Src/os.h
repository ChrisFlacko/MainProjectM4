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

/* Task states */
typedef enum taskState
{
	t_ready,
	t_running,
	t_blocked,
	t_sleeping
}taskState_e;

/* Task control block */
typedef struct tcb
{
	uint32_t *psp;			// Psp of the task
	struct tcb *nextPt;		// Pointer to the next task
	uint8_t prio;			// Priority of the task 0-8
	taskState_e state;		// Which state the task is currently in
	uint32_t waitTick;		// Sleep/Timeout ticks
	void *waitObj;			// Object which is waited for
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
